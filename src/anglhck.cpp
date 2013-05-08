#include "anglhck.h"

#include <string>
#include <iostream>
#include <new>

namespace
{
  glhckTexture* createTexture(std::string const& filename, const glhckImportImageParameters& importParameters, const glhckTextureParameters& parameters);
  glhckObject* createModel(std::string const& filename, float const size, const glhckImportModelParameters&);
  glhckObject* createTextObject(glhckText *text, unsigned int const font, float const size, std::string const& str, const glhckTextureParameters &parameters);
  float stashText(glhckText *text, unsigned int const font_id, float const size, float const x, float const y, std::string const& s);
  unsigned int setTextFont(glhckText *text, std::string const& filename);

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

  void createColor(void* memory, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
}

int anglhck::registerToEngine(asIScriptEngine *engine)
{
  std::string const previousNameSpace = engine->GetDefaultNamespace();
  engine->SetDefaultNamespace("glhck");

  engine->RegisterObjectType("ImportModelParameters", sizeof(glhckImportModelParameters), asOBJ_VALUE | asOBJ_POD);
  engine->RegisterObjectProperty("ImportModelParameters", "bool animated", asOFFSET(glhckImportModelParameters, animated));
  engine->RegisterObjectProperty("ImportModelParameters", "bool flatten", asOFFSET(glhckImportModelParameters, flatten));

  engine->RegisterEnum("TextureCompression");
  engine->RegisterEnumValue("TextureCompression", "COMPRESSION_NONE", GLHCK_COMPRESSION_NONE);
  engine->RegisterEnumValue("TextureCompression", "COMPRESSION_DXT", GLHCK_COMPRESSION_DXT);

  engine->RegisterObjectType("ImportImageParameters", sizeof(glhckImportImageParameters), asOBJ_VALUE | asOBJ_POD);
  engine->RegisterObjectProperty("ImportImageParameters", "TextureCompression compression", asOFFSET(glhckImportImageParameters, compression));

  engine->RegisterEnum("TextureWrap");
  engine->RegisterEnumValue("TextureWrap", "WRAP_REPEAT", GLHCK_WRAP_REPEAT);
  engine->RegisterEnumValue("TextureWrap", "WRAP_MIRRORED_REPEAT", GLHCK_WRAP_MIRRORED_REPEAT);
  engine->RegisterEnumValue("TextureWrap", "WRAP_CLAMP_TO_EDGE", GLHCK_WRAP_CLAMP_TO_EDGE);
  engine->RegisterEnumValue("TextureWrap", "WRAP_CLAMP_TO_BORDER", GLHCK_WRAP_CLAMP_TO_BORDER);

  engine->RegisterEnum("TextureFilter");
  engine->RegisterEnumValue("TextureFilter", "FILTER_NEAREST", GLHCK_FILTER_NEAREST);
  engine->RegisterEnumValue("TextureFilter", "FILTER_LINEAR", GLHCK_FILTER_LINEAR);
  engine->RegisterEnumValue("TextureFilter", "FILTER_NEAREST_MIPMAP_NEAREST", GLHCK_FILTER_NEAREST_MIPMAP_NEAREST);
  engine->RegisterEnumValue("TextureFilter", "FILTER_LINEAR_MIPMAP_NEAREST", GLHCK_FILTER_LINEAR_MIPMAP_NEAREST);
  engine->RegisterEnumValue("TextureFilter", "FILTER_NEAREST_MIPMAP_LINEAR", GLHCK_FILTER_NEAREST_MIPMAP_LINEAR);
  engine->RegisterEnumValue("TextureFilter", "FILTER_LINEAR_MIPMAP_LINEAR", GLHCK_FILTER_LINEAR_MIPMAP_LINEAR);

  engine->RegisterEnum("TextureCompareMode");
  engine->RegisterEnumValue("TextureCompareMode", "COMPARE_NONE", GLHCK_COMPARE_NONE);
  engine->RegisterEnumValue("TextureCompareMode", "COMPARE_REF_TO_TEXTURE", GLHCK_COMPARE_REF_TO_TEXTURE);

  engine->RegisterEnum("TextureCompareFunc");
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_LEQUAL", GLHCK_COMPARE_LEQUAL);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_GEQUAL", GLHCK_COMPARE_GEQUAL);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_LESS", GLHCK_COMPARE_LESS);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_GREATER", GLHCK_COMPARE_GREATER);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_EQUAL", GLHCK_COMPARE_EQUAL);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_NOTEQUAL", GLHCK_COMPARE_NOTEQUAL);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_ALWAYS", GLHCK_COMPARE_ALWAYS);
  engine->RegisterEnumValue("TextureCompareFunc", "COMPARE_NEVER", GLHCK_COMPARE_NEVER);

  engine->RegisterObjectType("TextureParameters", sizeof(glhckTextureParameters), asOBJ_VALUE | asOBJ_POD);
  engine->RegisterObjectProperty("TextureParameters", "float minLod", asOFFSET(glhckTextureParameters, minLod));
  engine->RegisterObjectProperty("TextureParameters", "float maxLod", asOFFSET(glhckTextureParameters, maxLod));
  engine->RegisterObjectProperty("TextureParameters", "float biasLod", asOFFSET(glhckTextureParameters, biasLod));
  engine->RegisterObjectProperty("TextureParameters", "int baseLevel", asOFFSET(glhckTextureParameters, baseLevel));
  engine->RegisterObjectProperty("TextureParameters", "int maxLevel", asOFFSET(glhckTextureParameters, maxLevel));
  engine->RegisterObjectProperty("TextureParameters", "TextureWrap wrapS", asOFFSET(glhckTextureParameters, wrapS));
  engine->RegisterObjectProperty("TextureParameters", "TextureWrap wrapT", asOFFSET(glhckTextureParameters, wrapT));
  engine->RegisterObjectProperty("TextureParameters", "TextureWrap wrapR", asOFFSET(glhckTextureParameters, wrapR));
  engine->RegisterObjectProperty("TextureParameters", "TextureFilter minFilter", asOFFSET(glhckTextureParameters, minFilter));
  engine->RegisterObjectProperty("TextureParameters", "TextureFilter magFilter", asOFFSET(glhckTextureParameters, magFilter));
  engine->RegisterObjectProperty("TextureParameters", "TextureCompareMode compareMode", asOFFSET(glhckTextureParameters, compareMode));
  engine->RegisterObjectProperty("TextureParameters", "TextureCompareFunc compareFunc", asOFFSET(glhckTextureParameters, compareFunc));
  engine->RegisterObjectProperty("TextureParameters", "int8 mipmap", asOFFSET(glhckTextureParameters, mipmap));

  engine->RegisterObjectType("Texture", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Texture", asBEHAVE_FACTORY, "Texture@ f(const ::string &in, const ImportImageParameters &in, const TextureParameters &in)", asFUNCTION(createTexture), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Texture", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckTextureRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Texture", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckTextureFree), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectType("Color", sizeof(glhckColorb), asOBJ_VALUE | asOBJ_POD);
  engine->RegisterObjectBehaviour("Color", asBEHAVE_CONSTRUCT, "void f(uint8 r, uint8 g, uint8 b, uint8 a)", asFUNCTION(createColor), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectProperty("Color", "uint8 r", asOFFSET(glhckColorb, r));
  engine->RegisterObjectProperty("Color", "uint8 g", asOFFSET(glhckColorb, g));
  engine->RegisterObjectProperty("Color", "uint8 b", asOFFSET(glhckColorb, b));
  engine->RegisterObjectProperty("Color", "uint8 a", asOFFSET(glhckColorb, a));

  engine->RegisterObjectType("Material", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Material", asBEHAVE_FACTORY, "Material@ f(Texture@)", asFUNCTION(glhckMaterialNew), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Material", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckMaterialRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Material", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckMaterialFree), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Material", "void set_diffuse(const Color &in)", asFUNCTION(glhckMaterialDiffuse), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "const Color& get_diffuse()", asFUNCTION(glhckMaterialGetDiffuse), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "void set_specular(const Color &in)", asFUNCTION(glhckMaterialSpecular), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "const Color& get_specular()", asFUNCTION(glhckMaterialGetSpecular), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "void set_ambient(const Color &in)", asFUNCTION(glhckMaterialAmbient), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "const Color& get_ambient()", asFUNCTION(glhckMaterialGetAmbient), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "void set_emissive(const Color &in)", asFUNCTION(glhckMaterialEmissive), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "const Color& get_emissive()", asFUNCTION(glhckMaterialGetEmissive), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "void set_shininess(float)", asFUNCTION(glhckMaterialShininess), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Material", "float get_shininess()", asFUNCTION(glhckMaterialGetShininess), asCALL_CDECL_OBJFIRST);

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

  engine->RegisterObjectMethod("Object", "void set_material(Material@)", asFUNCTION(glhckObjectMaterial), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Object", "Material@+ get_material()", asFUNCTION(glhckObjectGetMaterial), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectMethod("Object", "void set_parent(Object@)", asFUNCTION(glhckObjectAddChild), asCALL_CDECL_OBJLAST);
  engine->RegisterObjectMethod("Object", "Object@+ get_parent()", asFUNCTION(glhckObjectParent), asCALL_CDECL_OBJFIRST);

  engine->RegisterGlobalFunction("Object@ createCube(const float)", asFUNCTION(glhckCubeNew), asCALL_CDECL);
  engine->RegisterGlobalFunction("Object@ createSprite(Texture@ texture, const float width, const float height)", asFUNCTION(glhckSpriteNew), asCALL_CDECL);
  engine->RegisterGlobalFunction("Object@ createModel(const ::string &in, const float, const ImportModelParameters &in)", asFUNCTION(createModel), asCALL_CDECL);

  engine->RegisterObjectType("Camera", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_FACTORY, "Camera@ f()", asFUNCTION(glhckCameraNew), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckCameraRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Camera", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckCameraFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "Object@+ get_object()", asFUNCTION(glhckCameraGetObject), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Camera", "void update()", asFUNCTION(glhckCameraUpdate), asCALL_CDECL_OBJFIRST);

  engine->RegisterObjectType("Text", 0, asOBJ_REF);
  engine->RegisterObjectBehaviour("Text", asBEHAVE_FACTORY, "Text@ f(const int, const int)", asFUNCTION(glhckTextNew), asCALL_CDECL);
  engine->RegisterObjectBehaviour("Text", asBEHAVE_ADDREF, "void f()", asFUNCTION(glhckTextRef), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectBehaviour("Text", asBEHAVE_RELEASE, "void f()", asFUNCTION(glhckTextFree), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Text", "uint setFont(const ::string &in)", asFUNCTION(setTextFont), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Text", "void setColor(const uint8, const uint8, const uint8, const uint8)", asFUNCTION(glhckTextColor), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Text", "float stash(const uint, const float, const float, const float, const ::string)", asFUNCTION(stashText), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Text", "void draw()", asFUNCTION(glhckTextRender), asCALL_CDECL_OBJFIRST);
  engine->RegisterObjectMethod("Text", "void clear()", asFUNCTION(glhckTextClear), asCALL_CDECL_OBJFIRST);

  engine->RegisterGlobalFunction("Object@ createTextObject(Text@, const uint8, const float, const ::string &in, const TextureParameters &in)", asFUNCTION(createTextObject), asCALL_CDECL);

  engine->SetDefaultNamespace(previousNameSpace.data());

  return 0;
}

namespace
{
  glhckTexture* createTexture(std::string const& filename, const glhckImportImageParameters &importParameters, const glhckTextureParameters &parameters)
  {
    return glhckTextureNew(filename.data(), &importParameters, &parameters);
  }

  glhckObject* createModel(std::string const& filename, float const size, const glhckImportModelParameters &params)
  {
    return glhckModelNew(filename.data(), size, &params);
  }

  glhckObject* createTextObject(glhckText *text, unsigned int const font, float const size, std::string const& str, const glhckTextureParameters &parameters)
  {
    return glhckTextPlane(text, font, size, str.data(), &parameters);
  }

  float stashText(glhckText *text, unsigned int const font_id, float const size, float const x, float const y, std::string const& s)
  {
    float width = 0.0f;
    glhckTextStash(text, font_id, size, x, y, s.data(), &width);
    return width;
  }

  unsigned int setTextFont(glhckText *text, std::string const& filename)
  {
    return glhckTextNewFont(text, filename.data());
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

  void createColor(void* memory, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  {
    glhckColorb* color = static_cast<glhckColorb*>(memory);
    *color = {r, g, b, a};
  }
}
