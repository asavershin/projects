#include <iostream>
#include "rgbimage.h"

const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000



struct Rectangle {
    int x_max;
    int y_max;
    int x_min;
    int y_min;
    
    Rectangle(int x_max_, int y_max_, int x_min_, int y_min_) : x_max(x_max_), y_max(y_max_), x_min(x_min_), y_min(y_min_) {}

    int computeCode(double x, double y)
    {
        
        int code = INSIDE;

        if (x < x_min) 
            code |= LEFT;
        else if (x > x_max) 
            code |= RIGHT;
        if (y < y_min) 
            code |= BOTTOM;
        else if (y > y_max) 
            code |= TOP;

        return code;
    }

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

    void cohenSutherlandClip(double x1, double y1, double x2, double y2, rgbImg& img) {
        
        int code1 = computeCode(x1, y1);
        int code2 = computeCode(x2, y2);
        
        if (!(code1 & code2)) {
            while ((code1 | code2) && !(code1 & code2)) {

                if (code1 == INSIDE) { // т.е. A внутри
                    // меняем координаты местами, чтобы A всегда лежала снаружи
                    std::swap(x1, x2);
                    std::swap(y1, y2);
                    std::swap(code1, code2);
                }
                if (code1 & LEFT) // т.е. A лежит слева
                {
                    
                    y1 += (y2 - y1) * (x_min - x1) / (x2 - x1);
                    x1 = x_min;
                }
                else if (code1 & TOP) // т.е. A лежит сверху
                {
                    x1 += (x2 - x1) * (y_max - y1) / (y2 - y1);
                    y1 = y_max;
                }
                else if (code1 & RIGHT) // т.е. A лежит справа
                {
                    y1 += (y2 - y1) * (x_max - x1) / (x2 - x1);
                    x1 = x_max;
                }
                else if (code1 & BOTTOM) // т.е. A лежит снизу
                {
                    x1 += (x2 - x1) * (y_min - y1) / (y2 - y1);
                    y1 = y_min;
                }
                code1 = computeCode(x1, y1);
            }
            Bresenham(x1, y1, x2, y2, img);
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        return 2;
    }

    try {
        int x, y, x1, y1, x2, y2;
        inFile >> x >> y;
        rgbImg img(x, y);
        inFile >> x1 >> y1 >> x2 >> y2;

        Rectangle rec(x2, y2, x1, y1);

        while (inFile >> x1 >> y1 >> x2 >> y2) {
            rec.cohenSutherlandClip(x1, y1, x2, y2, img);
        }
        img.save(argv[2]);

    }
    catch (std::exception& e) {
        std::cout << "Error. " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error. " << std::endl;
    }
    inFile.close();
    return 0;
}
