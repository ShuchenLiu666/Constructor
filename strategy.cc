#include "strategy.h"
#include <random>

Strategy::~Strategy() {}

void DiceRand::rollDice(int& dicePoint, int seed) {
    static std::default_random_engine gen;
	static std::uniform_int_distribution<int> dist(2,12);
	static bool flag = false; 
	if (!flag) {
		gen.seed(seed);
		flag = true;
	}
    dicePoint = dist(gen);
}

void DiceLoad::rollDice(int& dicePoint, int seed) { }
