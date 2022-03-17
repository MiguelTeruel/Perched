#pragma once

struct Casilla{
	int y{0};
	int x{0};
	int parentX{0};
	int parentY{0};
	float gCost{0};
	float hCost{0}; 
	float fCost{0};
};