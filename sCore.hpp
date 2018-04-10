#ifndef SCORE_HPP
#define SCORE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <vector>
#include "sPlayer.hpp"
#include "sRoom.hpp"
#include "sThing.hpp"

class ServerConnection;


class ServerCommands
{
public:
	ServerCommands(){}
	~ServerCommands(){}


void Say(char *message)
{
	//printf(message);
}

};

class ServerLogic 
{
	ServerConnection *connect;
	std::vector<Room*> allRooms;
	std::vector<PlayerCharacter*> playChar;
	std::vector<LivingObject*> allLivObjects;
	ServerCommands cmd;

	
public:
	ServerLogic(ServerConnection *s)
	:connect(s)
	{}
	~ServerLogic(){}

	void LoadRooms();
	void SaveRooms() {for(unsigned int i = 1; i < allRooms.size(); ++i) allRooms[i]->SaveRoom();}
	int NewPlayer(int sd);
	std::vector<PlayerCharacter*> *GetPlayers() {return &playChar;}
	bool DefineCmd(int i);
	void DoActions();
};

class ServerConnection 
{
	int lstSocket;
	int numberConnections;
	ServerLogic gameLogic;

public:
	ServerConnection(int port);
	~ServerConnection(){};

	void startGame();
	void WriteToPlayer(int fd, char *message)
	{
		write(fd, message, strlen(message) + 1);
	}
private:
	int ReadMessage(int i);
	int DefineBuf(char *plbuf, char *plcmd, int size);
};
#endif