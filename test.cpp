#include <SFML/Graphics.hpp>
#include <vector>

sf::IntRect changeSprite(char state)
{
	switch(state) {
		case 's': //standing 
			return sf::IntRect(10, 10, 20, 20);
			break;
		case 'm': //moving
			return sf::IntRect(27, 10, 20, 20);
		case 'j': //jumping
			return sf::IntRect(113, 10, 20, 20);
		default:
			return sf::IntRect(10, 10, 20, 20);

	}
}

int main() {

	//create window
	sf::RenderWindow window(sf::VideoMode(1400, 900), "Buper Bario");

	//create view
	sf::View view(sf::Vector2f(400, 600), sf::Vector2f(800, 600));

	//vector for bario walking animations
	sf::Texture bariot;
	bariot.loadFromFile("bario.png");

	//bario sprite
	sf::Sprite bario;
	bario.setTexture(bariot);
	bario.setTextureRect(changeSprite('s'));
	bario.setPosition(sf::Vector2f(20, window.getSize().y - 45));

	//load tile set
	sf::Texture tiles;
	tiles.loadFromFile("groundtiles.png");
	sf::Sprite tile;
	tile.setTexture(tiles);
	tile.setTextureRect(sf::IntRect(122, 152, 15, 15));
	tile.setPosition(sf::Vector2f(20, window.getSize().y - 25));

	//level layout
	int numTilesX = window.getSize().x / tile.getLocalBounds().width + 2;
	int numTilesY = window.getSize().y / tile.getLocalBounds().height + 2;
	std::vector< std::vector<float> > map;
	map.resize(numTilesY, std::vector<float>(numTilesX, 00));

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
	background.setScale(1400 / background.getLocalBounds().width, 900 / background.getLocalBounds().height);

	
	//game physics
	float gravity = 2.;
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

			bario.setTextureRect(changeSprite('m'));
			if (bario.getScale().x == -1)
			{
				bario.setScale(1.f, 1.f);
			}
			
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

			barioXVel -= xAccel;
			if(barioXVel < -xMax)
				barioXVel = -xMax;

			bario.setTextureRect(changeSprite('m'));
			if (bario.getScale().x == 1)
			{
				bario.setScale(-1.f, 1.f);
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

		if(bario.getPosition().y + gravity >= window.getSize().y - 55) {

			onground = true;
		}
		else
		{
			bario.setTextureRect(changeSprite('j'));
		}

		//view shifts when bario leaves screen
		view.setCenter(bario.getPosition().x, bario.getPosition().y);

		window.clear(sf::Color::Black);
		window.setView(view);
		window.draw(background);
		window.draw(bario);
		window.draw(tile);
		window.display();
	}

	return 0;
}

