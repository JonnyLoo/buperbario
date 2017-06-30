#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Object {

public:

	Object(sf::Texture texture, sf::RenderWindow w);
	virtual void setup();
	void draw();
	float getPositionX1();
	float getPositionY1();
	float getPositionX2();
	float getPositionY2();

private:
	sf::Texture t;
	sf::Sprite s;
};

class Background : public Object {

public:
	Background(sf::Texture texture, sf::RenderWindow w);
	void setup();
};