#include "anglhck.h"
#include "GL/glfw3.h"

#include "scriptbuilder/scriptbuilder.h"
#include "scriptstdstring/scriptstdstring.h"
#include "scriptarray/scriptarray.h"
#include "scripthelper/scripthelper.h"

#include "consolehck.h"
#include "utf8.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

int const WIDTH = 800;
int const HEIGHT = 480;

struct Context
{
  consolehckConsole* console;
  bool consoleVisible;
};


GLFWwindow* window;

void run(std::string const& scriptFile, Context &context);
void print(std::string &msg);
void swap();
double currentTime();
void messageCallback(const asSMessageInfo *msg, void *param);


void quit()
{
  asIScriptContext* ctx = asGetActiveContext();
  if(ctx)
  {
    ctx->Abort();
  }
}

static void windowCloseCallback(GLFWwindow* w)
{
  quit();
}

void windowCharCallback(GLFWwindow* w, unsigned int c)
{
  Context* context = static_cast<Context*>(glfwGetWindowUserPointer(w));
  if(context->consoleVisible)
  {
    consolehckConsole* console = context->console;
    consolehckConsoleInputUnicodeChar(console, c);
    consolehckConsoleUpdate(console);
  }
}

void windowKeyCallback(GLFWwindow* w, int key, int action)
{
  Context* context = static_cast<Context*>(glfwGetWindowUserPointer(w));
  if(context->consoleVisible)
  {
    consolehckConsole* console = context->console;

    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
      consolehckConsoleInputEnter(console);
      consolehckConsoleUpdate(console);
    }
    else if(key == GLFW_KEY_BACKSPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
      consolehckConsoleInputPopUnicodeChar(console);
      consolehckConsoleUpdate(console);
    }
    else if(key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
      consolehckConsoleOutputOffset(console, consolehckConsoleOutputGetOffset(console) + 12);
      consolehckConsoleUpdate(console);
    }
    else if(key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
      consolehckConsoleOutputOffset(console, consolehckConsoleOutputGetOffset(console) - 12);
      consolehckConsoleUpdate(console);
    }
  }

  if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
  {
    context->consoleVisible = !context->consoleVisible;
  }
}

consolehckContinue angelscriptConsoleCallback(consolehckConsole* console, unsigned int const* input)
{
  consolehckConsoleOutputUnicodeString(console, input);
  consolehckConsoleOutputChar(console, '\n');

  asIScriptContext* ctx = asGetActiveContext();

  unsigned int encodedLength = utf8EncodedStringLength(input);
  char* code = new char[encodedLength];
  utf8EncodeString(input, code);

  if(ctx)
  {
    asIScriptEngine* engine = ctx->GetEngine();
    std::cout << "Running code: '" << code << "'" << std::endl;
    if(ExecuteString(engine, code) < 0)
    {
      std::cout << "Invalid statement: '" << code << "'" << std::endl;
    }
  }

  delete[] code;

  consolehckConsoleInputClear(console);
  consolehckConsoleUpdate(console);

  return CONSOLEHCK_CONTINUE;
}

consolehckConsole* createAngelscriptConsole()
{
  consolehckConsole* console = consolehckConsoleNew(WIDTH, HEIGHT/2);
  glhckObjectPositionf(console->object, WIDTH/2, 3*HEIGHT/4, 0);
  consolehckConsoleUpdate(console);
  consolehckConsoleInputCallbackRegister(console, angelscriptConsoleCallback);

  return console;
}


int main(int argc, char** argv)
{
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [glhck options] <script>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string scriptFile(argv[argc - 1]);

  if (!glfwInit())
     return EXIT_FAILURE;

  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  if (!(window = glfwCreateWindow(WIDTH, HEIGHT, "anglhck - simple.cpp", NULL, NULL)))
     return EXIT_FAILURE;

  glfwMakeContextCurrent(window);

  glfwSwapInterval(0);

  if (!glhckContextCreate(argc, argv))
     return EXIT_FAILURE;

  if (!glhckDisplayCreate(WIDTH, HEIGHT, GLHCK_RENDER_AUTO))
     return EXIT_FAILURE;

  Context context;
  context.console = createAngelscriptConsole();
  context.consoleVisible = false;
  glfwSetWindowUserPointer(window, &context);
  glfwSetCharCallback(window, windowCharCallback);
  glfwSetKeyCallback(window, windowKeyCallback);
  glfwSetWindowCloseCallback(window, windowCloseCallback);

  run(scriptFile, context);

  consolehckConsoleFree(context.console);
  glhckContextTerminate();
  glfwTerminate();

  return 0;
}

