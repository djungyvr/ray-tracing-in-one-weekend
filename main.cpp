#include "ray.h"
#include <iostream>
#include <cmath>

float hitSphere(const vec3& center, const ray& r, float radius) {
	// recall eqn of sphere at origin 0 given by <v, v> = r^2
	// where v is a vector [x,y,z]
	// and with an origin that is offset by u
	// <v-u, v-u> = r^2
	// this results in
	// to see if a ray p *hits* the sphere
	// we simply insert v as p
	// <p-u, p-u> = r^2
	// <tB + A - C, tB + A - C> = r^2
	// t^2*<B, B> + 2*t<B, A - C> + <A-C, A-C> - r^2 = 0
	// The following has a soln if the descriminant b^2 - 4ac is greater than 0
	vec3 oc {r.origin() - center};

	float a = inner(r.direction(), r.direction());
	float b = 2.0*inner(oc, r.direction());
	float c = inner(oc, oc) - radius*radius;
	float discriminant {b*b - 4*a*c};
	if (discriminant < 0) {
		return -1.0;
	}
	return (-b - std::sqrt(discriminant) / (2.0*a));
}


// Given a ray returns a color
// based on the magnitude of the y direction
vec3 color(const ray& r) {
	float t = hitSphere(vec3(0,0,-1), r, 0.5);
	if (t > 0.0) {
		vec3 N = (r.pointAt(t) - vec3(0,0,-1)).unit();
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unitDir = r.direction().unit();
	// In this case t is dependent on the
	// y direction
	// this y direction has been shifted so we go
	// from range [-1,1] to [0,2]
	// which is then scaled down to [0,1]
	t = 0.5*(unitDir.y() + 1.0); // Forms a linear interpolation (lerp)
	// Basically when t = 0 we want white
	// And when t = 1 we want dominant blue,
	// hence 0.5, 0.7 1.0
	return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
	// Chapter 4
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n" << nx << ' ' << ny << "\n255\n";
	// Negative z direction is inside the screen
	vec3 llc(-2.0, -1.0, -1.0);
	vec3 htl(4.0, 0.0, 0.0);
	vec3 vtl(0.0, 2.0, 0.0);
	vec3 ogn(0.0, 0.0, 0.0);

	for (int i = ny-1; i >= 0; --i) {
		for (int j = 0; j < nx; j++) {
			float u = float(j) / float(nx);
			float v = float(i) / float(ny);
			// The horizontal component increases as u increases
			// The vertical component increases as we go
			// through the loop
			// Which is why we have strong blue
			// at the top that continuously goes across
			// since the htl vector has no blue component
			// for each value of the y-component
			ray r(ogn, llc + u*htl + v*vtl);
			vec3 clr = color(r);
			int ir = int(255.99*clr.r());
			int ig = int(255.99*clr.g());
			int ib = int(255.99*clr.b());
			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	// Chapter 1 and 2
	//draw(std::cout, 4, 4, "RRRRGGGGBBBBRRRR");
	//drawGradient(std::cout, 152, 152);
}

