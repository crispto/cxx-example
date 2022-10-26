#include <iostream>
using namespace std;
//继承， 不含多态
class Point2D{
  private:
  int x;
  short y;
  public:
  virtual void call(){
    cout << "2d call" << endl;
  };
  void only2d(){
    cout << "2d only called " << endl;

  }
};

class Painter{
  public:
  void call(){
    cout << "painter call " << endl;
  }
};

class Point3D: public Point2D{
  public:
  int z;
  void call() override{
    std::cout << "3d calle" << std::endl;
  }
};

class Point3Dshort: public Point2D{
  public:
  short z;
};

int main(){
  cout << "size of point2d: " << sizeof(Point2D) << endl;
  cout << "size of point3d: " << sizeof(Point3D) << endl;
  cout << "size of point3dshort: " << sizeof(Point3Dshort) << endl;

  Point3D p0;
  Point3D & p = p0;
  p.call();
  p.Point2D::call(); // 多继承 父类函数重名的情况下需要在调用时精确指定哪个父类
  // p.Painter::call();
  p.only2d(); // 这里会发生强制转换，Point3D 会被转换成  Point2D
  return 0;

}