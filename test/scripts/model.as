void main()
{
  glhck::ImportModelParameters modelParameters = glhck::defaultImportModelParameters();
  glhck::Object@ ambulance = glhck::createModel("test/models/raf22031.ctm", 4, modelParameters);
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
    ambulance.draw();
    render();
    current = time();
  } while(current - start < 5);
}
