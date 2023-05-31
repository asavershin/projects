#pragma once

#include "rgbimage.h"

void Bresenham(int x1, int y1, int x2, int y2, rgbImg& img) {
    RGB white{ 255, 255, 255 };
    bool k = abs(y2 - y1) > abs(x2 - x1);//y = kx
    if (k) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int d = 2 * dy - dx;
    int y = y1;
    int step = (y2 >= y1) ? 1 : -1;
    for (int x = x1; x <= x2; ++x) {
        img.get(k ? y : x, k ? x : y) = white;
        if (d < 0) {
            d += 2 * dy;
        }
        else {
            d += 2 * (dy - dx);
            y += step;
        }
    }
}
