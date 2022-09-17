#pragma once

#include <string>

class Fighter
{
	public:
		static int maxHp;

		Fighter(std::string name, double defense, double strength, double speed);
		~Fighter();

		std::string name;

		double defense;
		double strength;
		double speed;
		double hp;

		void Attack(Fighter* enemyToAttack);
		void Damage(double attackersStrength);
		void Defend();
		void Rest();
	protected:

};
