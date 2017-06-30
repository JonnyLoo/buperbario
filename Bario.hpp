#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Unit.hpp"

class Bario : public Unit{

public:
	Bario(sf::Sprite sprite);
	void changeState(int state);
	void jump();
	void moveLeft();
	void moveRight();
	void noInput();

protected:

};
	