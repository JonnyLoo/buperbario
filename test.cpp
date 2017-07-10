#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Unit.hpp"
#include "TileMap.hpp"

int main() {

	//create window
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Buper Bario");

	//create view
	//sf::View view(sf::Vector2f(600, 500), sf::Vector2f(1200, 800));

/*	const int level[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
						  0, 3, 4, 5, 4, 5, 4, 5, 4, 5, 4, 0,
						  0, 3, 4, 5, 4, 5, 4, 5, 4, 5, 4, 0,
						  0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
						  0, 8, 9, 10, 10, 9, 8, 9, 10, 10, 9, 8,
						  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, };

	TileMap map;
	if(!map.load("tiles.png", sf::Vector2u(15, 15), level, 12, 10))
		return -1;	*/
	const int level[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
						  0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0,
						  0, 1, 2, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 1, 0,
						  0, 1, 2, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 2, 1, 0,
						  0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0,
						  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
						  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

	TileMap map;
	if(!map.load("tiletest.png", sf::Vector2u(32, 32), level, 16, 8))
		return -1;

	//load tile set
/*	sf::Texture tiles;
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

	//list of tiles
	sf::Sprite groundfill;
	groundfill.setTexture(tiles);
	groundfill.setTextureRect(sf::IntRect(28, 80, 15, 15));
	groundfill.setPosition(sf::Vector2f(140, 540));
	groundfill.setScale(40 / groundfill.getLocalBounds().width, 40 / groundfill.getLocalBounds().height);
	groundfill.setOrigin(20, 20);

	sf::Sprite groundslope;
	groundslope.setTexture(tiles);
	groundslope.setTextureRect(sf::IntRect(82, 62, 15, 15));
	groundslope.setPosition(sf::Vector2f(140, 500));
	groundslope.setScale(40 / groundslope.getLocalBounds().width, 40 / groundslope.getLocalBounds().height);
	groundslope.setOrigin(20, 20);

	sf::Sprite groundslope2;
	groundslope2.setTexture(tiles);
	groundslope2.setTextureRect(sf::IntRect(99, 62, 15, 15));
	groundslope2.setPosition(sf::Vector2f(180, 500));
	groundslope2.setScale(40 / groundslope2.getLocalBounds().width, 40 / groundslope2.getLocalBounds().height);
	groundslope2.setOrigin(20, 20);

	sf::Sprite groundslope3;
	groundslope3.setTexture(tiles);
	groundslope3.setTextureRect(sf::IntRect(99, 80, 15, 15));
	groundslope3.setPosition(sf::Vector2f(180, 540));
	groundslope3.setScale(40 / groundslope3.getLocalBounds().width, 40 / groundslope3.getLocalBounds().height);
	groundslope3.setOrigin(20, 20);

	sf::Sprite bigslope;
	bigslope.setTexture(tiles);
	bigslope.setTextureRect(sf::IntRect(63, 62, 15, 15));
	bigslope.setPosition(sf::Vector2f(220, 500));
	bigslope.setScale(-40 / bigslope.getLocalBounds().width, 40 / bigslope.getLocalBounds().height);
	bigslope.setOrigin(20, 20);

	sf::Sprite bigslope2;
	bigslope2.setTexture(tiles);
	bigslope2.setTextureRect(sf::IntRect(63, 80, 15, 15));
	bigslope2.setPosition(sf::Vector2f(220, 540));
	bigslope2.setScale(-40 / bigslope2.getLocalBounds().width, 40 / bigslope2.getLocalBounds().height);
	bigslope2.setOrigin(20, 20);

	sf::Sprite itemblock;
	itemblock.setTexture(tiles);
	itemblock.setTextureRect(sf::IntRect(126, 461, 16, 16));
	itemblock.setPosition(sf::Vector2f(360, 500));
	itemblock.setScale(40 / itemblock.getLocalBounds().width, 40 / itemblock.getLocalBounds().height);
	itemblock.setOrigin(20, 20);*/
	


	//vector for bario walking animations
	sf::Texture bariot;
	bariot.loadFromFile("smallbario.png");

	//Bario bario(bariot, &window, tile, &view);

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

/*		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
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
		bario.update();*/

		window.clear(sf::Color::Black);
		//window.setView(view);
		window.draw(background);
		window.draw(map);
		//bario.draw();
/*		for(int i = 0; i < tile.size(); i++) {
			window.draw(tile[i]);
		}

		window.draw(groundfill);
		window.draw(groundslope);
		window.draw(groundslope2);
		window.draw(groundslope3);
		window.draw(bigslope);
		window.draw(bigslope2);
		window.draw(itemblock);*/

		window.display();
	}

	return 0;
}