#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Unit.hpp"

int main() {

	//create window
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Buper Bario");

	//create view
	sf::View view(sf::Vector2f(600, 500), sf::Vector2f(1200, 800));

	//load tile set
	sf::Texture tiles;
	tiles.loadFromFile("tiles.png");

	int xLoc = 20;
	std::vector<sf::Sprite> tile(50);
	for (int i = 0; i < tile.size(); i++) {

		tile[i].setTexture(tiles);
		tile[i].setTextureRect(sf::IntRect(28, 64, 15, 15));
		tile[i].setPosition(sf::Vector2f(xLoc, window.getSize().y - 35));
		tile[i].setScale(20 / tile[i].getLocalBounds().width, 20 / tile[i].getLocalBounds().height);
		xLoc += 20;
	}

	//vector for bario walking animations
	sf::Texture bariot;
	bariot.loadFromFile("smallbario.png");

	Bario bario(bariot, &window, tile);

	//load background
	//make parallax
	sf::Texture backgroundt;
	backgroundt.loadFromFile("background1.png");
	backgroundt.setRepeated(true);
	sf::Sprite background;
	background.setTexture(backgroundt);
	background.setScale(2746 / background.getLocalBounds().width, 900 / background.getLocalBounds().height);
	background.setPosition(0, window.getSize().y - 800);
	background.setTextureRect(sf::IntRect(0, 0, 4000, 900)); 

	//game loop
	while(window.isOpen()) {

		//handle window closing event
		sf::Event e;
		while(window.pollEvent(e)) {

			if(e.type == sf::Event::Closed)
				window.close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			bario.jump();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			bario.moveRight();
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			bario.moveLeft();
		}
		else {
			bario.noInput();
		}
		bario.update();

		window.clear(sf::Color::Black);
		window.setView(view);
		window.draw(background);
		bario.draw();
		for(int i = 0; i < tile.size(); i++) {
			window.draw(tile[i]);
		}

		window.display();
	}
}