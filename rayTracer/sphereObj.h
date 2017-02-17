#ifndef sphereObjH
#define sphereObjH
#include "hitTable.h"


class sphere : public hitable {

public:
	
	sphere() {}
	sphere(vec3 c, float r, material *m) : center(c), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray& ray, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material *mat_ptr;
};

bool sphere::hit(const ray& ray, float t_min, float t_max, hit_record& rec) const {
	
	vec3 oc = ray.origin() - center;
	float a = dot(ray.direction(), ray.direction());
	float b = dot(oc, ray.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b*b - a*c;

	if (discriminant > 0) {
		float temp = (-b - sqrt(b*b - a*c)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		
		temp = (-b + sqrt(b*b - a*c)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;

		}
	}
	return false;
	}
#endif