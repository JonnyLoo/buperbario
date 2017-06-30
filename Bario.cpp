#include "Bario.hpp"
#include "Unit.hpp"

Bario::Bario(sf::Sprite sprite) : Unit(sprite) {}

void changeState(int state) {
	sf::IntRect newState;

	switch (state) {
	case 0: //standing 
		newState = sf::IntRect(10, 6, 20, 22);
		break;
	case 1: //moving 1
		newState = sf::IntRect(30, 6, 20, 22);
		break;
	case 2: //moving 2
		newState = sf::IntRect(53, 5, 20, 22);
		break;
	case 4: //jumping
		newState = sf::IntRect(180, 6, 20, 22);
		break;
	default:
		newState = sf::IntRect(10, 6, 20, 22);

		sprite.setTextureRect(newState);
		return;
	}

	void jump() {
		if (onground) {

			yVel -= 25.;
			onground = false;
		}
	}

	void moveRight() {

		xVel += xAccel;
		if (xVel > xMax)
			xVel = xMax;

		count++;
		if (count == 3) {

			count = 0;
			bstate++;
			if (bstate > 2)
				bstate = 1;
		}
		changeState(bstate);
		if (sprite.getScale().x < 0)
		{
			turn();
		}
	}

	void moveLeft() {
		if (!(sprite.getPosition().x <= 15)) {

			xVel -= xAccel;
			if (xVel < -xMax)
				xVel = -xMax;
		}
		else
			xVel = 0;

		count++;
		if (count == 3) {

			count = 0;
			bstate++;
			if (bstate > 2)
				bstate = 1;
		}
		changeState(bstate);
		if (sprite.getScale().x > 0)
		{
			turn();
		}
	}

	void noInput() {
		if (xVel > 0)
			xVel--;
		else if (xVel < 0)
			xVel++;
		else
			xVel = 0;

		changeState(0);
	}