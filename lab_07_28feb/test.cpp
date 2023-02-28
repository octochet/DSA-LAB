#include<iostream>
#include<queue>

using namespace std;

#define MAX 100

class lineSegment {
    int x1,x2,y1,y2,orientation;
public:
    //constructor
    lineSegment(int _x1, int _y1, int _x2, int _y2, int _orientation) {
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
        orientation = _orientation;
    }

    //default constructor
    lineSegment() = default;

    //first pair(x1,y1) is always having smaller x coord
    void lesser() {
        if(x1>x2) {
            swap(x1,x2);
            swap(y1,y2);
        }
        return;
    }
    
    bool operator<(const lineSegment& other) const {
        return x1 > other.x1;
    }
};

int isHorizontal(int x1, int y1, int x2, int y2) {
    if(x1==x2) return 1;
    return 0;
}

int main() {
    //defining enum orientation
    enum Orientation {Vertical, Horizontal};
    int x1,y1,x2,y2,orientation,i=0;
    lineSegment lines[MAX];
    priority_queue<lineSegment> pq;
    while(i<3) {
        cin>>x1>>y1>>x2>>y2;
        orientation=isHorizontal(x1, y1, x2, y2);
        lines[i] = lineSegment(x1,y1,x2,y2,orientation);i++;
        pq.push(lines[i]);
    }
    
    return 0;
}