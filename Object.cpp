#include "Object.hpp"

Object::Object(sf::Texture texture, sf::RenderWindow* window) {
	t = texture;
	s.setTexture(t);

	w = window;
}

void Object::draw() {

	w->draw(s);
}

//left
float Object::getPositionX1() {

	return s.getGlobalBounds().left;
}

//top
float Object::getPositionY1() {

	return s.getGlobalBounds().top;
}

//right
float Object::getPositionX2() {

	return s.getGlobalBounds().left + s.getGlobalBounds().width;
}

//bottom
float Object::getPositionY2() {

	return s.getGlobalBounds().top + s.getGlobalBounds().height;
}