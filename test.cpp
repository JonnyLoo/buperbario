#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Unit.hpp"
#include "TileMap.hpp"

void setup() {

}

int main() {

	//create window
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Buper Bario");

	//create view
	sf::View view(sf::Vector2f(600, 500), sf::Vector2f(1200, 800));

	//-1 = Nothing ; 
	//#0 = left; #1 = mid; #2 = right ; #3 = steepslope 
	//0# = icetop; 1# = icemid; 2# = icebottom || 3# = grasstop ; 4# = grassmid ; 5# = grassbottom || etc
	const int level[] = {	
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //0
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //10
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //15
		-1, -1, -1, -1, -1, -1, -1, 30, 31, 31, 32, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
		-1, -1, -1, -1, -1, -1, -1, 50, 51, 51, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
		30, 31, 31, 31, 31, 31, 31, 32, -1, -1, 00, 03, -1, -1, -1, -1, -1, -1, -1, -1,
		40, 41, 41, 41, 41, 41, 41, 42, -1, -1, 10, 13, 01, 01, 01, 02, -1, -1, -1, -1, //20
		40, 41, 41, 41, 41, 41, 41, 42, -1, -1, 10, 11, 11, 11, 11, 12, -1, -1, -1, -1,
		50, 51, 51, 51, 51, 51, 51, 52, -1, -1, 20, 21, 21, 21, 21, 22, -1, -1, -1, -1,

	//  0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
		};

	TileMap map;
	if(!map.load("tiles.png", sf::Vector2u(16, 16), level, 20, 23))
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
	Bario bario(bariot, &window, map, &view);

	sf::Texture koopat;
	koopat.loadFromFile("koopa.png");
	Koopa koopa(koopat, &window, map, map.getPosition(7, 15));

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

	bool pause = false;
	int pausePress = 0;

	//game loop
	while(window.isOpen()) {
		//handle window closing event
		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed)
				window.close();
		}

		if (!pause)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				bario.jump();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				bario.moveRight();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				bario.moveLeft();
			}
			else {
				bario.noInput();
			}
			if (bario.attack(&koopa) == 0)
				koopa.die();

			bario.update();
			koopa.update();

			window.clear(sf::Color::Black);
			window.setView(view);
			window.draw(background);
			window.draw(map);
			bario.draw();
			koopa.draw();


			window.display();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (pausePress == 0)
			{
				pause = !pause;
				pausePress = 1;
			}
		}
		else
			pausePress = 0;

		if(sf::Keyboard::isKeyPressed(sf::Keyboaord::R))

	}

	return 0;
}