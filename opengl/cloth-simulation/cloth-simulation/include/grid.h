#pragma once

#include<vector>

class Point;

struct ClothConfig {
	float K; // Fj�derns styvhet
	float L0; // Fj�rderns vilol�ngd
};

class Cloth {
	Cloth()

	void Update(float dt);

private:
	ClothConfig clothConfig;
	std::vector<Point> gridPoints;
};