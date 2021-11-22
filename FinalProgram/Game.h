#pragma once
#include "Player.h"
using namespace std;

class Game 
{
public:
	Player* players;
	static int number_of_players;
	static bool end_of_game;
	static int turn;
	Game();
	~Game();
	void AddPlayer(Player *p);
	bool FullTurn();
	void RemovePlayer(Player* p);
};
