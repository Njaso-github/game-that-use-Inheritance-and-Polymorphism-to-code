#include <iostream>
#include <cstring>
#include <conio.h>
#include <ctime>
#include <cstdlib>
using namespace std;

class SkillTemplate;
class Boss; 
class Me;

class SkillTemplate {
public:
	virtual int m_attack() { 
		return 0;
	}
	virtual void m_strengthen() {}
};

class Boss: public SkillTemplate {
public:
	string m_name = "Boss";
	int m_health = 1500;
	int m_strength = 1;
	int m_attack() {
		return 200;
	}
	void m_strengthen() {
		m_strength++;
	}
};

class Me: public SkillTemplate {
public:
	string m_name = "Me";
	int m_health = 500;
	int m_strength = 1;
	int m_attack() {
		return 500;
	}
	void m_strengthen() {
		m_strength++;
	}
};

void panel(string name, string skill) {
	cout << name << " has " << skill << '\n';
}

void fight() {
	Boss boss;
	Me me;
	srand(time(NULL));
	while (boss.m_health > 0 && me.m_health > 0) {
		cout << boss.m_name << '(' << boss.m_strength << ')' <<  " Health: " << boss.m_health << '\n';
		cout << me.m_name << '(' << me.m_strength << ')' << " Health: " << me.m_health << '\n';
		while (true) {
			if (_kbhit()) {
				char ch = _getch();
				if (ch == '1') {
					boss.m_health -= int(me.m_attack() * (1.0 / boss.m_strength));
					panel(me.m_name, "attacked");
					break;
				} else if (ch == '2') {
					me.m_strengthen();
					panel(me.m_name, "strengthened");
					break;
				}
			}
		}
		if (boss.m_health <= 0) {
			cout << "--------------------" << '\n';
			break;
		}
		int RandomActionOfBoss = rand() % 2;
		switch(RandomActionOfBoss) {
			case 0:
				me.m_health -= int(boss.m_attack() * (1.0 / me.m_strength));
				panel(boss.m_name, "attacked");
				break;
			case 1:
				boss.m_strengthen();
				panel(boss.m_name, "strengthened");
				break;
		}
		cout << "--------------------" << '\n';
		if (me.m_health <= 0) break;
	}
	me.m_health > 0 ? boss.m_health = 0 : me.m_health = 0;
	cout << boss.m_name << " Health: " << boss.m_health << '\n';
	cout << me.m_name << " Health: " << me.m_health << '\n';
	cout << "WINNER: " << (me.m_health > 0 ? me.m_name : boss.m_name) << '\n';
	cout << "LOSSER: " << (me.m_health > 0 ? boss.m_name : me.m_name) << '\n';
}

int main() {
	cout << "RULE: " << '\n';
	cout << "Press 1 to attack" << '\n';
	cout << "Press 2 to strengthen" << '\n';
	cout << "The number in the bracket means the strength level" << '\n';
	cout << "--------------------" << '\n';
	fight();
	cout << "Press ESC to exit" << '\n';
	while (true) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 27) {
				break;
			}
		}
	}
	return 0;
}
