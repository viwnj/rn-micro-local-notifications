#include "Position.h"

Position::Position(int x, int y) {
    this->x = x;
    this->y = y;
}

Position Position::operator+(Position & pos) {
	return Position(this->x + pos.x, this->y + pos.y);
}

Position Position::operator-(Position & pos) {
	return Position(this->x - pos.x, this->y - pos.y);
}