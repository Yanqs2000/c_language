#include <iostream>
#include <string>
using namespace std;

class Point{
public:
    int x, y;
    Point(int i = 0, int j = 0){
        x = i;
        y = j;
    }

    const int getX() const{
        return x;
    }
    const int getY() const{
        return y;
    }
};

int main(){
    const Point p1;
    cout << "p1: (" << p1.getX() << ", " << p1.getY() << ")" << endl;

    return 0;
}