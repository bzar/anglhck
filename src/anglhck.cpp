#include "anglhck.h"
#include "anglhckObject.h"

#include <new>

namespace
{

  void objectConstructor(void* memory)
  {
    glhckObject* o = glhckCubeNew(1);
    new(memory) anglhck::Object(o);
  }

  void objectDestructor(void* memory)
  {
    static_cast<anglhck::Object*>(memory)->~Object();
  }

}

int anglhck::registerToEngine(asIScriptEngine *engine)
{
  engine->RegisterObjectType("Object", sizeof(Object), asOBJ_VALUE);
  engine->RegisterObjectBehaviour("Object", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(objectConstructor), asCALL_CDECL_OBJLAST);
  engine->RegisterObjectBehaviour("Object", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(objectDestructor), asCALL_CDECL_OBJLAST);
  engine->RegisterObjectMethod("Object", "void draw()", asMETHOD(Object, draw), asCALL_THISCALL);
  engine->RegisterObjectMethod("Object", "void position(float x, float y, float z)", asMETHOD(Object, position), asCALL_THISCALL);
  engine->RegisterObjectMethod("Object", "void rotation(float x, float y, float z)", asMETHOD(Object, rotation), asCALL_THISCALL);
  return 0;
}
