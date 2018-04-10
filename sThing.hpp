#ifndef STHING_HPP
#define STHING_HPP

#include "sIntelib.hpp"
#include <string.h>
//#include "sRoom.hpp"

class Room;

enum ObjState {
	NotReady,
	Idle,
	Working
};

enum ActionType {
	touch
};

class Object 
{
	LispContinuation *lspCont;
	static LSymbol MAIN;
	LExpressionPackage *ReaderPackage(LSymbol &main);
	ObjState currState;
public:
	Object(){}
	virtual ~Object(){}
};

class LivingObject
{
	LispContinuation *contPhys;
	LispContinuation *contBeh;

	static LSymbol MAIN;

	ObjState currState;

	Room *currRoom;
	int passSec;
	char name[50];
	char moderProgram[1000];
	char plrProgram[1000];
	int roomId;

	LReference PhysPackage;
	LReference BehPackage;

	int PhysMark;
	int behMark;
public:
	enum StepCont {
			physic,
			behavior
		};
private:	
	StepCont avalCont;
public:
	LivingObject()
	:contPhys(0), contBeh(0), currState(Idle),
	 passSec(0),
	 PhysPackage(ModerPackage()), 
	 BehPackage(PlayerPackage(MAIN)),
	 avalCont(physic)
	{}
	~LivingObject(){}

	void ActivateBehObject();
	void ActivatePhysObject();
	void DoStep();
	void SetTitle(const char *t) {strcpy(name, t);}
	void SetModerProgram(const char *t) {strcpy(moderProgram, t);}
	void SetPlrProgram(const char *t) {strcpy(plrProgram, t);}
	void SetRoomId(int id) {roomId = id;}
	void PrintObject();
	ObjState GetState() {return currState;}
	const char *GetName() {return name;}
	void ChangeContinuation(StepCont c) {avalCont = c;}
	//void DoPhysicFunc(LReference ref);
	void DoPhysicFuncSay(const char* message);
	void DoPhysicFuncName();
	//void ReadProgramPhys(const char *prog);
	void CheckAction(ActionType t);
	void SayToAll(const char *str);
private:

	
	LExpressionPackage *PlayerPackage(LSymbol &main);
	LExpressionPackage *ModerPackage();
	void ReadProgram(const char *prog, StepCont contKind);
};

#endif 