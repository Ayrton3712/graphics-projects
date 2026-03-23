#include <iostream>
#include <vector>

using namespace std;

void Bresenham(float* x1, float* y1, float* x2, float* y2) {
	float dx = *x2 - *x1;
	float dy = *y2 - *y1;
	float steps = std::max(std::abs(dx), std::abs(dy));
	float xIncrement = dx / steps;
	float yIncrement = dy / steps;
	float x = *x1;
	float y = *y1;
	for (int i = 0; i <= steps; i++) {
		std::cout << "Plotting point: (" << x << ", " << y << ")\n";
		x += xIncrement;
		y += yIncrement;
	}
}

int main(){
    float x1 = 8, y1 = 5, x2 = 12, y2 = 8;
    vector<float> points;

    Bresenham(&x1, &y1, &x2, &y2);
}