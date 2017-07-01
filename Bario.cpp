#include "Unit.hpp"

Bario::Bario(sf::Texture texture, sf::RenderWindow* window, std::vector<sf::Sprite> tiles_) : Unit(texture, window, tiles_) {

	Bario::setup();
}

void Bario::changeSprite(int new_sprite) {
	sf::IntRect sprite;

	switch (new_sprite) {
	case 0: //standing 
		sprite = sf::IntRect(10, 6, 20, 22);
		break;
	case 1: //moving 1
		sprite = sf::IntRect(30, 6, 20, 22);
		break;
	case 2: //moving 2
		sprite = sf::IntRect(53, 5, 20, 22);
		break;
	case 4: //jumping
		sprite = sf::IntRect(180, 6, 20, 22);
		break;
	default:
		sprite = sf::IntRect(10, 6, 20, 22);
		break;
	}

	s.setTextureRect(sprite);
}

void Bario::setup() {

	animation_delay = 3;
	animation_count = 0;
	x_max_vel = 9;
	x_accel = .5;
	gravity = 1.5;

	changeSprite(0);
	s.setPosition(sf::Vector2f(30, w->getSize().y - 55));
	s.setScale(20 / s.getLocalBounds().width, 20 / s.getLocalBounds().height);
	s.setOrigin(10, 10);
}



void Bario::changeState(int new_state) {


}

void Bario::jump() {
	if (onGround()) {
		y_vel -= 25.;
	}
}

void Bario::moveLeft() {
	if (!(s.getPosition().x <= 15)) {

		x_vel -= x_accel;
		if (x_vel < -x_max_vel)
			x_vel = -x_max_vel;
	}
	else
		x_vel = 0;

	animation_count++;
	if (animation_count == 3) {

		animation_count = 0;
		state++;
		if (state > 2)
			state = 1;
	}
	changeSprite(state);
	if (s.getScale().x > 0)
	{
		flip();
	}

}

void Bario::moveRight() {
	x_vel += x_accel;
	if (x_vel > x_max_vel)
		x_vel = x_max_vel;

	animation_count++;
	if (animation_count == 3) {

		animation_count = 0;
		state++;
		if (state > 2)
			state = 1;
	}
	changeSprite(state);
	if (s.getScale().x < 0)
	{
		flip();
	}
}

void Bario::noInput() {
	if (x_vel > 0)
		x_vel--;
	else if (x_vel < 0)
		x_vel++;
	else
		x_vel = 0;

	state = 0;
	changeSprite(state);
}

void Bario::update() {
	y_vel += gravity;
	if (y_vel > 0 && onGround()) {
		y_vel = 0.;
	}

	s.move(x_vel, y_vel);

	if (!onGround()) {
		state = 4;
		changeSprite(state);
	}
	else
		s.setPosition(s.getPosition().x, tiles[0].getPosition().y - 12); //Pls fix this. just gets y position of first tile

	//Tired of Bario falling forever. Reset when falls to bottom of screen
	if (s.getPosition().y > w->getSize().y) {
		setup();
	}
}