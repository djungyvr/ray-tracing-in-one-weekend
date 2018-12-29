#pragma once

#include "vec3.h"

/*
 * ray as represented is a book is a parameterized vector function
 * ie. p(t) = A + t*B
 * Where A and B are vectors, and t is some real number
 * This class will capture this notion
 */

class ray {
	public:
		ray() : A{vec3()}, B{vec3()} {};
		ray(const vec3& a, const vec3& b) : A{a}, B{b} {};
		vec3 origin() const {return A;};
		vec3 direction() const {return B;};
		vec3 pointAt(float t) const {return A + t*B;};
	private:
		vec3 A;
		vec3 B;
};
