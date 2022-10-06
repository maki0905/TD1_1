#pragma once
struct Vector2f {
	float x;
	float y;
};
struct Vector2i {
	int x;
	int y;
};

struct Circle {
	Vector2f possition;
	Vector2f velocity;
	Vector2f width;
	int isactive;
};

Circle player{
	{100, 100},
	{5, 5},
	{50, 50},
	0
};

Circle circle[10]{
	{0, 0},
	{0, 0},
	{0, 0},
	0
};

Vector2i mausepossition{
	0, 0
};

