void main()
{
  glhck::TextureParameters textureParameters;
  textureParameters.minLod = -1000.0f;
  textureParameters.maxLod = 1000.0f;
  textureParameters.biasLod = 0.0f;
  textureParameters.baseLevel = 0;
  textureParameters.maxLevel = 1000;
  textureParameters.wrapS = glhck::WRAP_CLAMP_TO_EDGE;
  textureParameters.wrapT = glhck::WRAP_CLAMP_TO_EDGE;
  textureParameters.wrapR = glhck::WRAP_CLAMP_TO_EDGE;
  textureParameters.minFilter = glhck::FILTER_NEAREST;
  textureParameters.magFilter = glhck::FILTER_NEAREST;
  textureParameters.compareMode = glhck::COMPARE_NONE;
  textureParameters.compareFunc = glhck::COMPARE_LEQUAL;
  textureParameters.mipmap = 0;
  
  glhck::Text text(512, 128);
  text.setColor(255, 255, 255, 255);
  uint font = text.setFont("test/fonts/DejaVuSans.ttf");

  glhck::Object@ textObject = glhck::createTextObject(text, font, 64, "Hello World!", textureParameters);

  glhck::Camera camera;
  camera.object.position = glhck::Vec3(25, 25, 50);
  camera.object.target = glhck::Vec3(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    textObject.position = glhck::Vec3(196 - t*100, 0, 0);
    textObject.draw();
    render();
    current = time();
  } while(current - start < 5);
}
