#include "anglhck.h"
#include "GL/glfw3.h"

#include "scriptbuilder/scriptbuilder.h"
#include "scriptstdstring/scriptstdstring.h"

#include <cstdlib>
#include <iostream>
#include <string>

int const WIDTH = 800;
int const HEIGHT = 480;

void run(GLFWwindow* window, std::string const& scriptFile);
void print(std::string &msg);

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " [glhck options] <script>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string scriptFile(argv[argc - 1]);

  GLFWwindow* window;
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

  run(window, scriptFile);

  return 0;
}

void run(GLFWwindow* window, std::string const& scriptFile)
{
  asIScriptEngine* engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
  anglhck::registerToEngine(engine);

  RegisterStdString(engine);
  engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(print), asCALL_CDECL);

  CScriptBuilder builder;
  builder.StartNewModule(engine, "MyModule");
  builder.AddSectionFromFile(scriptFile);
  builder.BuildModule();
  asIScriptModule *mod = engine->GetModule("MyModule");
  asIScriptFunction *func = mod->GetFunctionByDecl("void main()");
  asIScriptContext *ctx = engine->CreateContext();
  ctx->Prepare(func);
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

