#pragma once
#include <vector>
#include "Color.h"
#include "ColorsEnum.h"
#include "NumbersKeyEnum.h"

class Pallete {
private :
	Color actualColor;
	std::vector <Color> pallete;

public :
	Pallete();

	Color getActualColor();

	void processColorInput(int key);
	void changeActualColor(int index);
};
