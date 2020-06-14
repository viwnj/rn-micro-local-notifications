#pragma once

struct Position {
	int x, y;
	Position(int _x, int _y);
	Position operator+(Position & pos);
	Position operator-(Position & pos);
};