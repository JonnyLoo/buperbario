#include "Unit.hpp"

Bario::Bario(sf::Texture texture, sf::RenderWindow* window, TileMap map, sf::View* view) : Unit(texture, window, map) {

	Bario::setup();
	v = view;
	w->setView(*v);
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
	s.setPosition(sf::Vector2f(30, w->getSize().y - 200));
	s.setScale(20 / s.getLocalBounds().width, 20 / s.getLocalBounds().height);
	s.setOrigin(10, 10);
}

void Bario::updateView() {

	//view shifts when bario leaves screen
	if(s.getPosition().x >= v->getCenter().x + 200) {

		v->setCenter(s.getPosition().x - 200, 500);
	}
	else if(s.getPosition().x <= v->getCenter().x - 200) {

		if(v->getCenter().x <= 600) {}
		else
			v->setCenter(s.getPosition().x + 200, 500);
	}
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
	if (y_vel < -25)
		y_vel = -25;
	y_vel += gravity;
	if (y_vel > 0 && onGround() >= 0) {
		y_vel = 0.;
	}

	s.move(x_vel, y_vel);

	int on_ground = onGround();

	if (on_ground < 0) {
		state = 4;
		changeSprite(state);
	}
	else
	{
		s.setPosition(s.getPosition().x, on_ground - 10);
	}

	updateView();

	//Tired of Bario falling forever. Reset when falls to bottom of screen
	if (s.getPosition().y > 2000) {
		setup();
	}
}