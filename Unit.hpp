#include "Object.hpp"

class Unit : public Object {

public:
	Unit(sf::Texture texture, sf::RenderWindow w);
	virtual void setup();
	virtual void changeState(int new_state);
	virtual void update();
	void updateSpeed(float dx, float dy);
	void flip();
	bool onGround(std::vector<sf::Sprite> tiles);

private:
	int state;
	int animation_delay;
	float x_vel;
	float y_vel;
	float x_accel;
	float x_max_vel;
	float gravity;
};

class Bario : public Unit {

public:
	Bario(sf::Texture texture, sf::RenderWindow w);
	void setup();
	void changeState(int new_state);
	void jump();
	void moveLeft();
	void moveRight();
	void update();
};

class Koopa : public Unit {

public:
	Koopa(sf::Texture texture, sf::RenderWindow w);
	void setup();
	void changeState(int new_state);
	void update(Bario b);
};