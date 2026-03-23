#pragma once

class Point{
    private:
        float x, y;

    public:
        Point(float, float);

        float getX() const;
        float getY() const;

        void setX(float);
        void setY(float);

        void displayPoint() const;
};