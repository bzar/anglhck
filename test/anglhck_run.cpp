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

  glhckCamera* camera = glhckCameraNew();
  glhckObjectPositionf(glhckCameraGetObject(camera), 25, 25, 50);
  glhckObjectTargetf(glhckCameraGetObject(camera), 0, 0, 0);
  glhckCameraRange(camera, 1.0f, 1000.0f);
  glhckCameraUpdate(camera);

  run(scriptFile);

  return 0;
}

void run(std::string const& scriptFile)
{
  std::cout << "Creating engine" << std::endl;
  asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

  std::cout << "Registering objects and functions" << std::endl;
  anglhck::registerToEngine(engine);

  RegisterStdString(engine);
  engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);
  engine->RegisterGlobalFunction("double time()", asFUNCTION(currentTime), asCALL_CDECL);
  engine->RegisterGlobalFunction("void swap()", asFUNCTION(swap), asCALL_CDECL);

  std::cout << "Loading script" << std::endl;
  CScriptBuilder builder;
  builder.StartNewModule(engine, "MyModule");
  if(builder.AddSectionFromFile(scriptFile.data()) < 0)
  {
    std::cerr << "Error loading script " << scriptFile << std::endl;
    return;
  }
  builder.BuildModule();
  asIScriptModule *mod = engine->GetModule("MyModule");
  asIScriptFunction *func = mod->GetFunctionByDecl("void main()");

  std::cout << "Creating context" << std::endl;
  asIScriptContext *ctx = engine->CreateContext();
  ctx->Prepare(func);

  std::cout << "Running script" << std::endl;
  int ret = ctx->Execute();

  if( ret == asEXECUTION_EXCEPTION )
  {
    std::cout << ctx->GetExceptionString() << std::endl;
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
