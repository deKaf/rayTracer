#include "rayh.h"

int resX = 2000;
int resY = 1000;
double aspectRatio = (resX / resY);

class camera {
public:
	camera() {


		vec3 lowerLeftCorner = vec3(-2.0,-1.0,-1.0);
		vec3 horizontal = vec3(4.0, 0.0, 0.0);
		vec3 vertical = vec3(0.0, 2.0, 0.0);
		vec3 origin = vec3(0.0, 0.0, 0.0);

	}

	ray getRay(float u, float v) { 
		return ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin); 
	}
	
	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	
};

