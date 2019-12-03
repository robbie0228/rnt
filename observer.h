#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
    public:
        void notify(Subject &whoFrom) { doNotify(whoFrom); };
        virtual ~Observer() = default;
    private:
        virtual void doNotify(Subject &whoFrom) = 0;
};

#endif
