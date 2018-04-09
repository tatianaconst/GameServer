#ifndef SROOM_HPP
#define SROOM_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <vector>
#include <string.h>
#include <map>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "sThing.hpp"
#include "sThing.hpp"

typedef std::map<std::string, int> mapWays;

class Room {
	int id;
	char description[1000];
	std::vector<int> PlayersInside;
	std::vector<LivingObject*> hereLivObjects;
	char interactiveList[500];

	mapWays posRooms;
public:
	Room()
	:id(0)
	{}
	~Room(){}

	char *GetInteractiveList();
	mapWays GetPosRooms() {return posRooms;}
	void AddPlayer(int i) {PlayersInside.push_back(i);}
	void DelPlayer(int i) {
		PlayersInside.erase(std::remove(PlayersInside.begin(), PlayersInside.end(), i), PlayersInside.end());
	}
	bool TryToLeave(char* command, int* room);
	void SaveRoom();
	void SetDescription(char *d) {strcpy(description, d);}
	void SetId(int i) {id = i;}
	void AddWay(char *title, int id) {
		posRooms.insert(std::pair<std::string, int> (std::string(title), id));
	}
	void ActivateBehavior(int objId)
	{
		hereLivObjects[objId]->ActivateBehObject();
	}
	void ActivatePhysical(int objId)
	{
		hereLivObjects[objId]->ActivatePhysObject();
	}
	void AddLivObject(LivingObject *obj)
	{
		hereLivObjects.push_back(obj);
	}
	
};


#endif