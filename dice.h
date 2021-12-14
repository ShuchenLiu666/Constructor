#ifndef __DICE_H__
#define __DICE_H__
#include <memory>


// use of Dice:
// Dice dice = Dice{new DiceLoad, pointWeWant};   --- roll loaded dice
// Dice dice = Dice{new DiceRand, 0 (placeholder), seed};       --- roll random dice
// strategy should be wrapped insmart pointer

class Strategy;

class Dice {
    std::shared_ptr<Strategy> strategy;
    int dicePoint;
    int seed;
    public:
    Dice(std::shared_ptr<Strategy> strategy, int dicePoint = 0, int seed = 0);
    void setStrategy(std::shared_ptr<Strategy> strategy);
    void roll();
    void setPoint(int value);
    int getPoint();
};

#endif
