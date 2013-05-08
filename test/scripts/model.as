void main()
{
  glhck::ImportModelParameters modelParameters;
  modelParameters.animated = false;
  modelParameters.flatten = false;
  
  glhck::Object@ ambulance = glhck::createModel("test/models/raf22031.ctm", 4, modelParameters);
  glhck::Camera camera;
  
  camera.object.setPosition(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    ambulance.yRotation = t * 180;
    ambulance.draw();
    render();
    current = time();
  } while(current - start < 5);
}
