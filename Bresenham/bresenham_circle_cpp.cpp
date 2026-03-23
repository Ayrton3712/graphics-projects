#include <iostream>
#include <vector>

using namespace std;

class Points{
    public:
        float x, y;

        Points(float x, float y){
            this -> x = x;
            this -> y = y;
        }

        void displayPoint(){
            cout << "(" << this -> x << ", " << this -> y << ")\n";
        }
};

void BresenhamCircle(float x0, float r, vector<Points>& points){
    // Calculating decision parameter
    float P = 3 - (2 * r);

    // Declaring variables to be used in the algorithm
    float next_x = x0, next_y = r;
    
    // Pushing initial point
    points.push_back(Points(x0, r));

    // Quad 1
    int i = 1; // Counter
    while (!(next_x >= next_y || next_x == next_y)){
        // Checking decision parameter and performing corresponding operations
        if (P < 0){
            next_x = next_x + 1;

            points.push_back(Points(next_x, next_y));

            P = P + (4 * next_x) + 6;
        }
        else{
            next_x = next_x + 1;
            next_y = next_y - 1;

            points.push_back(Points(next_x, next_y));

            P = P + (4 * (next_x - next_y)) + 10;
        }
        
        cout << "Iteration " << i << ": " << "Next x: " << next_x << ", Next y: " << next_y << endl;
        ++i;
    }
    points.pop_back(); // Removing the extra point pushed
    
    // One octal completed

    // Traversing the vector in reverse order to mirror points for octal
    for (int i = points.size() - 1; i >= 0; i--) {
        points.push_back(Points(points[i].y, points[i].x));
    }
    
    // Quad 1 completed

    int points_in_quad1 = points.size();
    
    // Quad 2
    for (int i = 0; i < points_in_quad1; i++){
        points.push_back(Points(points[i].x, -points[i].y));
    }

    // Quad 3
    for (int i = 0; i < points_in_quad1; i++){
        points.push_back(Points(-points[i].x, -points[i].y));
    }

    // Quad 4
    for (int i = 0; i < points_in_quad1; i++){
        points.push_back(Points(-points[i].x, points[i].y));
    }
}

int main(){
    vector<Points> points;
    
    BresenhamCircle(0, 6, points);

    for (Points s : points){
        s.displayPoint();
    }

    return 0;
}