#ifndef SCORE_CPP
#define SCORE_CPP

#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include "sCore.hpp"
#include "sRoom.hpp"
#include <string.h>
#include <sys/time.h>



ServerConnection::ServerConnection(int port)
:gameLogic(this)
{
	lstSocket = socket (AF_INET, SOCK_STREAM, 0);
	if (!lstSocket)
		throw "Invalid listening socket initialization";

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons (port);
	addr.sin_addr.s_addr = INADDR_ANY;

	int opt = 1;
	setsockopt (lstSocket,SOL_SOCKET,SO_REUSEADDR,&opt, sizeof(opt));
	if (0 != bind (lstSocket, (struct sockaddr*) &addr, sizeof(addr)))
		throw "Invalid binding";
	if (-1 == listen(lstSocket, 5))
		throw "Invalid listening";
}
void ServerLogic::DoActions()
{
	for (uint i = 0; i < allLivObjects.size(); i++) {
		if (allLivObjects[i]->GetState() == Working || allLivObjects[i]->GetState() == Idle) {
			allLivObjects[i]->DoStep();
		}
	}
}

void ServerConnection::startGame()
{
//	ServerLogic gameLogic;
	gameLogic.LoadRooms();
	gameLogic.SaveRooms();
	numberConnections = 0;
	int maxDesc;
	std::vector<PlayerCharacter*> *plVec = gameLogic.GetPlayers();
//Set updating
	for (;;) {
		fd_set readFds;
		maxDesc = lstSocket;
		FD_ZERO (&readFds);
		FD_SET (lstSocket, &readFds);
		
		for (unsigned int i = 0; i < plVec->size(); ++i) {
			//std::cout << "Size" << plVec->size() << std::endl;
			int fd = (*plVec)[i]->GetFd();
			if (fd) {
				//std::cout << "Fd" << (*plVec)[i].GetFd() << std::endl;
				FD_SET(fd, &readFds);
				if (fd > maxDesc)
					maxDesc = fd;
			}
		}
//Continuation actions
		timeval timeStruct;
		gettimeofday(&timeStruct, NULL);
		timeStruct.tv_sec = 0;
		timeStruct.tv_usec = 3000000 - timeStruct.tv_usec;

		errno = 0;
		int res = select(maxDesc+1, &readFds, 0, 0,  &timeStruct);
		if (res < 0) perror("Select");
		if (res == 0) {
			//printf("Action\n");
			gameLogic.DoActions();
		}
//Add new player
		if (FD_ISSET (lstSocket, &readFds)) {
			int sd = accept(lstSocket, NULL, NULL);
			if (sd == -1) throw "Accept";
			if (0 == gameLogic.NewPlayer(sd))
				++ numberConnections;
		}
		// else {
//Message received
			//plVec = gameLogic.GetPlayers();
			for (int i = 0; i < plVec->size(); ++i) {
				int fd = (*plVec)[i]->GetFd();
				if (fd > 0) {
					if (FD_ISSET (fd, &readFds)) {
						if (!ReadMessage(i))
							(*plVec)[i]->SetFd(-1);
						gameLogic.DefineCmd(i);
					}
					//std::cout <<
				}
			}
		// }
	}
}

const char cmd_create[] = "CREATE";//create a programming object
const char cmd_addfunc[] = "ADDFUNC";



