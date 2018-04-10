#ifndef SROOM_CPP
#define SROOM_CPP


#include "sRoom.hpp"
#include "sPlayer.hpp"
char *Room::GetInteractiveList() 
{
	return interactiveList;
}

void Room::DelPlayer(PlayerCharacter *i) 
{//  !!!!!!!!!!!!!!!!!!!!!!!!!!
	PlayersInside.erase(std::remove(PlayersInside.begin(), PlayersInside.end(), i), PlayersInside.end());
}

void Room::AddPlayer(PlayerCharacter *pl) 
{
	PlayersInside.push_back(pl);
}

bool Room::TryToLeave(char* command, int* room)
{
	std::string com(command);
	mapWays::iterator it;
	it = posRooms.find(com);
	if (it != posRooms.end()) {
		*room = it->second;
		return true;
	}
	return false;
}

void Room::SayToAll(const char *message, int myFd) {
	printf("Players inside: %d\n", PlayersInside.size());
	for (unsigned i = 0; i < PlayersInside.size(); ++i) {
		if (myFd != PlayersInside[i]->GetFd()) {
			write(PlayersInside[i]->GetFd(), message, strlen(message) + 1);
		}
		else {
			char mess[100];
			sprintf(mess, "[SAY] %s\n", message);
			write(myFd, mess, strlen(mess) + 1);
		}
	}
}

void Room::SaveRoom() 
{
	if (id == 0) return;
	printf("Save %d\n", id);
	char fileName[32];
	sprintf(fileName, "./savedRooms/%06d", id);
	FILE *file = fopen(fileName, "w");

	char nextString[1000];

	sprintf(nextString, "/number/ %d\n", id);
	fwrite(nextString, strlen(nextString), 1, file);

	sprintf(nextString, "/description/ %s\n\n", description);
	fwrite(nextString, strlen(nextString), 1, file);

	for (mapWays::const_iterator it(posRooms.begin()); it != posRooms.end(); ++it) {
		sprintf(nextString, "/way/ %d %s\n", it->second, it->first.c_str());
		fwrite(nextString, strlen(nextString), 1, file);
	}

	fclose(file);
}

#endif