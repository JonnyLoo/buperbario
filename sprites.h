class Sprite {

public:
	Sprite();
};

class Bario {

public:
	int lives;
	int coins;
	int powerup;
	bool isJumping;

	Bario();
	void update();
	void collisionDetect();
	void manageInput();
};

class Enemy {

public:
	Enemy();
};

class Block {

public:
	Block();
};

class Item {

public:
	Item();
};