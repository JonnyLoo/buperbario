#include "Unit.hpp"

Bario::Bario(sf::Texture texture, sf::RenderWindow* window, TileMap map, sf::View* view) : Unit(texture, window, map) {

	Bario::setup();
	v = view;
	w->setView(*v);
}

void Bario::changeSprite(int new_sprite) {
	sf::IntRect sprite;

	switch (new_sprite) {
	case -1: //death
		sprite = sf::IntRect(196, 34, 16, 24);
		break;
	case 0: //standing 
		sprite = sf::IntRect(10, 7, 14, 20);
		break;
	case 1: //moving 1
		sprite = sf::IntRect(32, 8, 15, 19);
		break;
	case 2: //moving 2
		sprite = sf::IntRect(55, 7, 14, 20);
		break;
	case 4: //jumping
		sprite = sf::IntRect(184, 5, 16, 22);
		break;
	default:
		sprite = sf::IntRect(10, 7, 14, 20);
		break;
	}

	s.setTextureRect(sprite);
}

void Bario::changeState(int new_state) {

}

void Bario::setup() {
	animation_delay = 3;
	animation_count = 0;
	x_max_vel = 9;
	x_accel = .5;
	gravity = 1.5;
	state = 0;

	changeSprite(0);
	s.setPosition(sf::Vector2f(30, w->getSize().y - 200));
	s.setScale(16 / s.getLocalBounds().width, 20 / s.getLocalBounds().height);
	s.setOrigin(s.getLocalBounds().width / 2, s.getLocalBounds().height / 2);
}


//return -1 for no collision, 0 for hit enemy, 1 for get hit
int Bario::attack(Unit* enemy) {
	if ((*enemy).state == -1)
		return -1;
	if (s.getGlobalBounds().intersects((*enemy).s.getGlobalBounds()))
	{
		if (y_vel < 1)
			return 1;
		else
			return 0;
	}
	return -1;
}


void Bario::die() {
	if (state != -1)
	{
		changeSprite(-1);
		state = -1;
		y_vel = -10;
		x_vel = 0;
	}
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

void Bario::jump() {
	if (onGround()) {
		y_vel -= 25.;
	}
}

void Bario::moveLeft() {
	if (!hitWall())
	{
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
	else
		y_vel = 0;
}

void Bario::moveRight() {
	if (!hitWall())
	{
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
	else
		y_vel = 0;
}

void Bario::noInput() {
	if (x_vel < 1 && x_vel > -1)
		x_vel = 0;
	else if (x_vel > 0)
		x_vel--;
	else if (x_vel < 0)
		x_vel++;
	else
		x_vel = 0;
	
	state = 0;
	changeSprite(state);
}

void Bario::update() {
	if (state != -1)
	{
		if (hitWall())
			x_vel = 0;

		if (y_vel < -25)
			y_vel = -25;
		y_vel += gravity;
		if (y_vel > 0 && onGround()) {
			y_vel = 0.;
		}

		s.move(x_vel, y_vel);

		int newXPos = collideX();
		if (newXPos == -1)
			newXPos = s.getPosition().x;
		else
		{
			int xPosBuffer = s.getLocalBounds().width / 2;
			if (x_vel > 0)
				newXPos -= xPosBuffer;
			else
				newXPos += xPosBuffer;
		}

		int newYPos = collideY();
		int yPosBuffer = s.getLocalBounds().height / 2;
		if (y_vel >= 0)
			newYPos -= yPosBuffer;
		else
			newYPos += yPosBuffer;

		if (!onGround()) {
			state = 4;
			changeSprite(state);
		}
		else
		{
			s.setPosition(newXPos, newYPos);
		}

		updateView();

		//Tired of Bario falling forever. Reset when falls to bottom of screen
		if (s.getPosition().y > w->getSize().y) {
			die();
		}
	}
	else if (state == -1)
	{
		y_vel += gravity;
		s.move(x_vel, y_vel);

		if (s.getPosition().y > 1450)
			setup();
	}
	
}