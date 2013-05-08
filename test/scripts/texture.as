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

  glhck::ImportImageParameters imageParameters;
  imageParameters.compression = glhck::COMPRESSION_NONE;

  glhck::Texture tex("test/textures/infantry_1.png", imageParameters, textureParameters);

  glhck::Object@ cube = glhck::createCube(1);
  @cube.material = glhck::Material(tex);
  
  glhck::Camera camera;
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
