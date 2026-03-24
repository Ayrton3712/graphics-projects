#include "boundary_filling_algorithm.h"
#include "bresenham_circle.h"

#include <iostream>

std::vector<Point> boundary_filling_algorithm(
    const Point& start,
    GLfloat fillColor[4],
    const unsigned int WIDTH,
    const unsigned int HEIGHT,
    const std::vector<Point>& boundary)
{
    const int halfW = WIDTH / 2;
    const int halfH = HEIGHT / 2;

    // Flat grids
    std::vector<uint8_t> boundaryGrid(WIDTH * HEIGHT, 0);
    std::vector<uint8_t> visited(WIDTH * HEIGHT, 0);

    auto index = [&](int x, int y) {
        return y * WIDTH + x;
        };

    // ---- BUILD & THICKEN BOUNDARY ----
    for (const auto& p : boundary) {
        int x = (int)p.getX() + halfW;
        int y = (int)p.getY() + halfH;

        if (x < 0 || x >= (int)WIDTH || y < 0 || y >= (int)HEIGHT)
            continue;

        // Mark center
        boundaryGrid[index(x, y)] = 1;

        // Thicken boundary (4-neighbors)
        if (x + 1 < (int)WIDTH)  boundaryGrid[index(x + 1, y)] = 1;
        if (x - 1 >= 0)          boundaryGrid[index(x - 1, y)] = 1;
        if (y + 1 < (int)HEIGHT) boundaryGrid[index(x, y + 1)] = 1;
        if (y - 1 >= 0)          boundaryGrid[index(x, y - 1)] = 1;
    }

    // ---- STACK ----
    std::vector<std::pair<int, int>> stack;
    stack.reserve(WIDTH * HEIGHT / 4);

    int startX = (int)start.getX() + halfW;
    int startY = (int)start.getY() + halfH;

    stack.emplace_back(startX, startY);

    // ---- RESULT ----
    std::vector<Point> fill;
    fill.reserve(WIDTH * HEIGHT / 4);

    // ---- FLOOD FILL (8-CONNECTED) ----
    while (!stack.empty()) {
        auto [x, y] = stack.back();
        stack.pop_back();

        // Bounds
        if (x < 0 || x >= (int)WIDTH || y < 0 || y >= (int)HEIGHT)
            continue;

        int idx = index(x, y);

        // Skip visited or boundary
        if (visited[idx] || boundaryGrid[idx])
            continue;

        visited[idx] = 1;

        // Convert back to centered coordinates
        fill.emplace_back((GLfloat)(x - halfW), (GLfloat)(y - halfH));

        // ---- 8-CONNECTED NEIGHBORS ----
        stack.emplace_back(x + 1, y);
        stack.emplace_back(x - 1, y);
        stack.emplace_back(x, y + 1);
        stack.emplace_back(x, y - 1);

        stack.emplace_back(x + 1, y + 1);
        stack.emplace_back(x - 1, y - 1);
        stack.emplace_back(x + 1, y - 1);
        stack.emplace_back(x - 1, y + 1);
    }

    return fill;
}