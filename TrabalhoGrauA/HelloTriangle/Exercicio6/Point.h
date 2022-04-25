#pragma once

class Point {
private:
	float x;
	float y;
	float z;
	float initialX;
	float initialY;

public:
	Point(float x, float y, float z);

	Point();

	float getX();
	float getY();
	float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	float* getPoints();

	float getInitialX();
	float getInitialY();

	void increaseX();
	void increaseY();
	void increaseZ();

	void initializateX();
	void initializateY();
};
