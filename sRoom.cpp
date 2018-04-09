#ifndef SROOM_CPP
#define SROOM_CPP


#include "sRoom.hpp"

char *Room::GetInteractiveList() 
{
	return interactiveList;
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