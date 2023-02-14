#pragma once

class Coord {
private:
    int x;
    int y;

public:
    Coord(int x, int y);

    [[nodiscard]] int get_x() const;
    [[nodiscard]] int get_y() const;
};