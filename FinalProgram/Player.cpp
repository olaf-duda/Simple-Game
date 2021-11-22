#include "Player.h"
#include "Game.h"
using namespace std;
Player::Player() : defending(false), evading(false), IsPoisoned(false)
{
	declared_actions = new(nothrow)int [0];
	playernumber = 0;
	Classes temp;
	role = temp;
	potion = NoPotion;
}

Player::Player(Classes role, potions potion) :defending(false), evading(false), IsPoisoned(false), role(role), potion(potion)
{
	declared_actions = new int[0];
	playernumber = 0;
}

Player::~Player() {
	role.~Classes();
	playernumber = 0;
	defending = false;
	evading = false;
	IsPoisoned = false;

}

ostream& operator<<(ostream& os, const Player& p) {
	os << endl << "IT'S YOUR TURN, PLAYER NUMBER " << p.playernumber << endl << endl;
	os << "YOU HAVE " << p.role.ReturnHealth() << " HEALTH" << endl;
	os << "AND " << p.role.ReturnActions() << " ACTION POINTS" << endl << endl;

	return os;
}

istream& operator>>(istream& is, Player& p) 
{
	int n;
	cout << "HELLO PLAYER NUMBER " << p.playernumber << endl;
	is >> p.role;
	cout << "CHOOSE YOUR DRINK" << endl;
	cout << "1) Potion of Healing" << endl << "2) Potion of Action" << endl << "3) Potion of Defence" << endl;
	is >> n;
	switch (n) {
	case 1:
		p.potion = PotionOfHealing;
		break;
	case 2:
		p.potion = PotionOfAction;
		break;
	case 3:
		p.potion = PotionOfDefence;
	}
	cout << endl;
	return is;
}

int* Player::YourTurn() {
	int actionp = role.ReturnActions();
	cout << *this;
	int i = 0;
	do {
		i++;
		do {
	cout << endl << "AVAILABLE ACTIONS: " << endl;
			if (IsDefending() != true) {
				cout << "1) defending for 1 action point" << endl;
			}
			if (IsEvading() != true) {
				cout << "2) evading for 1 action point" << endl;
			}
			if (role.ReturnActions() >= role.ReturnAttackCost()) {
				cout << "3) atacking with ";

				switch (role.ReturnWeapon()) {
				case sword:
					cout << "sword for 1 action point" << endl;
					break;
				case greataxe:
					cout << "greataxe for 2 action point" << endl;
					break;
				case fireball:
					cout << "fireball for 3 action point" << endl;
					break;
				case frostbolt:
					cout << "frostbolt for 1 action point" << endl;
					break;
				case knives:
					cout << "knives for 1 action point" << endl;
					break;
				case poison:
					cout << "poison for 1 action point" << endl;
				}
			}
			if(potion != NoPotion)
				cout << "4) drinking potion for 1 action" << endl;
			int* temp = declared_actions;
			declared_actions = new(nothrow)int[i];
			for (int k = 0; k < i; k++) {
				declared_actions[k] = temp[k];
			}
			cin >> declared_actions[i - 1];
		} while (declared_actions[i - 1] > 4 || declared_actions[i - 1] < 1 || 
			((role.ReturnActions() < role.ReturnAttackCost()) && declared_actions[i - 1] == 3) || ((declared_actions[i - 1] == 4) && (potion == NoPotion))
			|| ((declared_actions[i - 1] == 1) && IsDefending()) || ((declared_actions[i - 1] == 2 )&& IsEvading()));

		if (declared_actions[i - 1] == 3) {
			role.UseAction(role.ReturnAttackCost());
		}
		else if (declared_actions[i - 1] == 1) {
			role.UseAction(1);
			defending = true;
		}
		else if (declared_actions[i - 1] == 4) {
			role.UseAction(1);
			switch (potion) {
			case PotionOfHealing:
				role.LooseHealth(-rand() % 6);
				break;
			case PotionOfAction:
				role.UseAction(-3);
				break;
			case PotionOfDefence:
				role.LooseHealth(-rand() % 2);
				defending = true;
				evading = true;
			}
			potion = NoPotion;
		}
		else {
			role.UseAction(1);
			evading = true;
		}
	}
	while (role.ReturnActions() != 0);
	sizeofda = i;
	role.UseAction(-actionp);
	return declared_actions;
}

int Player::TakeDmg(int damage) {
	if (IsEvading()) {
		cout << endl << "PLAYER " << playernumber << " IS EVADING" << endl;
		damage -= rand() % 3;
		if (damage <= 0)
			damage = 1;
		evading = false;
		IsPoisoned = false;
	}
	if (IsDefending()) {
		cout << endl << "PLAYER " << playernumber << " IS DEFENDING" << endl;
		damage = damage / 2;
		if (damage <= 0)
			damage = 1;
		defending = false;
	}
	if (damage == 100) {
		damage = 1;
		IsPoisoned = true;
	}
	cout << endl << "PLAYER " << playernumber << " TOOK " <<damage << " DAMAGE" << endl;
	role.LooseHealth(damage);
	if (role.ReturnHealth() < 0)
		role.LooseHealth(-role.ReturnHealth());
	return role.ReturnHealth();
}

int Player::DealDmg() {
	int dmg = 0;
	if (role.ReturnWeapon() == poison)
		return 100;
	for(int i = 0; i< role.ReturnNumDice(); i++)
		dmg += rand() % role.ReturnDmgDice();
	return dmg;
}

Player& Player::operator= (const Player& rhs){
	role = rhs.role;
	declared_actions = rhs.declared_actions;
	potion = rhs.potion;
	playernumber = rhs.playernumber;
	defending = rhs.defending;
	evading = rhs.evading;
	IsPoisoned = rhs.IsPoisoned;
	return *this;
}

bool Player::IsDefending() {
	return defending;
}
bool Player::IsEvading() {
	return evading;
}
bool Player::ReturnIsPoisoned() {
	return IsPoisoned;
}