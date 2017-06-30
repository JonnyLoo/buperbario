#include "Unit.hpp"

Bario::Bario(sf::Texture texture, sf::RenderWindow w) : Unit(texture, w) {

	Bario::setup();
}

void Bario::setup() {

	animation_delay = 3;
	x_max_vel = 9;
	x_accel = .5;
	gravity = 1.5;

	s.setTextureRect(sf::IntRect(10, 6, 20, 22));
	s.setPosition(sf::Vector2f(30, w.getSize().y - 55));
	s.setScale(20 / s.getLocalBounds().width, 20 / s.getLocalBounds().height);
	s.setOrigin(10, 10);
}

void Bario::changeState(int new_state) {


}

void Bario::jump() {


}

void Bario::moveLeft() {


}

void Bario::moveRight() {


}

void Bario::update() {


}