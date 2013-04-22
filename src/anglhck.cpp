#include "anglhck.h"

#include <string>

namespace
{
  glhckTexture* createTexture(std::string const& filename, const unsigned int importFlags, const glhckTextureParameters &parameters);
  glhckObject* createModel(std::string const& filename, float const size, const unsigned int importFlags);

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
  engine->RegisterEnum("glhckTextureWrap");
  engine->RegisterEnumValue("glhckTextureWrap", "GLHCK_WRAP_REPEAT", GLHCK_WRAP_REPEAT);
  engine->RegisterEnumValue("glhckTextureWrap", "GLHCK_WRAP_MIRRORED_REPEAT", GLHCK_WRAP_MIRRORED_REPEAT);
  engine->RegisterEnumValue("glhckTextureWrap", "GLHCK_WRAP_CLAMP_TO_EDGE", GLHCK_WRAP_CLAMP_TO_EDGE);
  engine->RegisterEnumValue("glhckTextureWrap", "GLHCK_WRAP_CLAMP_TO_BORDER", GLHCK_WRAP_CLAMP_TO_BORDER);

  engine->RegisterEnum("glhckTextureFilter");
  engine->RegisterEnumValue("glhckTextureFilter", "GLHCK_FILTER_NEAREST", GLHCK_FILTER_NEAREST);
  engine->RegisterEnumValue("glhckTextureFilter", "GLHCK_FILTER_LINEAR", GLHCK_FILTER_LINEAR);
  engine->RegisterEnumValue("glhckTextureFilter", "GLHCK_FILTER_NEAREST_MIPMAP_NEAREST", GLHCK_FILTER_NEAREST_MIPMAP_NEAREST);
  engine->RegisterEnumValue("glhckTextureFilter", "GLHCK_FILTER_LINEAR_MIPMAP_NEAREST", GLHCK_FILTER_LINEAR_MIPMAP_NEAREST);
  engine->RegisterEnumValue("glhckTextureFilter", "GLHCK_FILTER_NEAREST_MIPMAP_LINEAR", GLHCK_FILTER_NEAREST_MIPMAP_LINEAR);
  engine->RegisterEnumValue("glhckTextureFilter", "GLHCK_FILTER_LINEAR_MIPMAP_LINEAR", GLHCK_FILTER_LINEAR_MIPMAP_LINEAR);

  engine->RegisterEnum("glhckTextureCompareMode");
  engine->RegisterEnumValue("glhckTextureCompareMode", "GLHCK_COMPARE_NONE", GLHCK_COMPARE_NONE);
  engine->RegisterEnumValue("glhckTextureCompareMode", "GLHCK_COMPARE_REF_TO_TEXTURE", GLHCK_COMPARE_REF_TO_TEXTURE);

