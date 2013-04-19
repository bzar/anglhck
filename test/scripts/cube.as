void main()
{
  Object o;
  double start = time();
  double current = time();
  do
  {
    o.rotation(0, current * 360, 0);
    o.draw();
    swap();
    current = time();
  } while(current < 5);
}
