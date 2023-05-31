#pragma once

#include "bresenham.h"
#include <vector>
#include <sstream>

class objFileProection {
	struct Dot {
		double x;
		double y;
		double z;
		Dot(std::stringstream& in) {
			in >> x >> y >> z;
		}
	};

	struct Polygon {
		std::vector <Dot*> dots;// храним указатели на точки в памяти, чтобы не дублировать два раза
		Polygon(std::stringstream &in, std::vector<Dot>& dots_) {
			for (int i; in >> i;) {
				dots.push_back(&dots_[i - 1]);
			}
		}
	};

	std::vector<Dot> dots;
	std::vector<Polygon> polygons;

	double maxX;
	double minX;
	double maxY;
	double minY;
	double maxZ;
	double minZ;

	void drawPolygonOxy(Polygon& pol, rgbImg& img) {
		//масштабирование, учитываем рабочую область, рамки нет
		double scalingX = (img.width() - 20.0) / (maxX - minX);
		double scalingY = (img.height() - 20.0) / (maxY - minY);

		//сдвиг, масштабирование, + граница  
		double x1 = (pol.dots[0]->x - minX) * scalingX + 10.0;
		double x2 = (pol.dots[1]->x - minX) * scalingX + 10.0;
		double x3 = (pol.dots[2]->x - minX) * scalingX + 10.0;

		double y1 = (maxY - pol.dots[0]->y) * scalingY + 10.0;
		double y2 = (maxY - pol.dots[1]->y) * scalingY + 10.0;
		double y3 = (maxY - pol.dots[2]->y) * scalingY + 10.0;

		Bresenham(x1, y1, x2, y2, img);
		Bresenham(x2, y2, x3, y3, img);
		Bresenham(x3, y3, x1, y1, img);

	}

	void drawPolygonOyz(Polygon& pol, rgbImg& img) {
		//масштабирование, учитываем рабочую область, рамки нет
		double scalingY = (img.width() - 20.0) / (maxY - minY);
		double scalingZ = (img.height() - 20.0) / (maxZ - minZ);

		//сдвиг, масштабирование, + граница 
		double y1 = (pol.dots[0]->y - minY) * scalingY + 10.0;
		double y2 = (pol.dots[1]->y - minY) * scalingY + 10.0;
		double y3 = (pol.dots[2]->y - minY) * scalingY + 10.0;

		double z1 = (maxZ - pol.dots[0]->z) * scalingZ + 10.0;
		double z2 = (maxZ - pol.dots[1]->z) * scalingZ + 10.0;
		double z3 = (maxZ - pol.dots[2]->z) * scalingZ + 10.0;

		Bresenham(y1, z1, y2, z2, img);
		Bresenham(y2, z2, y3, z3, img);
		Bresenham(y3, z3, y1, z1, img);

	}

	void drawPolygonOxz(Polygon& pol, rgbImg& img) {
		//масштабирование, учитываем рабочую область, рамки нет
		double scalingX = (img.width() - 20.0) / (maxX - minX);
		double scalingZ = (img.height() - 20.0) / (maxZ - minZ);

		//сдвиг, масштабирование, + граница
		double x1 = (pol.dots[0]->x - minX) * scalingX + 10.0;
		double x2 = (pol.dots[1]->x - minX) * scalingX + 10.0;
		double x3 = (pol.dots[2]->x - minX) * scalingX + 10.0;

		double z1 = (maxZ - pol.dots[0]->z) * scalingZ + 10.0;
		double z2 = (maxZ - pol.dots[1]->z) * scalingZ + 10.0;
		double z3 = (maxZ - pol.dots[2]->z) * scalingZ + 10.0;

		Bresenham(x1, z1, x2, z2, img);
		Bresenham(x2, z2, x3, z3, img);
		Bresenham(x3, z3, x1, z1, img);

	}
public:
	objFileProection(std::ifstream &inFile) {
		std::string s;
		std::string first;//используем string, чтобы игнорировать строки вида vn a b c
		
		for (std::stringstream in; std::getline(inFile, s);) {
			in.clear();
			in.str(s);
			in >> first;

			if (first == "v") {
				dots.push_back(Dot(in));
			}
			else if (first == "f") {
				polygons.push_back(Polygon(in, dots));
			}
		}
		maxX = minX = dots[0].x;
		maxY = minY = dots[0].y;
		maxZ = minZ = dots[0].z;

		for (auto& dot : dots) {

			maxX = (dot.x > maxX) ? dot.x : maxX;
			maxY = (dot.y > maxY) ? dot.y : maxY;
			maxZ = (dot.z > maxZ) ? dot.z : maxZ;

			minX = (dot.x < minX) ? dot.x : minX;
			minY = (dot.y < minY) ? dot.y : minY;
			minZ = (dot.z < minZ) ? dot.z : minZ;

		}



	}

	

	void proectionsBMP(rgbImg& objOXY, rgbImg& objOXZ, rgbImg& objOYZ) {
		for (auto& pol : polygons) {
			drawPolygonOxy(pol, objOXY);
			drawPolygonOyz(pol, objOYZ);
			drawPolygonOxz(pol, objOXZ);
		}
	}

};

