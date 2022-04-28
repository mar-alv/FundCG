#include "Pallete.h"

Pallete::Pallete() {
	Color red = Color(1.0, 0.0, 0.0);
	Color green = Color(0.0, 1.0, 0.0);
	Color blue = Color(0.0, 0.0, 1.0);
	Color white = Color(1.0, 1.0, 1.0);
	Color yellow = Color(1.0, 1.0, 0.0);
	Color orange = Color(1.0, 0.65, 0.0);
	Color purple = Color(0.5, 0.0, 0.5);
	Color black = Color(0.0, 0.0, 0.0);
	Color pink = Color(1.0, 0.08, 0.58);
	Color cyan = Color(0.0, 1.0, 1.0);

	this->pallete.push_back(white);
	this->pallete.push_back(red);
	this->pallete.push_back(green);
	this->pallete.push_back(blue);
	this->pallete.push_back(yellow);
	this->pallete.push_back(orange);
	this->pallete.push_back(purple);
	this->pallete.push_back(black);
	this->pallete.push_back(pink);
	this->pallete.push_back(cyan);

	this->actualColor = white;
}

Color Pallete::getActualColor() {
	return this->actualColor;
}

void Pallete::processColorInput(int key) {
	switch (key) {
		case NumbersKeyEnum::ZERO:
			changeActualColor(ColorsEnum::WHITE);
			break;
		case NumbersKeyEnum::ONE:
			changeActualColor(ColorsEnum::RED);
			break;
		case NumbersKeyEnum::TWO:
			changeActualColor(ColorsEnum::GREEN);
			break;
		case NumbersKeyEnum::THREE:
			changeActualColor(ColorsEnum::BLUE);
			break;
		case NumbersKeyEnum::FOUR:
			changeActualColor(ColorsEnum::YELLOW);
			break;
		case NumbersKeyEnum::FIVE:
			changeActualColor(ColorsEnum::ORANGE);
			break;
		case NumbersKeyEnum::SIX:
			changeActualColor(ColorsEnum::PURPLE);
			break;
		case NumbersKeyEnum::SEVEN:
			changeActualColor(ColorsEnum::BLACK);
			break;
		case NumbersKeyEnum::EIGHT:
			changeActualColor(ColorsEnum::PINK);
			break;
		case NumbersKeyEnum::NINE:
			changeActualColor(ColorsEnum::CYAN);
			break;
	}
}

void Pallete::changeActualColor(int index) {
	actualColor = pallete.at(index);
}
