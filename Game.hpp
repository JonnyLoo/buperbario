#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Game {

public:
	Game();
	sf::IntRect changeSprite(int s);
	void run();
};