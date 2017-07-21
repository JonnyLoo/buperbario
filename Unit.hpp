#include "Object.hpp"
#include "TileMap.hpp"

class Unit : public Object {

public:
	Unit(sf::Texture texture, sf::RenderWindow* w, TileMap map);
	virtual void setup()=0;
	virtual void changeState(int new_state)=0;
	virtual void update()=0;
	void updateSpeed();
	void flip();
	int onGround();

protected:
	TileMap map;
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
	Bario(sf::Texture texture, sf::RenderWindow* w, TileMap map, sf::View* view);
	void setup();
	void changeState(int new_state);
	void jump();
	void moveLeft();
	void moveRight();
	void noInput();
	void update();

private:
	sf::View* v;
	void changeSprite(int new_sprite);
	int animation_count;
	void updateView();
};

/*
class Koopa : public Unit {

public:
	Koopa(sf::Texture texture, sf::RenderWindow w);
	void setup();
	void changeState(int new_state);
	void update(Bario b);
};
*/