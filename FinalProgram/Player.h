#pragma once
#include <iostream>
#include "Classes.h"
using namespace std;
enum potions { NoPotion, PotionOfHealing = 1, PotionOfAction, PotionOfDefence };

class Player
{
	int* declared_actions;
	Classes role;
	potions potion;
	int playernumber;	
	bool defending;
	bool evading;
	bool IsPoisoned;
public:
	int sizeofda =0;
	Player();
	Player(Classes role, potions potion);
	~Player();
	int* YourTurn();
	int DealDmg();
	int ReturnPlayerNum()const { return playernumber; };
	void SetPlayerNum(int n) { playernumber = n; };
	bool IsDefending();
	bool IsEvading(); 
	bool ReturnIsPoisoned();
	int TakeDmg(int damage);

	friend ostream& operator<<(ostream& os, const Player& p);
	friend istream& operator>>(istream& is, Player& p);
	Player& operator= (const Player& rhs);

};