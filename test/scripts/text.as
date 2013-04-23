void main()
{
  glhckText text(512, 128);
  text.setColor(255, 255, 255, 255);
  uint font = text.setFont("test/fonts/DejaVuSans.ttf");
  float textWidth = text.render(font, 40, 400, 240, "Hello World!");

  glhckCamera camera;
  camera.object.setPosition(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();

  double start = time();
  do
  {
    text.draw();
    render();
  } while(time() - start < 5);
}
