#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>

class Observer;

class Subject {
    protected:
    std::vector<Observer*> observers;
    public:
    virtual ~Subject() = default;
    void attach(Observer * o);
    virtual void notifyObservers() = 0;
};

#endif
