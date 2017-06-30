#include "Object.hpp"

Background::Background(sf::Texture texture, sf::RenderWindow w) : Object(texture, w) {

	Background::setup();
}

void Background::setup() {

	s.setScale(2746 / s.getLocalBounds().width, 900 / s.getLocalBounds().height);
	s.setPosition(0, w.getSize().y - 800);
	s.setTextureRect(sf::IntRect(0, 0, 4000, 900));
}