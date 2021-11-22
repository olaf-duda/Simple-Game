#include <iostream>
#include "Classes.h"
using namespace std;

Classes::Classes() {
	role = knight;
	weapon = sword;
	int health = 0;	
	int action = 0;
	int dmg_dice = 0;
	int num_of_dice = 0;
	int attack_cost = 0;
}

Classes::Classes(roles s): role(s) {
	weapon = sword;
	switch (s) {
	case knight:
		health = 40;
		action = 3;
		break;
	case sorcerer:
		health = 25;
		action = 4;
		break;
	case rogue:
		health = 30;
		action = 5;
	}
}

Classes::~Classes() {
	health = 0;
	action = 0;
	dmg_dice = 0;
	num_of_dice = 0;
	attack_cost = 0;
}

void Classes::ChooseKnight() {
	int n;
	role = knight;
	do {
		cout << "CHOOSE YOUR WEAPON" << endl << "1) A sword (1k6, 1 action)" << endl << "2) A greataxe (2k8, 2 actions)" << endl;
		cin >> n;
	} while (!&n || n > 2 || n < 0);

	switch (n)
	{
	case 1:
		dmg_dice = 6;
		num_of_dice = 1;
		attack_cost = 1;
		weapon = sword;
		break;

	case 2:
		dmg_dice = 8;
		num_of_dice = 2;
		attack_cost = 2;
		weapon = greataxe;
	}

}

void Classes::ChooseRogue() {
	int n;
	role = rogue;
	do {
		cout << "CHOOSE YOUR WEAPON" << endl << "1) Knives (2k4, 1 action)" << endl << "2) Poison (1 dmg and poisons, 1 actions)" << endl;
		cin >> n;
	} while (!&n || n > 2 || n < 0);

	switch (n)
	{
	case 1:
		dmg_dice = 4;
		num_of_dice = 2;
		attack_cost = 1;
		weapon = knives;
		break;
	case 2:
		dmg_dice = 1;
		num_of_dice = 1;
		attack_cost = 1;
		weapon = poison;
	}

}

void Classes::ChooseSorcerer() {
	int n;
	role = sorcerer;
	do {
		cout << "CHOOSE YOUR SKILL" << endl << "1) A fireball (6k4, 3 action)" << endl << "2) An icebolt (3k2, 1 actions)" << endl;
		cin >> n;
	} while ( n > 2 || n < 1);

	switch (n)
	{
	case 1:
		dmg_dice = 4;
		num_of_dice = 6;
		attack_cost = 3;
		weapon = fireball;
		break;
	case 2:
		dmg_dice = 2;
		num_of_dice = 3;
		attack_cost = 1;
		weapon = frostbolt;
	}

}


ostream& operator<<(ostream& os, const Classes& p) {
	os << "Health: " << p.health << endl;
	if (p.action != 0) {
		os << "Actions left: " << p.action << endl;
	}
	else {
		os << "There are no actions left" << endl;
	}
	return os;
}

istream& operator>>(istream& os, Classes& p) {
	int n;
	do {
		cout << "CHOOSE YOUR DESTINY!" << endl << "1) A knight (40 health, 3 actions, can use swords and greataxes)" << endl;
		cout << "2) A sorcerer (25 health, 4 actions, can use fireballs and icebolts)" << endl;
		cout << "3) A rogue (30 health, 5 actions, can use knives or poison)" << endl << endl;
		os >> n;
	} while (!&n || n > 3 || n < 0);
	if (!&n)
		return os;

	switch (n)
	{
	case 1:
		p.health = 40;
		p.action = 3;
		p.ChooseKnight();
		break;
	case 2:
		p.health = 25;
		p.action = 4;
		p.ChooseSorcerer();
		break;
	case 3:
		p.health = 30;
		p.action = 5;
		p.ChooseRogue();
	}
	return os;

}


int GetDmg(int n, Classes p) {
	p.health -= n;
	return p.health;
}

int TakeAction(int n, Classes p) {
	p.action -= n;
	return p.action;
}

Classes& Classes::operator= (const Classes& rhs) {
	role = rhs.role;
	weapon = rhs.weapon;
	health = rhs.health;
	action = rhs.action;
	dmg_dice = rhs.dmg_dice;
	num_of_dice = rhs.num_of_dice;
	attack_cost = rhs.attack_cost;
	return *this;
}