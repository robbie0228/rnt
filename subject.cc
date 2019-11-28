#include "subject.h"

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

void Subject::setState(map<string, string> newS) { state = newS; }

map<string, string> Subject::getState() const { return state; }
