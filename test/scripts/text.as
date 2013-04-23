void main()
{
  glhckText text(512, 128);
  text.setColor(255, 255, 255, 255);
  uint font = text.setFont("test/fonts/DejaVuSans.ttf");

  glhckCamera camera;
  camera.object.setPosition(25, 25, 50);
  camera.object.target(0, 0, 0);
  camera.update();

  double start = time();
  do
  {
    float textWidth = text.render(font, 64, -400 + time() * 800/3, 240, "Hello World!");
    text.draw();
    render();
  } while(time() - start < 5);
}
