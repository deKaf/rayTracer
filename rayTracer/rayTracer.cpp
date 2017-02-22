// Farhan Noor - raytracer basics
#include "stdafx.h"
#include <float.h>
#include "hitTableList.h"
#include "sphereObj.h"
#include "camera.h"
#include "materials.h"
#include <iostream>
#include <fstream>



vec3 color(const ray& r, hitable *world, int depth) {
	hit_record rec;

	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {

		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);

	}
}



int main() {

	const char *path = "c:\\rayTracer\\image.ppm";
	std::ofstream testFile(path);
	
	int nX = 2000;
	int nY = 1000;
	int samples = 64;
	int aspRatio = nX / nY;

	testFile << "P3\n" << nX << " " << nY << "\n255\n";

	//camera//
	//vec3 lowerLeftCorner = vec3(-(2 * aspRatio), -(aspRatio), -1.0);
	//vec3 horizontal = vec3((4 * aspRatio), 0.0, 0.0);
	//vec3 vertical = vec3(0.0, (2 * aspRatio), 0.0);
	//vec3 origin = vec3(0.0, 0.0, 0.0);

	//set list of objects
	hitable *list[7];
	
	//lambert spheres
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambert(vec3(0.0, 0.25, 0.65)) );
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambert(vec3(0.2,0.5,0.3)) );
	
	//metal sphere
	list[2] = new sphere(vec3(-1.25, 0, -1), 0.5, new metal(vec3(0.35, 1.0, 0.0), 0.05) );
	//glass sphere
	list[3] = new sphere(vec3(1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(1, 0, -1), -0.49, new dielectric(1.5));

	//small lambert spheres
	list[5] = new sphere(vec3(-0.2, -0.4, -0.2), 0.1, new lambert(vec3(1.0, 0.0, 1.0)));
	list[6] = new sphere(vec3(-0.6, -0.2, -0.2), 0.3, new metal(vec3(0.2, 0.6, 1.0), 0.2));

	hitable *world = new hitable_list(list, 7);
	
	vec3 lookFrom(3, 0.2, 3);
	vec3 lookAt(0, 0, -1);

	float distanceFocus = (lookFrom - lookAt).length();
	float aperture = 0.1;

	camera mainCam(lookFrom,lookAt, vec3(0,1,0), 30, float(nX)/float(nY), aperture, distanceFocus);
	
	for (int j = nY - 1; j >= 0; j--) {
		
		for (int i = 0; i < nX; i++) {
			
			vec3 col(0, 0, 0);

			for (int s = 0; s < samples; s++) {

				float randomNumX = rand() / (RAND_MAX+1.0);
				float randomNumY = rand() / (RAND_MAX+1.0);
				float u = float(i+randomNumX) / float(nX);
				float v = float(j+randomNumY) / float(nY);
				ray r (mainCam.getRay(u, v));
				//ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
				col += color(r, world,0);
			}

			col /= float(samples);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 *col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			//write to file
			testFile << ir << " " << ig << " " << ib << "\n";
		}
		
	}
	testFile.close();
}

