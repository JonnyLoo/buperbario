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

//Returns -1 if unit not running into a tile. Else return new xPos
int Unit::collideX() {
	if (x_vel == 0)
		return -1;

	int buffer;
	if (x_vel > 0)
		buffer = s.getLocalBounds().width / 2 + 5;
	else if(x_vel < 0)
		buffer = -(s.getLocalBounds().width / 2 + 5);

	int xPos = s.getPosition().x + buffer;
	int yPos = s.getPosition().y - s.getLocalBounds().height / 2;

	int tileNum = map.getTileType(xPos, yPos);
	int tileType = tileNum % 10;
	int floorType = tileNum / 10;

	if (tileNum == -1 || tileType == 3)
		return -1;

	int xDif = xPos % map.getTileLength();
	int yDif = yPos % map.getTileLength();

	if (x_vel < 0)
		return xPos - xDif + map.getTileLength();
	else
		return xPos - xDif;
}

//Returns -1 if unit not standing on tile. Else returns yPos of tile
int Unit::collideY() {
	int yBuffer;
	if (y_vel >= 0)
		yBuffer = 15;
	else
		yBuffer = -15;

	int xBuffer = s.getLocalBounds().width / 2;

	int xPos = s.getPosition().x + xBuffer;
	int yPos = s.getPosition().y + yBuffer;

	int tileNum = map.getTileType(xPos, yPos);
	if (tileNum < 0)
	{
		xPos = s.getPosition().x - xBuffer;
		tileNum = map.getTileType(xPos, yPos);
		if (tileNum < 0)
			return -1;
	}

	int tileType = tileNum % 10;
	int floorType = tileNum / 10;

	int xDif = xPos % map.getTileLength();
	int yDif = yPos % map.getTileLength();

	if (y_vel < 0)
	{
		y_vel = 0;
		return yPos - yDif + map.getTileLength();
	}


	if (floorType % 3 == 0)
	{
		if (tileType < 3)
			return yPos - yDif;
		if (tileType == 3)
		{
			if (map.getTileLength() - 5 < xDif)
				return yPos - yDif + map.getTileLength();
			else
				return yPos - yDif + xDif;
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

bool Unit::onGround()
{
	return collideY() != -1;
}

bool Unit::hitWall()
{
	return collideX() > -1;
}