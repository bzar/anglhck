void main()
{
  Cube cube;
  Camera camera;
  
  camera.object.position(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();
  
  double start = time();
  double current = time();
  do
  {
    cube.rotation(0, current * 360, 0);
    cube.draw();
    render();
    current = time();
  } while(current < 5);
}
