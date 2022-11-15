#include <iostream>
#include <vector>

using namespace std;

class A
{
};
class B : public virtual A
{
};
class C : public virtual A
{
};
class D : public B, public C
{
};

class Point2d
{
public:
        Point2d(float x = 0.0, float y = 0.0) : _x(x), _y(y)
        {
        }
        float x()
        {
                return _x;
        }
        float y()
        {
                return _y;
        }
        void x(float newX)
        {
                _x = newX;
        }
        void y(float newY)
        {
                _y = newY;
        }
        void operator += (const Point2d &rhs){
                _x += rhs.x();
                _y += rhs.y();
        } 

protected:
        float _x;
        float _y;
};
class Point3d : virtual public Point2d
{
public:
        float z;
};


int main()
{
       
}