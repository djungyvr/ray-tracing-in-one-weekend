#include "vec3.h"
#include "ppm.h"

#include <iostream>

int main() {
	vec3 v1{1, 0, 0};
	vec3 v2{0, 0, 1};
	std::cout << +v1 << std::endl;
	std::cout << -v1 << std::endl;
	std::cout << cross(v1, v2) << std::endl;
}
