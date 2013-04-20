#include "anglhck.h"

namespace
{

  glhckObject* cubeFactory()
  {
    return glhckCubeNew(1);
  }

}

int anglhck::registerToEngine(asIScriptEngine *engine)
{
  engine->RegisterObjectType("Object", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Object", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckObjectRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Object", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckObjectFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void draw()", asFUNCTION(glhckObjectDraw), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void position(float x, float y, float z)", asFUNCTION(glhckObjectPositionf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void rotation(float x, float y, float z)", asFUNCTION(glhckObjectRotationf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void target(float x, float y, float z)", asFUNCTION(glhckObjectTargetf), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectType("Cube", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Cube", asBEHAVE_FACTORY, "Cube@ f()", asFUNCTION(cubeFactory), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Cube", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckObjectRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Cube", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckObjectFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Cube", "void draw()", asFUNCTION(glhckObjectDraw), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Cube", "void position(float x, float y, float z)", asFUNCTION(glhckObjectPositionf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Cube", "void rotation(float x, float y, float z)", asFUNCTION(glhckObjectRotationf), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectType("Camera", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera@ f()", asFUNCTION(glhckCameraNew), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckCameraRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckCameraFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "void draw()", asFUNCTION(glhckObjectDraw), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "Object@ get_object()", asFUNCTION(glhckCameraGetObject), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "void update()", asFUNCTION(glhckCameraUpdate), asCALL_CDECL_OBJFIRST);

  return 0;
}
