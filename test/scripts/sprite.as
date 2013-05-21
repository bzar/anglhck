void main()
{
  glhck::TextureParameters textureParameters = glhck::defaultTextureSpriteParameters();
  glhck::ImportImageParameters imageParameters = glhck::defaultImportImageParameters();
  glhck::Texture tex("test/textures/infantry_1.png", imageParameters, textureParameters);
  glhck::Object@ sprite = glhck::createSprite(tex, 8, 8);

  glhck::Camera camera;
  camera.object.position = glhck::Vec3(25, 25, 50);
  camera.object.target = glhck::Vec3(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    sprite.position = glhck::Vec3(-15 + t*10, 0, 0);
    sprite.draw();
    render();
    current = time();
  } while(current - start < 5);
}
