#ifndef __STRATEGY_H__
#define __STRATEGY_H__

class Strategy {
    public:
    virtual ~Strategy();
    virtual void rollDice(int& dicePoint, int seed) = 0;
};

class DiceRand : public Strategy {
    public:
    void rollDice(int& dicePoint, int seed) override;
};

class DiceLoad : public Strategy {
    public:
    void rollDice(int& dicePoint, int seed) override;
};

#endif
