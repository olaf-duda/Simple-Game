#pragma once
#include <iostream>
enum roles { knight = 1, sorcerer, rogue };
enum weapons { sword = 1, greataxe, fireball, frostbolt, knives, poison };

using namespace std;

class Classes
{
	roles role;
	weapons weapon;
	int health = 0;
	int action = 0;
	int dmg_dice = 0;
	int num_of_dice = 0;
	int attack_cost = 0;
	void ChooseKnight();
	void ChooseSorcerer();
	void ChooseRogue();

public:
	Classes();
	Classes(roles s);
	~Classes();
	roles ReturnRole() const { return role; };
	weapons ReturnWeapon() const { return weapon; };
	int ReturnHealth() const { int temp = health; return temp; };
	int ReturnActions() const { return action; };
	int ReturnAttackCost() const { return attack_cost; };
	int ReturnNumDice() const { return num_of_dice; };
	int ReturnDmgDice() const { return dmg_dice; };
	int LooseHealth(int n) { health -= n; return health; };
	void UseAction(int n) { action -= n;};
	friend int GetDmg(int n, Classes p);
	friend int TakeAction(int n, Classes p);
	friend ostream& operator<<(ostream& os, const Classes& p);
	friend istream& operator>>(istream& os, Classes& p);
	Classes& operator= (const Classes& rhs);
};
