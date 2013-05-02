void main()
{
  glhckTextureParameters textureParameters;
  textureParameters.minLod = -1000.0f;
  textureParameters.maxLod = 1000.0f;
  textureParameters.biasLod = 0.0f;
  textureParameters.baseLevel = 0;
  textureParameters.maxLevel = 1000;
  textureParameters.wrapS = GLHCK_WRAP_CLAMP_TO_EDGE;
  textureParameters.wrapT = GLHCK_WRAP_CLAMP_TO_EDGE;
  textureParameters.wrapR = GLHCK_WRAP_CLAMP_TO_EDGE;
  textureParameters.minFilter = GLHCK_FILTER_NEAREST;
  textureParameters.magFilter = GLHCK_FILTER_NEAREST;
  textureParameters.compareMode = GLHCK_COMPARE_NONE;
  textureParameters.compareFunc = GLHCK_COMPARE_LEQUAL;
  textureParameters.mipmap = 0;

  glhckImportImageParameters imageParameters;
  imageParameters.compression = GLHCK_COMPRESSION_NONE;

  glhckTexture tex("test/textures/infantry_1.png", imageParameters, textureParameters);

  glhckObject@ cube = createCube(1);
  @cube.texture = tex;
  
  glhckCamera camera;
  camera.object.setPosition(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    cube.yRotation = t * 360;
    cube.xScale = 1 + 15 * t / 5;
    cube.draw();
    render();
    current = time();
  } while(current - start < 5);
}
