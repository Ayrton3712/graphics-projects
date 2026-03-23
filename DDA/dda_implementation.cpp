// NOTE: Must account for when the first point entered is to the right of the second point, if that happens now, getIntermediatePoints doesn't work
#include <iostream>

using namespace std;

// function to get the y coordinate from the point-slope equation
float getYCoordinate(float y1, float x, float x1, float m){
    return (y1 + (m * (x - x1)));
}

// function to compute and print intermediate points
void getIntermediatePoints(float initial_point_x, float initial_point_y, float end_point_x, float end_point_y, float m){
    // If x coordinates are the same, the line is vertical
    if (initial_point_x == end_point_x){
        float x_coord = initial_point_x = end_point_x;

        // Looping through y coordinates, no need to shift x as it remains the same
        for (float i = initial_point_y + 1, j = 1; i < end_point_y; i++, j++){
            cout << "Intermediate point " << j << ": (" << x_coord << ", " << i << ")\n";
        }
    }
    // If the x coordinates are not the same, the line is not vertical and the algorithm continues normally
    else{
        // Looping through x coordinates from initial's to end's
        for (float i = initial_point_x + 1, j = 1; i < end_point_x; i++, j++){
                
                // Compute current intermediate y coordinate
                float intermediate_y = getYCoordinate(initial_point_y, i, initial_point_x, m);
                
                cout << "Intermediate point " << j << ": (" << i << ", " << intermediate_y << ")\n";
            }
    }
}

int main(){
    // Declaring all necessary variables as floats
    float x1, x2,
          y1, y2,
          dx, dy,
          m,
          initial_point_x, initial_point_y,
          end_point_x, end_point_y;

    // Getting user input for points
    cout << "Enter x1 and y1: ";
    cin >> x1 >> y1;

    cout << "Enter x2 and y2: ";
    cin >> x2 >> y2;

    cout << "Points entered:\n"
         << "(" << x1 << ", " << y1 << ")\n"
         << "(" << x2 << ", " << y2 << ")\n";

    // Computing differentials
    dx = x1 - x2;
    dy = y1 - y2;

    // Computing slope, checking if dx is 0 first
    if (dx == 0){
        cout << "Note: The points form a vertical line.\n";
        m = 0;
    }
    else{
        m = dy / dx;
    }

    // Setting initial point coordinates
    initial_point_x = x1;
    initial_point_y = y1;

    // Setting end point coordinates
    end_point_x = x2;
    end_point_y = y2;

    getIntermediatePoints(initial_point_x, initial_point_y, end_point_x, end_point_y, m);

    return 0;
}