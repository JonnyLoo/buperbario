#include "Unit.hpp"

Unit::Unit(sf::Texture texture, sf::RenderWindow* window, TileMap map_) : Object(texture, window) {
	state = 0;
	animation_delay = 0;
	x_vel = 0;
	y_vel = 0;
	x_accel = 0;
	x_max_vel = 0;
	gravity = 0;
	map = map_;
}

void Unit::updateSpeed() {

	x_vel += x_accel;
	y_vel += gravity;
	if(x_vel >= x_max_vel)
		x_vel = x_max_vel;
}

void Unit::flip() {

	if(s.getScale().x > 0)
		s.setScale(-1, 1);
	else
		s.setScale(1, 1);
}

//TODO
bool Unit::onGround() {
	return map.onTile(s.getPosition().x, s.getPosition().y);
}