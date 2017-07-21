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

//Returns -1 if unit not standing on tile. Else returns yPos of tile
int Unit::onGround() {
	int xPos = s.getPosition().x;
	int yPos = s.getPosition().y;
	int tileNum = map.getTileType(xPos, yPos);

	if (tileNum < 0)
	{
		int buffer = 15;
		xPos = s.getPosition().x;
		yPos = s.getPosition().y + buffer;

		tileNum = map.getTileType(xPos, yPos);
		if (tileNum < 0)
			return -1;
	}

	int tileType = tileNum % 10;
	int floorType = tileNum / 10;

	int xDif = xPos % map.getTileLength();
	int yDif = yPos % map.getTileLength();


	if (floorType % 3 == 0)
	{
		if (tileType < 3)
			return yPos - yDif;
		if (tileType == 3)
		{
			if (yDif < xDif)
				return -1;
			else
			{
				if (map.getTileLength() - 5 < xDif)
					return yPos - yDif - map.getTileLength();
				else
					return yPos - yDif + xDif;
			}
		}
	}
	else if (floorType % 3 == 1)
	{
		if (tileType < 3)
			return yPos - map.getTileLength() - yDif;
		if (tileType == 3)
		{
			return yPos - map.getTileLength() - yDif + xDif;
		}

	}



}