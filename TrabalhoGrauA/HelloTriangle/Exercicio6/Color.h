#pragma once

class Color {
private:
	float r;
	float g;
	float b;

public:
	Color(float r, float g, float b);

	Color();

	float* getPoints();

	float getR();
	float getG();
	float getB();
};
