#ifndef materialH
#define materialH

#include "rayh.h"
#include "hitTable.h"


//AO sampling
vec3 aoPoints() {
	vec3 point;
	do {
		point = 2.0 * vec3(rand() / (double)RAND_MAX, rand() / (double)RAND_MAX, rand() / (double)RAND_MAX) - vec3(1, 1, 1);
	} while (point.squared_length() >= 1.0);

	return point;
}

//reflection vector
vec3 reflect(const vec3& v, const vec3& n) {
	return (v - 2 * dot(v, n)*n);
}

struct hit_record;

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambert : public material {
public:
	lambert (const vec3& a): albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attentuation, ray& scattered) const {

		vec3 target = rec.p + rec.normal + aoPoints();
		scattered = ray(rec.p, target - rec.p);
		attentuation = albedo;

		return true;
	}

	vec3 albedo;
};

class metal : public material {
public:
	metal(const vec3& a, float f) : albedo(a) { if (f < 1) roughness = f; else roughness = 1; }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected+(roughness*aoPoints()));
		attenuation = albedo;

		return dot(scattered.direction(), rec.normal) > 0;
	}
	
	vec3 albedo;
	float roughness;

};

#endif