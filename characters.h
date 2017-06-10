class Player {

public:
	int lives;
	int coins;
	int powerup;
	bool isJumping;

	Player();
	void update();
	void collisionDetect();
	void manageInput();
};