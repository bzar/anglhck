void main()
{
  glhck::Text text(512, 128);
  text.color = glhck::Color(192, 128, 28, 255);
  uint font = text.setFont("test/fonts/DejaVuSans.ttf");

  double start = time();
  do
  {
    float textWidth = text.stash(font, 64, -400 + time() * 800/3, 240, "Hello World!");
    text.draw();
    render();
    text.clear();
  } while(time() - start < 5);
}
