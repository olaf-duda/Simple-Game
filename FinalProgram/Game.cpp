#include "Game.h"
int Game::number_of_players = 0;
int Game::turn = 0;
bool Game::end_of_game = false;

Game::~Game() {
	delete[] players;
	number_of_players = 0;
	turn = 0;
	end_of_game = false;
}
Game::Game() {
	players = new(nothrow)Player[number_of_players];
}

void Game::AddPlayer(Player* p) {
	number_of_players++;
	p->SetPlayerNum(number_of_players);
	Player* temp = players;
	players = new(nothrow)Player[number_of_players];
	for (int i = 0; i < number_of_players-1; i++) {
		players[i] = temp[i];
	}
	players[number_of_players - 1] = *p;
}

bool Game::FullTurn() 
{
	end_of_game = false;
	int* declared_turn = players[turn].YourTurn();
	if (declared_turn == nullptr)
		return end_of_game;
	for (int i = 0; i < players[turn].sizeofda; i++) {
		if (players[turn].ReturnIsPoisoned())
			players[turn].TakeDmg(1);
				switch (declared_turn[i]) {
				case 1:
					cout << endl << i+1 << ") YOU FEEL STEADY AND SAFE" << endl;
					break;
				case 2:
					cout << endl << i + 1 << ") YOU ARE READY FOR THE ATTACK" << endl;
					break;
				case 3:
					int n;
					cout << endl << i + 1 << ") WHICH PLAYER DO YOU WANT TO ATTACK?" << endl ;
					for (int k = 1; k <= number_of_players; k++) {
						if (k != players[turn].ReturnPlayerNum())
							cout << "  PLAYER NUMBER " << k << endl;
					}
					cin >> n;
					while (n == players[turn].ReturnPlayerNum() || n > number_of_players || n < 1) {
						cout << "  THAT'S NOT A VALID TARGET" << endl;
						cin >> n;
					}
					if (players[n - 1].TakeDmg(players[turn].DealDmg()) == 0) {
						RemovePlayer(&players[n - 1]);
						if (number_of_players == 1)
							end_of_game = true;
					}
					cout << "  YOU FEEL THE ADRENALINE BUMP IN YOU";
				}
			}
	turn++;
	turn = turn % number_of_players;
	return end_of_game;
}

void Game::RemovePlayer(Player* p) {
	int temp2 = number_of_players;
	Player* temp = new(nothrow)Player[number_of_players - 1];
	number_of_players = temp2;
	int i = 0;
	while (i != number_of_players - 1) {
		if (&players[i] != p) {
			temp[i] = players[i];
			i++;
		}
		else
			delete &players[i];
	}
	number_of_players--;
}