// const char cmd_room[] = "ROOM";//get number of current room
// const char cmd_look[] = "LOOK";//get description of current room
// const char cmd_ways[] = "WAYS";//get list of possible wa34у2цй1 2ys
// const char cmd_lookobj[] = "LOOKOBJ";//get list of objects
// const char cmd_delobj[] = "DELOBJ";//[n] delete object n
// const char cmd_read_obj[] = "READOBJ";//[n] get info of object n
// const char cmd_take[] = "TAKE";//[n] take object n
// const char cmd_read[] = "READ";//get info of your object
// const char cmd_act_obj[] = "ACTIVE";//[n] turn on object n
// const char cmd_off_obj[] = "OFF";//[n] turn off object n
// const char cmd_make[] = "MAKE";//[n]<info> create room n
// const char cmd_port[] = "PORT";//[n] port to room n
// const char cmd_makeway[] = "MAKEWAY";//[n]<way> create way to room n
// const char cmd_obj[] = "OBJECT";//<name><info> create object
// const char cmd_put[] = "PUT";//add your object to room
// //const char cmd_lisp[] = "LISP";
const char cmd_login[] = "LOGIN";//change login
const char cmd_say[] = "SAY";//change login
const char cmd_rnd[] = "AROUND";
const char cmd_way[] = "WAY";
const char cmd_beh[] = "B";
const char cmd_phy[] = "PHYS";
const char cmd_tch[] = "TOUCH";
const char cmd_crt[] = "CREATE";
const char cmd_title[] = "TITLE";
const char cmd_moderprog[] = "MODERPROG";
const char cmd_playerprog[] = "PLAYERPROG";

bool ServerLogic::DefineCmd(int i)
{
	// if (playChar[i].GetMode() == New) {
	// 	printf("WTF\n");
	// 	char message[] = "Enter command [login <your login>]\n";
	// 	write(playChar[i].GetFd(), message, strlen(message) + 1);
	// }
	char command[1024]; 
	char saveString[1024]; 
	strcpy(command, playChar[i]->GetStrBuf());
	strcpy(saveString, playChar[i]->GetStrBuf());
	//std::cout << playChar[i].GetStrBuf() << std::endl;
	//std::cout << command << std::endl;
	if (command[0] == 0) {
		return true;
	}
	for (uint ic = 0; ic < strlen(command); ++ic)
		if ((command[ic] >= 'a') && (command[ic] <= 'z'))
			command[ic] = command[ic] - 32;
	std::cout << command << std::endl;

	char firstWord[50];
	char restWords[1000];
	strcpy(firstWord, strtok(command, " \t"));
	strcpy(restWords, playChar[i]->GetStrBuf() + strlen(firstWord) + 1);
	// std::cout << " : " << restWords << std::endl;
	// std::cout << firstWord << std::endl;
	
//To do map with commands and functions
	if (strcmp(firstWord, cmd_say) == 0) {
		std::cout << "[SAY] " << restWords << std::endl;
		int roomId = playChar[i]->GetRoomIndex();
		int fd = playChar[i]->GetFd();
		allRooms[roomId]->SayToAll(restWords, fd, playChar[i]->GetName());
		return true;
	}

	if (strcmp(firstWord, cmd_login) == 0) {
		std::cout << "[LOGIN] " << restWords << std::endl;
		playChar[i]->SetLogin(restWords);
		return true;
	}
	if (strcmp(firstWord, cmd_rnd) == 0) {
		char makedesc[1000];
		int roomId = playChar[i]->GetRoomIndex();
		sprintf(makedesc, "%s\nPossible ways:\n%s\nPossible objects:\n%s\n",
			allRooms[roomId]->GetDesc(), allRooms[roomId]->GetPosRoomsList(),
			allRooms[roomId]->GetPosObjectsList());
		// strcat(makedesc, allRooms[roomId].GetDesc());
		// strcat(makedesc, allRooms[roomId].GetPosRoomsList());
		// strcat(makedesc, allRooms[roomId].GetPosObjectsList());
		write(playChar[i]->GetFd(), makedesc, strlen(makedesc) + 1);
	}
	if (strcmp(firstWord, cmd_beh) == 0) {
		int objId = atoi(restWords);

		int roomId = playChar[i]->GetRoomIndex();
		//allRooms[roomId]->ActivatePhysical(objId);
		allRooms[roomId]->ActivateBehavior(objId);
	}
	if (strcmp(firstWord, cmd_tch) == 0) {
		int objId = atoi(restWords);

		int roomId = playChar[i]->GetRoomIndex();
		allRooms[roomId]->CheckAction(objId, touch);
	}
	if (strcmp(firstWord, cmd_phy) == 0) {
		int objId = atoi(restWords);

		int roomId = playChar[i]->GetRoomIndex();
		allRooms[roomId]->ActivatePhysical(objId);
	}
	// if (strcmp(firstWord, cmd_crt) == 0) {
	// 	int objId = atoi(restWords);

	// 	int roomId = playChar[i].GetRoomIndex();
	// 	allRooms[roomId].ActivatePhysical(objId);
	// }
	// if (strcmp(firstWord, cmd_title) == 0) {
	// 	int objId = atoi(restWords);

	// 	int roomId = playChar[i].GetRoomIndex();
	// 	allRooms[roomId].ActivatePhysical(objId);
	// }
	// if (strcmp(firstWord, cmd_moderprog) == 0) {
	// 	int objId = atoi(restWords);

	// 	int roomId = playChar[i].GetRoomIndex();
	// 	allRooms[roomId].ActivatePhysical(objId);
	// }
	// if (strcmp(firstWord, cmd_playerprog) == 0) {
	// 	int objId = atoi(restWords);

	// 	int roomId = playChar[i].GetRoomIndex();
	// 	allRooms[roomId].ActivatePhysical(objId);
	// }
	if (strcmp(firstWord, cmd_way) == 0) {
		std::cout << "[WAY] " << std::endl;
		char secondWord[20];
		strcpy(secondWord, strtok(NULL, " "));
		int roomId = playChar[i]->GetRoomIndex();
		Room *curRoom = allRooms[roomId];
		int nextRoomIdx = (curRoom->GetPosRooms())[std::string(secondWord)];
		std::cout << "WAY " << secondWord << nextRoomIdx << std::endl;
		if (nextRoomIdx != 0) {
			char mes[100];
			sprintf(mes, "[WAY] [%s]", secondWord);
			write(playChar[i]->GetFd(), mes, strlen(mes) + 1);
			playChar[i]->SetRoomIndex(nextRoomIdx);
		} else {
			char mes[] = "No such way\n";
			write(playChar[i]->GetFd(), mes, strlen(mes) + 1);
		}
		
		//write(playChar[i].GetFd(), message, strlen(message) + 1);
	}
	playChar[i]->ClearStrBuf();
	return true;
}

