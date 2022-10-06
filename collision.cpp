#include <stdio.h>
int circlecollision(float x1, float y1, float w1, float x2, float y2, float w2) {
	float a = x1 - x2;
	float b = y1 - y2;
	float c = w1 + w2;
	if ((a * a) + (b * b) <= c * c) {
		return 1;
	}
	else {
		return 0;
	}
}