#include "Unit.hpp"

Koopa::Koopa(sf::Texture texture, sf::RenderWindow* w, TileMap map, sf::Vector2f pos) : Unit(texture, w, map){
	startPos = pos;
	Koopa::setup();
}

void Koopa::setup() {
	animation_count = 0;
	animation_delay = 3;
	x_vel = -2;
	gravity = 1;
	state = 0;
	
	changeState(0);
	s.setScale(20 / s.getLocalBounds().width, 30 / s.getLocalBounds().height);
	s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);
	s.setPosition(startPos);
}

void Koopa::changeState(int new_state) {
	sf::IntRect sprite;

	switch (new_state) {
	case -1: //dead
		sprite = sf::IntRect(36, 0, 17, 27);
		break;
	case 0: //moving 1
		sprite = sf::IntRect(0, 0, 17, 27);
		break;
	case 1: //moving 2
		sprite = sf::IntRect(18, 0, 17, 27);
		break;
	default:
		sprite = sf::IntRect(0, 0, 17, 27);
		break;
	}

	s.setTextureRect(sprite);
}

void Koopa::die() {
	if (state != -1)
	{
		changeState(-1);
		state = -1;
		y_vel = -10;
		x_vel = 0;
	}	
}

void Koopa::update() {
	//Alive
	if (state != -1){
		if (y_vel < -25)
			y_vel = -25;
		y_vel += gravity;
		if (y_vel > 0 && onGround()) {
			y_vel = 0.;
		}

		animation_count++;
		if (animation_count == 3) {

			animation_count = 0;
			state++;
			if (state > 1)
				state = 0;
		}
		changeState(state);

		int xBuffer;
		if (x_vel > 0)
			xBuffer = 15;
		else
			xBuffer = -15;
		int yBuffer = 20;

		if (map.getTileType(s.getPosition().x + xBuffer, s.getPosition().y + yBuffer) == -1) {
			x_vel *= -1;
			Unit::flip();
		}
		s.move(x_vel, y_vel);

		int newXPos = collideX();
		if (newXPos == -1)
			newXPos = s.getPosition().x;
		else
		{
			if (x_vel > 0)
				newXPos -= 15;
			else
				newXPos += 15;
			x_vel *= -1;
			Unit::flip();
		}

		int newYPos = collideY();
		if (y_vel >= 0)
			newYPos -= 15;
		else
			newYPos += 15;

		if (onGround()) {
			s.setPosition(newXPos, newYPos);
		}
	}

	
	//Dead
	else if (state == -1)
	{
		y_vel += gravity;
		s.move(x_vel, y_vel);
	}
	

}