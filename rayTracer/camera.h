#ifndef cameraH
#define cameraH
#define _USE_MATH_DEFINES

#include "rayh.h"
#include <math.h>

vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0* vec3( (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

class camera {
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focusDistance) {
		lensRadius = aperture / 2;
		
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		
		lowerLeftCorner = vec3(-half_width, -half_height, -1.0);
		lowerLeftCorner = origin - half_width*focusDistance*u - half_height*focusDistance*v - focusDistance*w;
		horizontal = 2*half_width*focusDistance*u;
		vertical = 2 * half_height*focusDistance*v;
	}

	ray getRay(float s, float t) { 
		
		vec3 rd = lensRadius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v*rd.y();
		return ray(origin+offset, lowerLeftCorner + s*horizontal + t*vertical - origin - offset); 
	}
	
	vec3 origin;
	vec3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lensRadius;
};

#endif