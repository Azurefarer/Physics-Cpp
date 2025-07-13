#include "gl_core/pipeline.h"
#include <stdexcept>
#include <utility>

double radian(double degrees) {
    return degrees * std::numbers::pi / 180;
}

float frac(float x) {
    float intPart;
    return std::modf(x, &intPart); // Returns the fractional part
}

// though this is not random at all, it does a good job at hiding it
// it is not often that you'd be looking in the same direction twice
// in 3d.  Maybe this is considered random because the mapping has no
// Physical meaning/Logic.  e.g. why choose 512 instead of 256, or any
// of these hard-coded numbers for that matter.
glm::vec3 random3(glm::vec3 c) { 
	float j = 4096.0*sin(glm::dot(c,glm::vec3(17.0, 59.4, 15.0)));
	glm::vec3 r;
	r.z = frac(512.0*j);
	j *= .125;
	r.x = frac(512.0*j);
	j *= .125;
	r.y = frac(512.0*j);
	return r + r - glm::vec3(1.0);
}


void Diagnostics_print() {
    
}