void ServerLogic::LoadRooms()
{
	char fileName[20], curString[200];
	int fileId = 1;
	sprintf(fileName, "./savedRooms/%05d", fileId);
	std::cout << fileName << std::endl;
	FILE *file;
	int creatingObjecyIndex;
	LivingObject *newLivObj;
	while (NULL != (file = fopen(fileName, "r"))) {
		int newRoomId;
		// Room *newRoom = new Room(newRoomId);
		while (fgets(curString, 200, file)) {
			char saveString[200];
			strcpy(saveString, curString);
			strtok(curString, "\n");
			printf("%s\n", curString);
			char firstWord[20];
			strcpy(firstWord, strtok(curString, " "));
			char *restWords = strtok(NULL, " ");
			if (0 == strcmp(firstWord, "/number/")) {
				newRoomId = atoi(restWords);
				if (allRooms.size() < newRoomId + 1) {
					allRooms.resize(newRoomId + 1, NULL);
				}
				allRooms[newRoomId] = new Room(newRoomId);
				allRooms[newRoomId]->SetId(newRoomId);
				//std::cout << newRoomId << std::endl;
			}
			if (0 == strcmp(firstWord, "/description/")) {
				allRooms[newRoomId]->SetDescription(restWords);
			}
			if (0 == strcmp(firstWord, "/way/")) {
				int wayRoomId = atoi(restWords);
				restWords = strtok(NULL, " ");
				if (allRooms.size() < wayRoomId + 1) {
					allRooms.resize(wayRoomId + 1);
				}
				if (allRooms[wayRoomId] == NULL) {	
					allRooms[wayRoomId] = new Room(wayRoomId);
				}
				allRooms[wayRoomId]->SetId(wayRoomId);
				char titleWay[20];
				strcpy(titleWay, restWords);
				std::string titleWayStr(titleWay);
				std::cout << titleWayStr << std::endl;
				allRooms[newRoomId]->AddWay(titleWay, wayRoomId);
			}
			if (0 == strcmp(firstWord, "/object/")) {
				newLivObj = new LivingObject();
				newLivObj->SetRoom(allRooms[newRoomId]);
			}
			if (0 == strcmp(firstWord, "/title/")) {
				newLivObj->SetTitle(saveString + strlen(firstWord));
			}
			if (0 == strcmp(firstWord, "/behavior/")) {
				newLivObj->SetPlrProgram(saveString + strlen(firstWord));
			}	
			if (0 == strcmp(firstWord, "/physic/")) {
				newLivObj->SetModerProgram(saveString + strlen(firstWord));
			}
			if (0 == strcmp(firstWord, "/endobject/")) {
				allLivObjects.push_back(newLivObj);
				allRooms[newRoomId]->AddLivObject(newLivObj);
				newLivObj->ActivatePhysObject();
				newLivObj->PrintObject();
				newLivObj = NULL;

			}
		}
		fclose(file);
		fileId++;
		sprintf(fileName, "./savedRooms/%05d", fileId);
	}
}

