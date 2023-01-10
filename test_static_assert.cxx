
class Base {
public:
  virtual void f(int index) = 0;
};

class Derived : public Base {
public:
  void f(const int index) override {
    static_assert(index == 0, "index must be 0");
  }
};

int main() {
  Derived d;
  d.f(0);
}