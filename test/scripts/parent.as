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
  glhckObject@ sprite = createSprite(tex, 8, 8);
  glhckObject@ child = createSprite(tex, 6, 6);
  glhckObject@ child2 = createSprite(tex, 4, 4);
  
  @child.parent = sprite;
  @child2.parent = child;

  child.x = 10;
  child2.x = 10;
  
  glhckCamera camera;
  camera.object.setPosition(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    sprite.zRotation = t*360/3;
    child.zRotation = t*360/2;
    
    sprite.draw();
    child.draw();
    child2.draw();
    render();
    current = time();
  } while(current - start < 5);
}