int ServerConnection::DefineBuf (char *plbuf, char *plcmd, int size)
{
	bool f = false;
	int i, j, h, res;
	for (i = 0; plbuf[i] != 0; ++i) {
		if (plbuf[i] == '\n') {
			f = true;
			++i;
			break;
		}
	}
	//std::cout << "Size" << size << "i" << i << std::endl;
	res = size - i;
	if (f) {
		for (j = 0; plbuf[j] == ' '; ++j);
			for (h = 0; plbuf[j] != '\n'; ++j, ++h) {
				if (plbuf[j] == '\r') {
					--h;
					continue;
				}
				if (plbuf[j] != ' ')
					plcmd[h] = plbuf[j];
				else {
					plcmd[h] = ' ';
					++j;
					while (plbuf[j] == ' ')
						++j;
					--j;
				}
			}
		if ((h > 1) && (plcmd[h - 1] == ' '))
			plcmd[h - 1] = 0;
		else
			plcmd[h] = 0;
		for (j = 0; plbuf[j + i] != 0; ++j)
			plbuf[j] = plbuf[j + i];
		plbuf[j] = 0;
	}
	//std::cout << "Res" << res << std::endl;
	return res;
}

int ServerConnection::ReadMessage(int i)
{
	std::vector<PlayerCharacter*> *plVec = gameLogic.GetPlayers();
	char *buf = (*plVec)[i]->GetAccBuf();
	int fd = (*plVec)[i]->GetFd();
	int size = (*plVec)[i]->GetAccBufSize();

	int rc = read (fd, buf + size, 256 - size - 1);
	if (rc) {
		buf[rc + size] = 0;
		size = rc + size;
		(*plVec)[i]->SetAccBufSize(rc + size);
		//std::cout << "SetSize " << rc + size << std::endl;
	}

	char *strBuf = (*plVec)[i]->GetStrBuf();
	while ((buf[0] == 0)||(buf[0] == '\n'))
		for (int j = 0; j < size + rc; ++j)
			buf[j] = buf[j+1];
	if (buf[0] != 0) {
		(*plVec)[i]->SetAccBufSize(DefineBuf(buf, strBuf, size));
		//std::cout << "BUF " << buf << " CMD " << strBuf << std::endl;
		//std::cout << "BUF " << buf << " CMD " << (*plVec)[i].GetStrBuf() << std::endl;
	}
	return rc;
}

int ServerLogic::NewPlayer(int sd)
{
	PlayerCharacter *newPlay = new PlayerCharacter(sd);
	playChar.push_back(newPlay);
	allRooms[1]->AddPlayer(newPlay);
	return 0;
}


int main(int argc, char **argv)
{
	try {
		if (argc != 2)
			throw "Invalid input format";

		int serverPort = atoi(argv[1]);
		if (! serverPort)
			throw "Invalid port";
		ServerConnection gameServer(serverPort);
		gameServer.startGame();
	}
	catch (const char* str) {
		fprintf(stderr, "ERROR: %s\n", str);
		exit(1);
	}
	catch (...) {
		fprintf(stderr, "MAIN EXEPTION\n");
		exit(1);
	}
	return 0;
}

#endif