void main()
{
  glhck::Text text(512, 128);
  text.color = glhck::Color(192, 128, 28, 255);
  uint font = text.setFont("test/fonts/DejaVuSans.ttf");
  uint font2 = text.setKakwafont();

  double start = time();
  do
  {
    float textWidth = text.stash(font, 64, -400 + time() * 800/3, 240, "Hello World!");
    text.stash(font2, 12, -300 + time() * 800/3, 260, "GLHCK builtin font!");
    text.draw();
    render();
    text.clear();
  } while(time() - start < 5);
}
