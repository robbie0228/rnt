#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <map>
#include <string>
#include "enums.h"
#include "observer.h"

using std::string;
using std::map;
using std::vector;

struct StateType {
	// Which player is downloading a link, if any
	//   -1 if no player
	int downloadingPlayer;

	// The name of the link being downloaded, if any
	//   '.' if no link
	char downloadingLinkName;

	// The type of the link being downloaded, if any
	//   LinkType::NoType if no link
	LinkType downloadingLinkType;

	// Whether or not the link being downloaded is being revealed
	bool downloadingLinkIsRevealed;

	// Whether or not the link at this cell is being revealed
	bool linkIsRevealed;

	// Which player is using an ability, if any
	//   -1 if no player
	int playerUsingAbility;
};

struct InfoType {
	int row;
	int col;
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
