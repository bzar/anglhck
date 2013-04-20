void main()
{
  Object@ cube = createCube(1);
  Camera camera;
  
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
