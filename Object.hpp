#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Object {

public:

	Object(sf::Texture texture, sf::RenderWindow* window);
	virtual void setup()=0;
	void draw();
	float getPositionX1();
	float getPositionY1();
	float getPositionX2();
	float getPositionY2();

	sf::Sprite s;


protected:
	sf::Texture t;
	sf::RenderWindow* w;
};
//
//class Background : public Object {
//
//public:
//	Background(sf::Texture texture, sf::RenderWindow w);
//	void setup();
//};