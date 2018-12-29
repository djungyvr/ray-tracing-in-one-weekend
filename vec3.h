#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

/*
 * vec3 represents geometric vectors and colors
 * Since functions defined in class I think it's implicitly inlined
 */

class vec3 {
	public:
		vec3() : e{0, 0, 0} {};
		vec3(float e1, float e2, float e3) : e{e1, e2, e3} {};
		float x() const { return e[0]; };
		float y() const { return e[1]; };
		float z() const { return e[2]; };

		float r() const { return e[0]; };
		float g() const { return e[1]; };
		float b() const { return e[2]; };

		float e1() const { return e[0]; };
		float e2() const { return e[1]; };
		float e3() const { return e[2]; };

		void e1(float v) { e[0] = v; };
		void e2(float v) { e[1] = v; };
		void e3(float v) { e[2] = v; };

		const vec3& operator+() const { return *this; };
		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); };
		float operator[](int i) const {
			if (i < 0 || i > 2)
				throw std::out_of_range("i out of range");
			return e[i];
		};
		float& operator[](int i) {
			if (i < 0 || i > 2)
				throw std::out_of_range("i out of range");
			return e[i];
		};

		vec3& operator+=(const vec3& v) {
			e[0] += v.e1();
			e[1] += v.e2();
			e[2] += v.e3();
			return *this;
		}
		vec3& operator-=(const vec3& v) {
			return operator+=(-v);
		}

		vec3& operator*=(float s) {
			e[0] *= s;
			e[1] *= s;
			e[2] *= s;
			return *this;
		}

		vec3& operator /=(float s) {
			e[0] /= s;
			e[1] /= s;
			e[2] /= s;
			return *this;
		}

		float norm() const {
			return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
		}

		float squaredNorm() const {
			return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
		}

	private:
		float e[3];
};

// streams
inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
	os << v.e1() << ' ' << v.e2() << ' ' << v.e3();
	return os;
}
inline std::istream& operator>>(std::istream& is, vec3& v) {
	float e1, e2, e3;
	is >> e1 >> e2 >> e3;
	v.e1(e1);
	v.e2(e2);
	v.e3(e3);
	return is;
}

// scalar product
inline vec3 operator*(float s, const vec3& v) {
	return vec3(s*v.e1(), s*v.e2(), s*v.e3());
}
inline vec3 operator*(const vec3& v, float s) {
	return vec3(s*v.e1(), s*v.e2(), s*v.e3());
}

// adding and subtracting vectors
inline vec3 operator+(const vec3& v1, const vec3& v2) {
	return vec3(v1.e1() + v2.e1(), v1.e2() + v2.e2(), v1.e3() + v2.e3());
}
inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return operator+(v1, -v2);
}

// inner and cross products
inline float inner(const vec3& v1, const vec3& v2) {
	return v1.e1()*v2.e1() + v1.e2()*v2.e2() + v1.e3()*v2.e3();
}
inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3(
		v1.e2()*v2.e3() - v1.e3()*v2.e2(),
		v1.e3()*v2.e1() - v1.e1()*v2.e3(),
		v1.e1()*v2.e2() - v1.e2()*v2.e1()
	);
}
