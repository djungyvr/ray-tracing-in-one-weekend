/*
 * Render an image by writing a PPM file
 * The file looks like
 * P3
 * 3 2
 * 255
 * 255 0 0 0 255 0 0 0 255
 * 255 0 0 0 255 0 0 0 255
 * * The P3 means the colours are in ASCII
 * With 3 columns and 2 rows
 * Each RGB value maxed out at 255
 */

#include <iostream>
#include <cassert>
#include <string>

void writePPMHeader(std::ostream& file, int width, int height) {
	file << "P3" << '\n';
	file << width << ' ' << height << '\n';
	file << 255 << '\n';
}

void draw(std::ostream& file, int width, int height, const std::string& drawing) {
	if (width * height != drawing.length()) {
		throw std::invalid_argument("width * height != length of drawing");
	}
	writePPMHeader(file, width, height);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			char color = drawing.at(width*i + j);
			switch(color) {
				case 'R':
					file << "255 0 0";
					break;
				case 'G':
					file << "0 255 0";
					break;
				case 'B':
					file << "0 0 255";
					break;
				default:
					file << "0 0 0";
					break;
			}
			file << '\n';
		}
	}
}

void drawGradient(std::ostream& file, int width, int height) {
	writePPMHeader(file, width, height);

	// Gets less green as we go down
	for (int i = height - 1; i >= 0; --i) {
		// Gets more red as we go right
		for (int j = 0; j < width; ++j) {
			float r {float(j) / float(width)};
			float g {float(i) / float(height)};
			float b {0.2};

			int ir = int(255.9*r);
			int ig = int(255.9*g);
			int ib = int(255.9*b);

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
}

int main() {
	// draw(std::cout, 2, 2, "RGBR");
	drawGradient(std::cout, 100, 100);
}
