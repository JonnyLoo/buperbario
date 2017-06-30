#include "Unit.hpp"

Unit::Unit(sf::Sprite s) {
	sprite = s;
}

sf::Sprite Unit::getSprite() {
	return sprite;
}

void Unit::turn() {
	sprite.setScale(-1, 1);
}

void updatePosition() {
	sprite.move(xVel, yVel);
}

bool onGround(std::vector<sf::Sprite> tiles) {
	return false;
}