#pragma once

#include"point.h"

#include<vector>
#include<glm/vec2.hpp>

class Point;

struct ClothConfig {
	float K; // Fj�derns styvhet
	float L0; // Fj�rderns vilol�ngd
};

class Cloth {
public:
	// Constructs the cloth 
	Cloth(ClothConfig _config, unsigned int _gridSize);

	// Updates each point in the cloth
	void Update(float dt);

	// Draws the cloth!
	void Draw();

private:
	void CreateGridPoints();
	void UpdateIndicesBuffer();
	void UpdateVertexBuffer();

private:
	unsigned int gridSize;
	ClothConfig clothConfig;
	std::vector<Point> gridPoints; // All the points making up the grid

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	unsigned int index_count;

};