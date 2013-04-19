#include "glhck/glhck.h"

namespace anglhck
{
  class Object
  {
  public:
    Object(glhckObject* o) : o(o) {}
    ~Object() {glhckObjectFree(o); }
    void draw() { glhckObjectDraw(o); }
    void position(float x, float y, float z) { glhckObjectPositionf(o, x, y, z); }
    void rotation(float x, float y, float z) { glhckObjectRotationf(o, x, y, z); }

  private:
    glhckObject* o;
  };
}
