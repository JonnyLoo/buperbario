#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

sf::IntRect changeSprite(char state)
{
	switch(state) {
		case 's': //standing 
			return sf::IntRect(11, 10, 19, 20);
			break;
		case 'm': //moving
			return sf::IntRect(28, 10, 19, 20);
		case 'j': //jumping
			return sf::IntRect(114, 10, 19, 20);
		default:
			return sf::IntRect(11, 10, 19, 20);

	}
}

void drawTiles(std::vector<sf::Sprite> tiles)
{

}

int main() {

	//create window
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Buper Bario");

	//create view
	sf::View view(sf::Vector2f(600, 500), sf::Vector2f(1200, 800));

	//vector for bario walking animations
	sf::Texture bariot;
	bariot.loadFromFile("smallbario.png");

	//bario sprite
	sf::Sprite bario;
	bario.setTexture(bariot);
	bario.setTextureRect(changeSprite('s'));
	bario.setPosition(sf::Vector2f(20, window.getSize().y - 45));
	bario.setOrigin(9.5, 10);

	//load tile set
	//make into an array of sprites
	sf::Texture tiles;
	tiles.loadFromFile("groundtiles.png");
	sf::Sprite ttile;
	ttile.setTexture(tiles);
	ttile.setTextureRect(sf::IntRect(122, 151, 14, 14));
	ttile.setPosition(sf::Vector2f(100, window.getSize().y - 35));
	ttile.setScale(20 / ttile.getLocalBounds().width, 20 / ttile.getLocalBounds().height);

	sf::Sprite tile;
	tile.setTexture(tiles);
	tile.setTextureRect(sf::IntRect(122, 151, 14, 14));
	tile.setPosition(sf::Vector2f(20, window.getSize().y - 35));

	sf::Sprite tile2;
	tile2.setTexture(tiles);
	tile2.setTextureRect(sf::IntRect(122, 169, 14, 14));
	tile2.setPosition(sf::Vector2f(20, window.getSize().y - 22));

	sf::Sprite tile3;
	tile3.setTexture(tiles);
	tile3.setTextureRect(sf::IntRect(122, 169, 14, 14));
	tile3.setPosition(sf::Vector2f(20, window.getSize().y - 9));

	sf::Sprite tile4;
	tile4.setTexture(tiles);
	tile4.setTextureRect(sf::IntRect(122, 151, 14, 14));
	tile4.setPosition(sf::Vector2f(33, window.getSize().y - 35));

	sf::Sprite tile5;
	tile5.setTexture(tiles);
	tile5.setTextureRect(sf::IntRect(122, 169, 14, 14));
	tile5.setPosition(sf::Vector2f(33, window.getSize().y - 22));

	sf::Sprite tile6;
	tile6.setTexture(tiles);
	tile6.setTextureRect(sf::IntRect(122, 169, 14, 14));
	tile6.setPosition(sf::Vector2f(33, window.getSize().y - 9));

	//level layout
	int numTilesX = window.getSize().x / tile.getLocalBounds().width + 2;
	int numTilesY = window.getSize().y / tile.getLocalBounds().height + 2;
	std::vector< std::vector<float> > map;
	map.resize(numTilesY - 1, std::vector<float>(numTilesX, 00));

	std::vector< sf::Sprite> listTiles;
	for (int i = 0; i < numTilesX; i = i + 1)
	{
		sf::Sprite newTile;
		newTile.setTexture(tiles);
		newTile.setTextureRect(sf::IntRect(122, 169, 14, 14));
		newTile.setPosition(sf::Vector2f(window.getSize().x / tile.getLocalBounds().width, window.getSize().y - 9));
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
	backgroundt.setRepeated(true);

	sf::Sprite background;
	background.setTexture(backgroundt);
	background.setScale(1400 / background.getLocalBounds().width, 900 / background.getLocalBounds().height);
	background.setTextureRect(sf::IntRect(0,0,4000,900)); //Background stretches for about IntRect.x * 2.5. So background till 10000 
	background.move(-10, 0);
	
	//game physics
	float gravity = 2.;
	float barioXVel = 0.;
	float barioYVel = 0.;
	float xMax = 6.;
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

			bario.setTextureRect(changeSprite('m'));
			if (bario.getScale().x == -1)
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

			bario.setTextureRect(changeSprite('m'));
			if (bario.getScale().x == 1)
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

			bario.setTextureRect(changeSprite('s'));
		}

		bario.move(barioXVel, barioYVel);
		background.move(-barioXVel / 10, -barioYVel / 10);

		if(bario.getPosition().y + gravity >= window.getSize().y - 55) {

			onground = true;
		}
		else
		{
			bario.setTextureRect(changeSprite('j'));
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

		window.draw(tile);
		window.draw(tile2);
		window.draw(tile3);
		window.draw(tile4);
		window.draw(tile5);
		window.draw(tile6);
		window.draw(ttile);

		bool inBounds = true;
		std::vector<sf::Sprite>::iterator it = listTiles.begin();

		while (inBounds && it != listTiles.end())
		{
			window.draw(*it);
			it++;
		}

		window.display();
	}

	return 0;
}

