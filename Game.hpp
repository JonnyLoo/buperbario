#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Game {

public:
	Game();
	int collisionCheck(sf::Sprite s1, sf::Sprite s2);
	void run();
};