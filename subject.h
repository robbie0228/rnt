#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <map>
#include <string>
#include "observer.h"

using std::string, std::map, std::vector;

class Subject {
		vector<Observer *> observers;
		map<string, string> state;
	public:
		void attach(Observer *o);  
		void notifyObservers();
		void setState(map<string, string> newS);
		map<string, string> getState() const;
		virtual map<string, string> getInfo() const = 0;
};

void Subject::attach(Observer *o) {
  observers.emplace_back(o);
}

void Subject::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

void Subject::setState(map<string, string> newS) { state = newS; }

map<string, string> Subject::getState() const { return state; }

#endif
