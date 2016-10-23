#include <cstdio>

struct PointS {
  int x, y;
};

class PointC {
public:
  PointC(int ix, int iy) {
    x = ix; y = iy;
  };
  ~PointC() {};
  int x, y;
};

PointC* SomeInit0() {
  PointC p0(3, 4);
  return &p0; // warning -Wreturn-local-addr
}

PointC* SomeInit1() {
  PointC p0(3, 4);
  PointC* addr = &p0; // TODO: what's happening here??
  return addr;
}

int main() {
  // struct allocation on stack
  struct PointS p = { 2, 3 };
  {
    p = { 3, 4 };
    printf("p: %d\n", p.x + p.y); // 7
  }
  printf("p: %d\n", p.x + p.y); // 7

  // object allocation on heap (memory leaks unless `delete`)
  PointC* q = new PointC(2, 3);
  {
    q = new PointC(3, 4);
    printf("q: %d\n", q->x + q->y); // 7
  }
  printf("q: %d\n", q->x + q->y); // 7

  // object allocation on heap
  PointC* r0;
  {
    PointC* r1 = new PointC(2, 3); // leaks
    r0 = r1;
    printf("r0: %d\n", r0->x + r0->y); // 5
    printf("r1: %d\n", r1->x + r1->y); // 5
  }
  printf("r0: %d\n", r0->x + r0->y); // 5

  // object allocation on stack
  PointC s0(2, 3);
  {
    PointC s1(3, 4); // cleared when s1 leaves scope (not really)
    s0 = s1;
    printf("s0: %d\n", s0.x + s0.y); // 7
    printf("s1: %d\n", s1.x + s1.y); // 7
  }
  printf("s0: %d\n", s0.x + s0.y); // 7 (somehow s1's information lives) (undefined behaviour from language spec)

  // object allocation on stack
  PointC* t0;
  {
    PointC t1(3, 4); // cleared when s1 leaves scope (not really)
    t0 = &t1;
    printf("t0: %d\n", t0->x + t0->y); // 7
    printf("t1: %d\n", t1.x + t1.y); // 7
  }
  printf("t0: %d\n", t0->x + t0->y); // 7 (somehow s1's information lives)

  // object allocation on stack inside of other function
  PointC* u0 = SomeInit1();
  printf("u0: %d\n", u0->x + u0->y); // somehow ok

  // object allocation
  PointC* v0 = SomeInit0();
  printf("v0: %d\n", v0->x + v0->y); // of course, Segmentation fault

  return 0;
}
