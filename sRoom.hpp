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
#include <arpa/inet.h>
#include <unistd.h>
//#include "sCore.hpp"

class PlayerCharacter;

typedef std::map<std::string, int> mapWays;

class Room {
	//ServerLogic *gameServer;
	int id;
	char description[1000];
	std::vector<PlayerCharacter*> PlayersInside;
	//std::vector<int> PlayersInside;
	std::vector<LivingObject*> hereLivObjects;
	char interactiveList[500];

	mapWays posRooms;


	char posRoomsList[500];
	char posObjectsList[500];
public:
	Room(int i)
	: id(i)
	{}
	~Room(){}


	char *GetPosRoomsList() {return posRoomsList;}
	char *GetPosObjectsList() {return posObjectsList;}
	char *GetDesc(){return description;}
	char *GetInteractiveList();
	mapWays GetPosRooms() {return posRooms;}
	void AddPlayer(PlayerCharacter *pl);// {PlayersInside.push_back(pl);}
	void DelPlayer(PlayerCharacter *i);// {//  !!!!!!!!!!!!!!!!!!!!!!!!!!
		//PlayersInside.erase(std::remove(PlayersInside.begin(), PlayersInside.end(), i), PlayersInside.end());
	//}
	bool TryToLeave(char* command, int* room);
	void SaveRoom();
	void SetDescription(char *d) {strcpy(description, d);}
	void SetId(int i) {id = i;}
	void AddWay(char *title, int id) {
		posRooms.insert(std::pair<std::string, int> (std::string(title), id));
		char newroom[100];
		sprintf(newroom, "%d %s\n", id, title);
		strcat(posRoomsList, newroom);
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

		char newobj[50];
		sprintf(newobj, "%d %s", (int)hereLivObjects.size() - 1, obj->GetName());
		strcat(posObjectsList, newobj);
	}
	void CheckAction(int id, ActionType a) 
	{
		hereLivObjects[id]->CheckAction(a);
	}
	void SayToAll(const char *message, int myFd);
};


#endif