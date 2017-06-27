#include "Game.hpp"

Game::Game() {}

sf::IntRect Game::changeSprite(int state)
{
	switch(state) {
		case 0: //standing 
			return sf::IntRect(10, 6, 20, 22);
			break;
		case 1: //moving 1
			return sf::IntRect(30, 6, 20, 22);
		case 2: //moving 2
			return sf::IntRect(53, 5, 20, 22);
		case 4: //jumping
			return sf::IntRect(180, 6, 20, 22);
		default:
			return sf::IntRect(10, 6, 20, 22);

	}
}

void Game::run() {

	//create window
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Buper Bario");

	//create view
	sf::View view(sf::Vector2f(600, 500), sf::Vector2f(1200, 800));

	//vector for bario walking animations
	sf::Texture bariot;
	bariot.loadFromFile("smallbario.png");

	//for animations
	int bstate = 0;
	int delay = 3;
	int count = 0;

	//bario sprite
	sf::Sprite bario;
	bario.setTexture(bariot);
	bario.setTextureRect(changeSprite(bstate));
	bario.setPosition(sf::Vector2f(20, window.getSize().y - 45));
	bario.setOrigin(9.5, 10);
	bario.setScale(20 / bario.getLocalBounds().width, 20 / bario.getLocalBounds().height);

	//load tile set
	sf::Texture tiles;
	tiles.loadFromFile("tiles.png");

	int xLoc = 20;
	std::vector<sf::Sprite> tile(10);
	for(int i = 0; i < tile.size(); i++) {

		tile[i].setTexture(tiles);
		tile[i].setTextureRect(sf::IntRect(28, 64, 15, 15));
		tile[i].setPosition(sf::Vector2f(xLoc, window.getSize().y - 35));
		tile[i].setScale(20 / tile[i].getLocalBounds().width, 20 / tile[i].getLocalBounds().height);
		xLoc += 20;
	}

	//level layout
	float numTilesX = (window.getSize().x / tile[0].getLocalBounds().width) + 2; //102
	float numTilesY = (window.getSize().y / tile[0].getLocalBounds().height) + 2; //62
	std::vector< std::vector<float> > map;
	map.resize(numTilesY, std::vector<float>(numTilesX, 00));

	std::vector< sf::Sprite> listTiles;
	for (int i = 0; i < numTilesX; i = i + 1)
	{
		sf::Sprite newTile;
		newTile.setTexture(tiles);
		newTile.setTextureRect(sf::IntRect(122, 169, 14, 14));
		newTile.setPosition(sf::Vector2f(window.getSize().x / tile[0].getLocalBounds().width, window.getSize().y - 9));
		listTiles.push_back(newTile);
	}

	std::cout << numTilesX << std::endl << numTilesY << std::endl;

   /*{{00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00},
	  {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00}}; */

	//load background
	//make parallax
	sf::Texture backgroundt;
	backgroundt.loadFromFile("background1.png");
	sf::Sprite background;
	background.setTexture(backgroundt);
	background.setScale(2746 / background.getLocalBounds().width, 800 / background.getLocalBounds().height);
	background.setPosition(0, window.getSize().y - 800);
	
	//game physics
	float gravity = 1.5;
	float barioXVel = 0.;
	float barioYVel = 0.;
	float xMax = 9.;
	float xAccel = .5;
	bool onground = true;

	//game loop
	while(window.isOpen()) {

		//handle window closing event
		sf::Event e;
		while(window.pollEvent(e)) {

			if(e.type == sf::Event::Closed)
				window.close();
		}

		//game physics
		barioYVel += gravity;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

			if (onground) {

				barioYVel -= 25.;
				onground = false;
			}
		}

		if(onground) {

			barioYVel = 0.;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			barioXVel += xAccel;
			if(barioXVel > xMax)
				barioXVel = xMax;

			count++;
			if(count == 3) {

				count = 0;
				bstate++;
				if(bstate > 2)
					bstate = 1;
			}
			bario.setTextureRect(changeSprite(bstate));
			if (bario.getScale().x < 0)
			{
				bario.setScale(1, 1);
			}
			
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			if(!(bario.getPosition().x <= 15)) {

				barioXVel -= xAccel;
				if(barioXVel < -xMax)
					barioXVel = -xMax;
			}
			else
				barioXVel = 0;

			count++;
			if(count == 3) {

				count = 0;
				bstate++;
				if(bstate > 2)
					bstate = 1;
			}
			bario.setTextureRect(changeSprite(bstate));
			if (bario.getScale().x > 0)
			{
				bario.setScale(-1, 1);
			}
		}
		else {

			if(barioXVel > 0)
				barioXVel--;
			else if(barioXVel < 0)
				barioXVel++;
			else
				barioXVel = 0;

			bstate = 0;
			bario.setTextureRect(changeSprite(bstate));
		}

		bario.move(barioXVel, barioYVel);
		background.move(-barioXVel / 10, -barioYVel / 10);

		if(bario.getPosition().y + gravity >= window.getSize().y - 55) {

			onground = true;
		}
		else {

			bstate = 4;
			bario.setTextureRect(changeSprite(bstate));
		}

		//view shifts when bario leaves screen
		if(bario.getPosition().x >= view.getCenter().x + 200) {

			view.setCenter(bario.getPosition().x - 200, 500);
		}
		else if(bario.getPosition().x <= view.getCenter().x - 200) {

			if(view.getCenter().x <= 600) {}
			else
				view.setCenter(bario.getPosition().x + 200, 500);
		}

		window.clear(sf::Color::Black);
		window.setView(view);
		window.draw(background);
		window.draw(bario);

		bool inBounds = true;
		std::vector<sf::Sprite>::iterator it = listTiles.begin();

		while (inBounds && it != listTiles.end())
		{
			window.draw(*it);
			it++;
		}

		for(int i = 0; i < tile.size(); i++) {

			window.draw(tile[i]);
		}

		window.display();
	}
}