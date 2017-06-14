#include <iostream>
using namespace std;

int main() {
	
	Menu menu;
	menu.load;

	if (menu.getDecision() == 1) {

		menu.close();
		GameManager game;
		game.initialize();

		//relay input and output to gamemanager
		while (game.notFinished()) {

			game.update();
		}
	}
	else if (menu.getDecision() == 2) {

		menu.close();
	}

	return 0;
}