void run(std::string const& scriptFile, Context& context)
{
  std::cout << "-- Creating engine" << std::endl;
  asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  engine->SetUserData(&context);
  engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);

  std::cout << "-- Registering objects and functions" << std::endl;
  RegisterStdString(engine);
  RegisterScriptArray(engine, true);
  anglhck::registerToEngine(engine);

  engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
  engine->RegisterGlobalFunction("double time()", asFUNCTION(currentTime), asCALL_CDECL);
  engine->RegisterGlobalFunction("void render()", asFUNCTION(swap), asCALL_CDECL);


  std::cout << "-- Loading script" << std::endl;
  CScriptBuilder builder;
  builder.StartNewModule(engine, "MyModule");
  if(builder.AddSectionFromFile(scriptFile.data()) < 0)
  {
    std::cerr << "-!- Error loading script " << scriptFile << std::endl;
    return;
  }
  builder.BuildModule();
  asIScriptModule *mod = engine->GetModule("MyModule");
  asIScriptFunction *func = mod->GetFunctionByDecl("void main()");

  std::cout << "-- Creating context" << std::endl;
  asIScriptContext *ctx = engine->CreateContext();
  ctx->Prepare(func);

  std::cout << "-- Running script" << std::endl << std::endl;
  int ret = ctx->Execute();
  switch (ret) {
  case asEXECUTION_FINISHED:
    break;
  case asEXECUTION_EXCEPTION:
    std::cout << "-!- Uncaught exception: " << ctx->GetExceptionString() << std::endl;
    break;
  case asEXECUTION_ABORTED:
    std::cout << "-!- Execution aborted" << std::endl;
    break;
  case asEXECUTION_ERROR:
    std::cout << "-!- Error running script" << std::endl;
    break;
  default:
    std::cout << "-!- Error code: " << ret << std::endl;
    break;
  }
}

void print(std::string &msg)
{
  std::cout << msg;
  asIScriptContext* ctx = asGetActiveContext();
  if(ctx)
  {
    Context* context = static_cast<Context*>(ctx->GetEngine()->GetUserData());
    consolehckConsoleOutputString(context->console, msg.data());
  }
}

void swap()
{
  glfwPollEvents();

  glhckRender();

  asIScriptContext* ctx = asGetActiveContext();
  if(ctx)
  {
    Context* context = static_cast<Context*>(ctx->GetEngine()->GetUserData());
    if(context->consoleVisible)
    {
      kmMat4 currentView = *glhckRenderGetView();
      kmMat4 currentProjection = *glhckRenderGetProjection();
      kmMat4 ortho;
      kmMat4OrthographicProjection(&ortho, 0, WIDTH, 0, HEIGHT, -1, 1);
      glhckRenderProjectionOnly(&ortho);
      glhckObjectRender(context->console->object);
      glhckRenderView(&currentView);
      glhckRenderProjection(&currentProjection);
    }
  }

  glfwSwapBuffers(window);
  glhckRenderClear(GLHCK_DEPTH_BUFFER | GLHCK_COLOR_BUFFER);
}

double currentTime()
{
  return glfwGetTime();
}

void messageCallback(const asSMessageInfo *msg, void *param)
{
  const char *type = "ERR ";
  if( msg->type == asMSGTYPE_WARNING )
    type = "WARN";
  else if( msg->type == asMSGTYPE_INFORMATION )
    type = "INFO";
  std::ostringstream oss;

  oss << msg->section << "(" << msg->row << ", " << msg->col << ") : " << type << " : " << msg->message << std::endl;
  std::cout << oss.str();

  asIScriptContext* ctx = asGetActiveContext();
  if(ctx)
  {
    Context* context = static_cast<Context*>(ctx->GetEngine()->GetUserData());
    consolehckConsoleOutputString(context->console, oss.str().data());
  }
}
