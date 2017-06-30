#include <SFML/Graphics.hpp>

#ifndef UNIT_HPP
#define UNIT_HPP


class Unit {

public:
	Unit(sf::Sprite sprite);
	sf::Sprite getSprite();
	void turn();
	void updatePosition();
	bool onGround(std::vector<sf::Sprite> tiles);

	sf::Sprite sprite;
	float xVel;
	float yVel;
	float xAccel;
	float xMax;

protected:

};

#endif