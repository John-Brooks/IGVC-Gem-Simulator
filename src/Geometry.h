#pragma once

struct Point {
    double x,y;
};
struct Line {
    Point p1, p2;
}
struct Rect {
    point p1, p2;
};
struct Object
{
    std::vector< std::pair< Point, Point > > lines;

    Object(const Rect& rect);
    Object(const Line& line);
}


