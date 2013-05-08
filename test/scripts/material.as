void main()
{
  glhck::ImportModelParameters modelParameters;
  modelParameters.animated = false;
  modelParameters.flatten = false;
  
  glhck::Object@ ambulance = glhck::createModel("test/models/raf22031.ctm", 4, modelParameters);
  glhck::Camera camera;
  
  glhck::Material@ material = ambulance.material;
  
  glhck::Color diffuse = material.diffuse;
  diffuse.g = 128;
  material.diffuse = diffuse;
  
  material.specular = glhck::Color(0, 255, 0, 255);
  
  camera.object.position = glhck::Vec3(25, 25, 50);
  camera.object.target = glhck::Vec3(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    ambulance.rotation = glhck::Vec3(0, t * 180, 0);
    ambulance.draw();
    render();
    current = time();
  } while(current - start < 5);
}
