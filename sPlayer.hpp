#ifndef SPLAYER_HPP
#define SPLAYER_HPP

#include <vector>
#include <string.h>

enum PlayState {
	New,
	Active,
	Died,
	Discon
};

class PlayerCharacter
{
	int fd;
	PlayState curMode;
	char accBuf[256];//ServerConnection::ReadMessage
	char strBuf[256];
	char login[50];
	int accBufSize;
	int curRoomIndex;
public:
	PlayerCharacter(int f)
	:fd(f), curMode(New), accBufSize(0), curRoomIndex(1){}
	int GetFd() {return fd;}
	int GetRoomIndex() {return curRoomIndex;}
	void SetRoomIndex(int r) {curRoomIndex = r;}
	void SetFd(int f) {fd =f;}
	char *GetAccBuf() {return accBuf;}
	char *GetStrBuf() {return strBuf;}
	void SetAccBufSize(int s) {
		if (s == 0)
			for (unsigned int i = 0; i < sizeof(accBuf); ++i)
				accBuf[i] = 0;
		accBufSize = s;
	}
	void ClearStrBuf() {
		for (unsigned int i = 0; i < sizeof(strBuf); ++i)
			strBuf[i] = 0;
	}
	int GetAccBufSize() {return accBufSize;}
	PlayState GetMode() {return curMode;}
	void SetLogin(char *log) {strcpy(login, log); curMode = Active;}
	const char *GetName() {return login;}
};

#endif