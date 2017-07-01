#include "Game.hpp"
#include "Unit.hpp"

Game::Game() {}

//Return 0 for no collision, 1 for touching sideways, 2 for jumping on other
int Game::collisionCheck(sf::Sprite s1, sf::Sprite s2) {
	sf::FloatRect r1 = s1.getGlobalBounds();
	sf::FloatRect r2 = s2.getGlobalBounds();


	if (!r1.intersects(r2))
	{
		return 0;
	}

	float s1l = r1.left;
	float s1r = r1.left + r1.width;
	float s1t = r1.top;
	float s1b = r1.top + r1.height;
	float s2l = r2.left;
	float s2r = r2.left + r2.width;
	float s2t = r2.top;
	float s2b = r2.top + r2.height;

	float xDiff = s1.getPosition().x - s2.getPosition().x;
	std::cout << "s1 x: " << s1.getPosition().x << std::endl;
	std::cout << "s2 x: " << s2.getPosition().x << std::endl;


	if (xDiff < 10 && xDiff > -10)
		return 2;
	else
		return 1;
}

void Game::run() {

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

	//for animations
	int bstate = 0;
	int delay = 3;
	int count = 0;

	Bario bario(bariot, window, tile);

	//level layout
	float numTilesX = (window.getSize().x / tile[0].getLocalBounds().width) + 2; //102
	float numTilesY = (window.getSize().y / tile[0].getLocalBounds().height) + 2; //62
	std::vector< std::vector<float> > map;
	map.resize(numTilesY, std::vector<float>(numTilesX, 00));

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
	background.setScale(2746 / background.getLocalBounds().width, 900 / background.getLocalBounds().height);
	background.setPosition(0, window.getSize().y - 800);
	background.setTextureRect(sf::IntRect(0, 0, 4000, 900)); //Background stretches for about IntRect.x * 2.5. So background till 10000 
	
	//enemies
	sf::Texture koopat;
	koopat.loadFromFile("enemies.png");
	sf::Sprite koopa;
	koopa.setTexture(koopat);
	koopa.setTextureRect(sf::IntRect(105, 12, 18, 31));
	koopa.setScale(20 / koopa.getLocalBounds().width, 30 / koopa.getLocalBounds().height);
	koopa.setOrigin(koopa.getLocalBounds().width / 2, koopa.getLocalBounds().height / 2);
	koopa.setPosition(500, window.getSize().y - 45);

	//koopa animation
	int koopa_delay = 5;
	int koopa_count = 0;
	int koopa_state = 0;

	//game physics
	float gravity = 1.5;

	float barioXVel = 0.;
	float barioYVel = 0.;
	float xMax = 9.;
	float xAccel = .5;
	bool onground = true;

	float koopaXVel = 0.;
	float koopaYVel = 0.;
	float koopaXMax = .4;
	float koopaXAccel = .2;
	bool koopa_onground = true;

	//game loop
	while(window.isOpen()) {

		//handle window closing event
		sf::Event e;
		while(window.pollEvent(e)) {

			if(e.type == sf::Event::Closed)
				window.close();
		}

		//game physics
		koopaYVel += gravity;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			bario.jump();
		}

		if(koopa_onground) {

			koopaYVel = 0.;
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




		//Checks if Bario is standing on any tiles
		//bool checkOnGround = true;
		//bool checkOnGround_koopa = true;
		//std::vector<sf::Sprite>::iterator it = tile.begin();
		//while (checkOnGround && it != tile.end())
		//{
		//	if ((*it).getPosition().x > bario.getPosition().x)
		//	{
		//		checkOnGround = false;
		//		onground = false;
		//	}
		//	else if (bario.getPosition().x - (*it).getPosition().x < 20)
		//	{
		//		if ((*it).getPosition().y - bario.getPosition().y < 15)
		//		{
		//			checkOnGround = false;
		//			onground = true;
		//		}
		//		else
		//		{
		//			it = ++it;
		//		}
		//	}
		//	else
		//	{
		//		it = ++it;
		//	}
		//}

		//if (it == tile.end()) {

		//	onground = false;
		//}

		//it = tile.begin();
		//while(checkOnGround_koopa && it != tile.end()) {

		//	if ((*it).getPosition().x > koopa.getPosition().x)
		//	{
		//		checkOnGround_koopa = false;
		//		koopa_onground = false;
		//	}
		//	else if (koopa.getPosition().x - (*it).getPosition().x < 20)
		//	{
		//		if ((*it).getPosition().y - koopa.getPosition().y < 15)
		//		{
		//			checkOnGround_koopa = false;
		//			koopa_onground = true;
		//		}
		//		else
		//		{
		//			it = ++it;
		//		}
		//	}
		//	else
		//	{
		//		it = ++it;
		//	}
		//}

		//if(it == tile.end())
		//	koopa_onground = false;



		//if(koopa_onground) {

		//	koopa.setPosition(koopa.getPosition().x, (*it).getPosition().y - 16);
		//}



		//koopa follows bario
		if(koopa.getPosition().x - bario.s.getPosition().x > 0) {

			koopaXVel -= koopaXAccel;
			if(koopaXVel < -koopaXMax)
				koopaXVel = -koopaXMax;
			koopa.setScale(1, 1);
		}
		else {

			koopaXVel += koopaXAccel;
			if(koopaXVel > koopaXMax)
				koopaXVel = koopaXMax;
			koopa.setScale(-1, 1);
		}

		//int collision = collisionCheck(bario, koopa);

		//if (collision == 1 && koopa_state != 2)
		//{
		//	bario.setPosition(sf::Vector2f(20, window.getSize().y - 45));
		//	view.setCenter(sf::Vector2f(600, 500));
		//}
		////koopa death
		//if(collision == 2) {
		//		koopa_state = 2;
		//		koopaXVel = 0;
		//		koopaXAccel = 0;
		//}

		koopa.move(koopaXVel, 0);

		//koopa animation
		koopa_count++;
		if(koopa_count > koopa_delay) {

			koopa_count = 0;
			if(koopa_state == 0)
				koopa_state = 1;
			else if(koopa_state == 1)
				koopa_state = 0;

			switch(koopa_state) {

				case 0:
					koopa.setTextureRect(sf::IntRect(105, 12, 18, 31)); 
					break;
				case 1:
					koopa.setTextureRect(sf::IntRect(123, 12, 18, 31)); 
					break;
				case 2:
					koopa.setTextureRect(sf::IntRect(42, 12, 18, 31));	
					break;
			}	
		}

		//view shifts when bario leaves screen
		if(bario.s.getPosition().x >= view.getCenter().x + 200) {

			view.setCenter(bario.s.getPosition().x - 200, 500);
		}
		else if(bario.s.getPosition().x <= view.getCenter().x - 200) {

			if(view.getCenter().x <= 600) {}
			else
				view.setCenter(bario.s.getPosition().x + 200, 500);
		}

		window.clear(sf::Color::Black);
		window.setView(view);
		window.draw(background);
		window.draw(koopa);

		for(int i = 0; i < tile.size(); i++) {

			window.draw(tile[i]);
		}

		window.display();
	}
}