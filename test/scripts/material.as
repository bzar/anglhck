void main()
{
  glhck::ImportModelParameters modelParameters = glhck::defaultImportModelParameters();
  glhck::TextureParameters textureParameters = glhck::defaultTextureParameters();
  glhck::ImportImageParameters imageParameters = glhck::defaultImportImageParameters();
  
  glhck::Object@ ambulance = glhck::createModel("test/models/raf22031.ctm", 4, modelParameters);
  
  glhck::Texture tex("test/textures/lava.png", imageParameters, textureParameters);
  glhck::Object@ lava = glhck::createSprite(tex, 64, 64);
  lava.position = glhck::Vec3(0, -4, 0);
  lava.rotation = glhck::Vec3(-90, 0, 0);
    
  glhck::Material@ material = ambulance.material;
  
  glhck::Color diffuse = material.diffuse;
  diffuse.g = 128;
  material.diffuse = diffuse;
  
  material.specular = glhck::Color(0, 255, 0, 255);
  
  material.shininess = 0.5;
  
  glhck::Camera camera;
  camera.object.position = glhck::Vec3(25, 25, 50);
  camera.object.target = glhck::Vec3(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    ambulance.rotation = glhck::Vec3(0, t * 180, 0);
    lava.material.textureOffset = glhck::Vec2(t * 0.05, t * 0.05);
    ambulance.draw();
    lava.draw();
    render();
    current = time();
  } while(current - start < 5);
}
