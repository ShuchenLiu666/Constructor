#include "dice.h"
#include "strategy.h"

Dice::Dice(std::shared_ptr<Strategy> strategy, int dicePoint, int seed)
    : strategy{strategy}, dicePoint{dicePoint}, seed{seed} {}

void Dice::setStrategy(std::shared_ptr<Strategy> strategy) {
        this->strategy = strategy;
}

void Dice::roll() {
    strategy->rollDice(dicePoint, seed);
}

int Dice::getPoint() {
    return dicePoint;
}

void Dice::setPoint(int value) {
    dicePoint = value;
}
