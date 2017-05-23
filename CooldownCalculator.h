#ifndef COOLDOWNCALCULATOR_H
#define COOLDOWNCALCULATOR_H


class CooldownCalculator
{
public:
    CooldownCalculator(float cooldownMS);
    float cooldownMS;
    float remaining;
    void start() {
        remaining = cooldownMS;
    }

    void clear() {
        remaining = 0;
    }

    void cool(float howMuch) {
        if(remaining>howMuch)
            remaining-=howMuch;
        else
            remaining = 0;
    }
    bool isCold() const {
        return remaining<=0;
    }
};

#endif // COOLDOWNCALCULATOR_H
