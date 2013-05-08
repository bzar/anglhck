void main()
{
  glhck::TextureParameters textureParameters = glhck::defaultTextureParameters();
  textureParameters.wrapS = glhck::WRAP_CLAMP_TO_EDGE;
  textureParameters.wrapT = glhck::WRAP_CLAMP_TO_EDGE;
  textureParameters.wrapR = glhck::WRAP_CLAMP_TO_EDGE;
  textureParameters.minFilter = glhck::FILTER_NEAREST;
  textureParameters.magFilter = glhck::FILTER_NEAREST;

  glhck::ImportImageParameters imageParameters = glhck::defaultImportImageParameters();
  
  glhck::Texture tex("test/textures/infantry_1.png", imageParameters, textureParameters);
  glhck::Object@ sprite = glhck::createSprite(tex, 8, 8);
  glhck::Object@ child = glhck::createSprite(tex, 6, 6);
  glhck::Object@ child2 = glhck::createSprite(tex, 4, 4);
  
  @child.parent = sprite;
  @child2.parent = child;

  child.position = glhck::Vec3(10, 0, 0);
  child2.position = glhck::Vec3(10, 0, 0);
  
  glhck::Camera camera;
  camera.object.position = glhck::Vec3(25, 25, 50);
  camera.object.target = glhck::Vec3(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    sprite.rotation = glhck::Vec3(0, 0, t*360/3);
    child.rotation = glhck::Vec3(0, 0, t*360/2);
    
    sprite.draw();
    child.draw();
    child2.draw();
    render();
    current = time();
  } while(current - start < 5);
}
