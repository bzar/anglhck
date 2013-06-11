void main()
{
  glhck::TextureParameters textureParameters = glhck::defaultTextureSpriteParameters();
  glhck::ImportImageParameters imageParameters = glhck::defaultImportImageParameters();
  glhck::Texture tex("test/textures/infantry_1.png", imageParameters, textureParameters);
  glhck::Object@ sprite = glhck::createSprite(tex, 8, 8);
  glhck::Object@ child = glhck::createSprite(tex, 6, 6);
  glhck::Object@ child2 = glhck::createSprite(tex, 4, 4);
  
  @child.parent = sprite;
  @child2.parent = child;
  child2.parentAffection = glhck::AFFECT_TRANSLATION | glhck::AFFECT_ROTATION | glhck::AFFECT_SCALING;

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
    child.scale = glhck::Vec3(1.0/t+1.0, 1.0/t+1.0, 1.0);
    
    sprite.draw();
    sprite.children[0].draw();
    sprite.children[0].children[0].draw();
    render();
    current = time();
  } while(current - start < 5);
}
