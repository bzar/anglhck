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
  
  glhckText text(512, 128);
  text.setColor(255, 255, 255, 255);
  uint font = text.setFont("test/fonts/DejaVuSans.ttf");

  glhckObject@ textObject = createTextObject(text, font, 64, "Hello World!", textureParameters);

  glhckCamera camera;
  camera.object.setPosition(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    textObject.x = 196 - t*100;
    textObject.draw();
    render();
    current = time();
  } while(current - start < 5);
}
