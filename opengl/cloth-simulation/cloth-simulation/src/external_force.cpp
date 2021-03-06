#include"../include/external_force.h"

#include<cmath>
#include<glm/glm.hpp>
#include<iostream>

glm::vec3 SinusWind::getForce(float time, const Point& point)
{
	// @TODO: Add some random strength, up to 1% of the strength is added

	float noiseStrengthx =  (rand() / (RAND_MAX / (0.01 * strength)));
	float noiseStrengthy =  (rand() / (RAND_MAX / (0.01 * strength)));
	float noiseStrengthz =  (rand() / (RAND_MAX / (0.01 * strength)));
	
    glm::vec3 temp = { direction.x + noiseStrengthx, direction.y + noiseStrengthy, direction.z + noiseStrengthz };
	return point.normal * glm::dot(point.normal, temp) * strength;

	
}
	