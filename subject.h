#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <map>
#include <string>
#include "observer.h"

using std::string;
using std::map;
using std::vector;

class Subject {
		vector<Observer *> observers;
		map<string, string> state;
	public:
		void attach(Observer *o);  
		void notifyObservers();
		void setState(map<string, string> newS);
		map<string, string> getState() const;
		virtual map<string, string> getInfo() const = 0;
    	virtual ~Subject() {};
};

#endif
