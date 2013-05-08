void main()
{
  glhck::Object@ cube = glhck::createCube(1);
  glhck::Camera camera;
  
  camera.object.position = glhck::Vec3(25, 25, 50);
  camera.object.target = glhck::Vec3(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    float t = current - start;
    cube.rotation = glhck::Vec3(0, t * 180, 0);
    cube.scale = glhck::Vec3(1 + 15 * t / 5, 1, 1);
    cube.draw();
    render();
    current = time();
  } while(current - start < 5);
}
