#include "anglhck.h"
#include "GL/glfw3.h"

#include "scriptbuilder/scriptbuilder.h"
#include "scriptstdstring/scriptstdstring.h"

#include <cstdlib>
#include <iostream>
#include <string>

int const WIDTH = 800;
int const HEIGHT = 480;

GLFWwindow* window;

void run(std::string const& scriptFile);
void print(std::string &msg);
void swap();
double currentTime();
void messageCallback(const asSMessageInfo *msg, void *param);

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

  run(scriptFile);

  glhckContextTerminate();
  glfwTerminate();

  return 0;
}

void run(std::string const& scriptFile)
{
  std::cout << "-- Creating engine" << std::endl;
  asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  engine->SetMessageCallback(asFUNCTION(messageCallback), 0, asCALL_CDECL);

  std::cout << "-- Registering objects and functions" << std::endl;
  RegisterStdString(engine);
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
  std::cout << msg.c_str();
}

void swap()
{
  glhckRender();
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
  std::cout << msg->section << "(" << msg->row << ", " << msg->col << ") : " << type << " : " << msg->message << std::endl;
}
