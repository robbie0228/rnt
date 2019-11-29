#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <map>
#include <string>
#include "observer.h"

using std::string;
using std::map;
using std::vector;

struct StateType {
	int downloadingPlayer;
	LinkType downloadingLinkType;
	bool linkIsUpdated;
	bool linkIsRevealed;
};

struct InfoType {
	char name;
	LinkType type;
	int strength;
};

class Subject {
		vector<Observer *> observers;
		StateType state;
	public:
		void attach(Observer *o);  
		void notifyObservers();
		void setState(StateType newS);
		StateType getState() const;
		virtual InfoType getInfo() const = 0;
    	virtual ~Subject() {};
};

#endif
