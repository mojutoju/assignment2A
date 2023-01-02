#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <time.h>
#include "Game.h"
#include "GameTester.h"
using namespace std;

void pause() {
	cout << "Press enter to continue..." << endl;
	string s;
	getline(cin, s);
}

class Shop {

	vector<unique_ptr<Object>> shopItems_;

public:

	Shop() {
		unique_ptr<Food> p1 = make_unique<Food>("apple", 10);
		unique_ptr<Food> p2 = make_unique<Food>("bread", 20);
		unique_ptr<Weapon> p3 = make_unique<Weapon>("sword", 30);
		unique_ptr<Weapon> p4 = make_unique<Weapon>("gun", 60);
		unique_ptr<Armour> p5 = make_unique<Armour>("shield", 40);
		unique_ptr<Armour> p6 = make_unique<Armour>("helmet", 20);

		shopItems_.push_back(std::move(p1));
		shopItems_.push_back(std::move(p2));
		shopItems_.push_back(std::move(p3));
		shopItems_.push_back(std::move(p4));
		shopItems_.push_back(std::move(p5));
		shopItems_.push_back(std::move(p6));
	}

	void visitShop(Player& p) {

		int i = rand() % shopItems_.size();
		if (shopItems_[i] != nullptr) { // else item gone
			cout << "You picked up a " << shopItems_[i]->getName() << endl;
			p.pickup(std::move(shopItems_[i]));
		}
	}

};

void askAndUseItem(Player& p) {

	if (p.getInventory() == "List of items: none") return;

	cout << "Do you want to use an item? [y/n]" << endl;
	string s;
	getline(cin, s);
	if (s == "y") {
		cout << "Which item?" << endl;
		getline(cin,s);
		if (p.use(s)) {
			cout << "Item used, updated player status:" << endl;
			cout << p << endl;
		}
		else cout << "You don't have such an item." << endl;
		pause();
	}
}

void visitDoctor(Player& p) {

	if (p.getHealth() == 100) return;

	cout << "You encounter a doctor who tries to heal you." << endl;
	Healer d("doctor");
	d.heal(p);
	cout << "Your health is now " << p.getHealth() << endl;
	pause();
}

int main(int argc, char* argv[]) {

	srand(time(0));

	Fighter a("alice");
	Fighter b("bob");
	Shop shop;

	try {
		while(a.getHealth() > 0 && b.getHealth() > 0) {

			cout << "---------- A's turn ----------" << endl;

			if (rand() % 5 == 0) visitDoctor(a);

			if (rand() % 2) shop.visitShop(a);

			askAndUseItem(a);

			a.attack(b);
			cout << a.getName() + " attacks " + b.getName() + ", result:" << endl;
			cout << a << endl;
			cout << b << endl;

			pause();

			cout << "---------- B's turn ----------" << endl;

			if (rand() % 5 == 0) visitDoctor(b);

			if (rand() % 2) shop.visitShop(b);

			askAndUseItem(b);

			b.attack(a);
			cout << b.getName() + " attacks " + a.getName() + ", result: " << endl;
			cout << a << endl;
			cout << b << endl;

			pause();
		}
	}
	catch(const std::logic_error& e) {
		cout << e.what() << endl;
	}

	if (a.getHealth() == 0) cout << "B won!" << endl;
	else if (b.getHealth() == 0) cout << "A won!" << endl;



for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { GameTester t; t.testa(); } break;
		case 'b': { GameTester t; t.testb(); } break;
		case 'c': { GameTester t; t.testc(); } break;
		case 'd': { GameTester t; t.testd(); } break;
		case 'e': { GameTester t; t.teste(); } break;
		case 'f': { GameTester t; t.testf(); } break;
		case 'g': { GameTester t; t.testg(); } break;
		case 'h': { GameTester t; t.testh(); } break;
		case 'i': { GameTester t; t.testi(); } break;
		case 'j': { GameTester t; t.testj(); } break;
		case 'k': { GameTester t; t.testk(); } break;
		case 'l': { GameTester t; t.testl(); } break;
		case 'm': { GameTester t; t.testm(); } break;
		case 'n': { GameTester t; t.testn(); } break;
		case 'o': { GameTester t; t.testo(); } break;
		case 'p': { GameTester t; t.testp(); } break;
		case 'q': { GameTester t; t.testq(); } break;
		case 'r': { GameTester t; t.testr(); } break;
		case 's': { GameTester t; t.tests(); } break;
		case 't': { GameTester t; t.testt(); } break;
		case 'u': { GameTester t; t.testu(); } break;
		case 'v': { GameTester t; t.testv(); } break;
		case 'w': { GameTester t; t.testw(); } break;
		case 'x': { GameTester t; t.testx(); } break;
		case 'y': { GameTester t; t.testy(); } break;
		case 'z': { GameTester t; t.testz(); } break;
		default: { cout << "Options are a -- y." << endl; } break;
	       	}
	}
	return 0;

}
