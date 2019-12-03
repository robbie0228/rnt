#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer
{
public:
    // pass the Subject that called the notify method
    void notify(Subject &whoFrom) { doNotify(whoFrom); };
    virtual ~Observer() = default;
private:
    virtual void doNotify(Subject &whoFrom) = 0;
};

#endif