  engine->RegisterEnum("glhckTextureCompareFunc");
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_LEQUAL", GLHCK_COMPARE_LEQUAL);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_GEQUAL", GLHCK_COMPARE_GEQUAL);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_LESS", GLHCK_COMPARE_LESS);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_GREATER", GLHCK_COMPARE_GREATER);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_EQUAL", GLHCK_COMPARE_EQUAL);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_NOTEQUAL", GLHCK_COMPARE_NOTEQUAL);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_ALWAYS", GLHCK_COMPARE_ALWAYS);
  engine->RegisterEnumValue("glhckTextureCompareFunc", "GLHCK_COMPARE_NEVER", GLHCK_COMPARE_NEVER);

  engine->RegisterEnum("glhckTextureCompression");
  engine->RegisterEnumValue("glhckTextureCompression", "GLHCK_COMPRESSION_NONE", GLHCK_COMPRESSION_NONE);
  engine->RegisterEnumValue("glhckTextureCompression", "GLHCK_COMPRESSION_DXT", GLHCK_COMPRESSION_DXT);

  engine->RegisterObjectType("glhckTextureParameters", sizeof(glhckTextureParameters), asOBJ_VALUE | asOBJ_POD);
  engine->RegisterObjectProperty("glhckTextureParameters", "float minLod", asOFFSET(glhckTextureParameters, minLod));
  engine->RegisterObjectProperty("glhckTextureParameters", "float maxLod", asOFFSET(glhckTextureParameters, maxLod));
  engine->RegisterObjectProperty("glhckTextureParameters", "float biasLod", asOFFSET(glhckTextureParameters, biasLod));
  engine->RegisterObjectProperty("glhckTextureParameters", "int baseLevel", asOFFSET(glhckTextureParameters, baseLevel));
  engine->RegisterObjectProperty("glhckTextureParameters", "int maxLevel", asOFFSET(glhckTextureParameters, maxLevel));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureWrap wrapS", asOFFSET(glhckTextureParameters, wrapS));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureWrap wrapT", asOFFSET(glhckTextureParameters, wrapT));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureWrap wrapR", asOFFSET(glhckTextureParameters, wrapR));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureFilter minFilter", asOFFSET(glhckTextureParameters, minFilter));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureFilter magFilter", asOFFSET(glhckTextureParameters, magFilter));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureCompareMode compareMode", asOFFSET(glhckTextureParameters, compareMode));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureCompareFunc compareFunc", asOFFSET(glhckTextureParameters, compareFunc));
  engine->RegisterObjectProperty("glhckTextureParameters", "glhckTextureCompression compression", asOFFSET(glhckTextureParameters, compression));
  engine->RegisterObjectProperty("glhckTextureParameters", "int8 mipmap", asOFFSET(glhckTextureParameters, mipmap));

  engine->RegisterObjectType("glhckTexture", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("glhckTexture", asBEHAVE_FACTORY, "glhckTexture@ createTexture(const string, const uint, const glhckTextureParameters)", asFUNCTION(createTexture), asCALL_CDECL);
  engine->RegisterObjectBehaviour("glhckTexture", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckTextureRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("glhckTexture", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckTextureFree), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectType("glhckObject", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("glhckObject", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckObjectRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("glhckObject", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckObjectFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void draw()", asFUNCTION(glhckObjectDraw), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void setPosition(float x, float y, float z)", asFUNCTION(glhckObjectPositionf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void setRotation(float x, float y, float z)", asFUNCTION(glhckObjectRotationf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void move(float x, float y, float z)", asFUNCTION(glhckObjectMovef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void rotate(float x, float y, float z)", asFUNCTION(glhckObjectRotatef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void target(float x, float y, float z)", asFUNCTION(glhckObjectTargetf), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void scale(float x, float y, float z)", asFUNCTION(glhckObjectScalef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_x()", asFUNCTION(getObjectX), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_y()", asFUNCTION(getObjectY), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_z()", asFUNCTION(getObjectZ), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_x(const float)", asFUNCTION(setObjectX), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_y(const float)", asFUNCTION(setObjectY), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_z(const float)", asFUNCTION(setObjectZ), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_xRotation()", asFUNCTION(getObjectXRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_yRotation()", asFUNCTION(getObjectYRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_zRotation()", asFUNCTION(getObjectZRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_xRotation(const float)", asFUNCTION(setObjectXRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_yRotation(const float)", asFUNCTION(setObjectYRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_zRotation(const float)", asFUNCTION(setObjectZRotation), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_xScale()", asFUNCTION(getObjectXScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_yScale()", asFUNCTION(getObjectYScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "float get_zScale()", asFUNCTION(getObjectZScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_xScale(const float)", asFUNCTION(setObjectXScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_yScale(const float)", asFUNCTION(setObjectYScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void set_zScale(const float)", asFUNCTION(setObjectZScale), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckObject", "void setTexture(glhckTexture@ texture)", asFUNCTION(glhckObjectTexture), asCALL_CDECL_OBJFIRST);
  engine->RegisterGlobalFunction("glhckObject@ createCube(const float)", asFUNCTION(glhckCubeNew), asCALL_CDECL);
  engine->RegisterGlobalFunction("glhckObject@ createSprite(glhckTexture@ texture, const float width, const float height)", asFUNCTION(glhckSpriteNew), asCALL_CDECL);
  engine->RegisterGlobalFunction("glhckObject@ createModel(const string, const float, uint8)", asFUNCTION(createModel), asCALL_CDECL);

  engine->RegisterObjectType("glhckCamera", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("glhckCamera", asBEHAVE_FACTORY, "glhckCamera@ f()", asFUNCTION(glhckCameraNew), asCALL_CDECL);
  engine->RegisterObjectBehaviour("glhckCamera", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckCameraRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("glhckCamera", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckCameraFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckCamera", "glhckObject@ get_object()", asFUNCTION(glhckCameraGetObject), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("glhckCamera", "void update()", asFUNCTION(glhckCameraUpdate), asCALL_CDECL_OBJFIRST);

  return 0;
}

namespace
{
  glhckTexture* createTexture(std::string const& filename, unsigned int const importFlags, glhckTextureParameters const& parameters)
  {
    return glhckTextureNew(filename.data(), importFlags, &parameters);
  }

  glhckObject* createModel(std::string const& filename, float const size, const unsigned int importFlags)
  {
    return glhckModelNew(filename.data(), size, importFlags);
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
