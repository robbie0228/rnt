#include "subject.h"

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

void Subject::setState(StateType newS) { state = newS; }

StateType Subject::getState() const { return state; }
