#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <map>
#include "observer.h"

class Subject {
		std::vector<Observer *> observers;
	public:
		void attach(Observer *o);  
		void notifyObservers();
		virtual std::map<std::string, std::string> getInfo() const = 0;
};

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

#endif
