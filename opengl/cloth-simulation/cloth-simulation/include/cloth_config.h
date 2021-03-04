#pragma once

#include<memory>
#include<vector>

class ExternalForce;

struct ClothConfig {
	float K; // Fj�derns styvhet
	float L0; // Fj�rderns vilol�ngd
	float g; // Gravity
	float cd; // Damp
	float mass; // mass of each individual point
	std::vector<ExternalForce*> externalForces;
};