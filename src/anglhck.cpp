#include "anglhck.h"

namespace
{
  glhckObject* createCube(float const size);
  void setObjectX(glhckObject* object, float const value);
  void setObjectY(glhckObject* object, float const value);
  void setObjectZ(glhckObject* object, float const value);
  float getObjectX(glhckObject* object);
  float getObjectY(glhckObject* object);
  float getObjectZ(glhckObject* object);
  void setObjectXRotation(glhckObject* object, float const value);
  void setObjectYRotation(glhckObject* object, float const value);
  void setObjectZRotation(glhckObject* object, float const value);
  float getObjectXRotation(glhckObject* object);
  float getObjectYRotation(glhckObject* object);
  float getObjectZRotation(glhckObject* object);
  void setObjectXScale(glhckObject* object, float const value);
  void setObjectYScale(glhckObject* object, float const value);
  void setObjectZScale(glhckObject* object, float const value);
  float getObjectXScale(glhckObject* object);
  float getObjectYScale(glhckObject* object);
  float getObjectZScale(glhckObject* object);
}

int anglhck::registerToEngine(asIScriptEngine *engine)
{
  engine->RegisterObjectType("Object", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Object", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckObjectRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Object", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckObjectFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void draw()", asFUNCTION(glhckObjectDraw), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void setPosition(float x, float y, float z)", asFUNCTION(glhckObjectPositionf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void setRotation(float x, float y, float z)", asFUNCTION(glhckObjectRotationf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void move(float x, float y, float z)", asFUNCTION(glhckObjectMovef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void rotate(float x, float y, float z)", asFUNCTION(glhckObjectRotatef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void target(float x, float y, float z)", asFUNCTION(glhckObjectTargetf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void scale(float x, float y, float z)", asFUNCTION(glhckObjectScalef), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "float get_x()", asFUNCTION(getObjectX), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "float get_y()", asFUNCTION(getObjectY), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "float get_z()", asFUNCTION(getObjectZ), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "void set_x(const float)", asFUNCTION(setObjectX), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void set_y(const float)", asFUNCTION(setObjectY), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void set_z(const float)", asFUNCTION(setObjectZ), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "float get_xRotation()", asFUNCTION(getObjectXRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "float get_yRotation()", asFUNCTION(getObjectYRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "float get_zRotation()", asFUNCTION(getObjectZRotation), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "void set_xRotation(const float)", asFUNCTION(setObjectXRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void set_yRotation(const float)", asFUNCTION(setObjectYRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void set_zRotation(const float)", asFUNCTION(setObjectZRotation), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "float get_xScale()", asFUNCTION(getObjectXScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "float get_yScale()", asFUNCTION(getObjectYScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "float get_zScale()", asFUNCTION(getObjectZScale), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "void set_xScale(const float)", asFUNCTION(setObjectXScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void set_yScale(const float)", asFUNCTION(setObjectYScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "void set_zScale(const float)", asFUNCTION(setObjectZScale), asCALL_CDECL_OBJFIRST);

  engine->RegisterGlobalFunction("Object@ createCube(const float)", asFUNCTION(createCube), asCALL_CDECL);

  engine->RegisterObjectType("Camera", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera@ f()", asFUNCTION(glhckCameraNew), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckCameraRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckCameraFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "Object@ get_object()", asFUNCTION(glhckCameraGetObject), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "void update()", asFUNCTION(glhckCameraUpdate), asCALL_CDECL_OBJFIRST);

  return 0;
}

namespace
{

  glhckObject* createCube(float const size)
  {
    return glhckCubeNew(size);
  }

  void setObjectX(glhckObject* object, float const value)
  {
    kmVec3 const* position = glhckObjectGetPosition(object);
    glhckObjectPositionf(object, value, position->y, position->z);
  }

  void setObjectY(glhckObject* object, float const value)
  {
    kmVec3 const* position = glhckObjectGetPosition(object);
    glhckObjectPositionf(object, position->x, value, position->z);
  }

  void setObjectZ(glhckObject* object, float const value)
  {
    kmVec3 const* position = glhckObjectGetPosition(object);
    glhckObjectPositionf(object, position->x, position->y, value);
  }

  float getObjectX(glhckObject* object)
  {
    return glhckObjectGetPosition(object)->x;
  }

  float getObjectY(glhckObject* object)
  {
    return glhckObjectGetPosition(object)->y;
  }

  float getObjectZ(glhckObject* object)
  {
    return glhckObjectGetPosition(object)->z;
  }

  void setObjectXRotation(glhckObject* object, float const value)
  {
    kmVec3 const* rotation = glhckObjectGetRotation(object);
    glhckObjectRotationf(object, value, rotation->y, rotation->z);
  }

  void setObjectYRotation(glhckObject* object, float const value)
  {
    kmVec3 const* rotation = glhckObjectGetRotation(object);
    glhckObjectRotationf(object, rotation->x, value, rotation->z);
  }

  void setObjectZRotation(glhckObject* object, float const value)
  {
    kmVec3 const* rotation = glhckObjectGetRotation(object);
    glhckObjectRotationf(object, rotation->x, rotation->y, value);
  }

  float getObjectXRotation(glhckObject* object)
  {
    return glhckObjectGetRotation(object)->x;
  }

  float getObjectYRotation(glhckObject* object)
  {
    return glhckObjectGetRotation(object)->y;
  }

  float getObjectZRotation(glhckObject* object)
  {
    return glhckObjectGetRotation(object)->z;
  }

  void setObjectXScale(glhckObject* object, float const value)
  {
    kmVec3 const* scale = glhckObjectGetScale(object);
    glhckObjectScalef(object, value, scale->y, scale->z);
  }

  void setObjectYScale(glhckObject* object, float const value)
  {
    kmVec3 const* scale = glhckObjectGetScale(object);
    glhckObjectScalef(object, scale->x, value, scale->z);
  }

  void setObjectZScale(glhckObject* object, float const value)
  {
    kmVec3 const* scale = glhckObjectGetScale(object);
    glhckObjectScalef(object, scale->x, scale->y, value);
  }

  float getObjectXScale(glhckObject* object)
  {
    return glhckObjectGetScale(object)->x;
  }

  float getObjectYScale(glhckObject* object)
  {
    return glhckObjectGetScale(object)->y;
  }

  float getObjectZScale(glhckObject* object)
  {
    return glhckObjectGetScale(object)->z;
  }
}
