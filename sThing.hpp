#ifndef STHING_HPP
#define STHING_HPP

#include "sIntelib.hpp"
#include <string.h>
//#include "sRoom.hpp"

class Room;

enum ObjState {
	NotReady,//  Nothing
	Idle,//      OnlyPhys
	Working//    Phys + Behavior
};

enum StepCont {
		physic,
		behavior
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
	static LSymbol FUNC_SAY;//("FUNC_SAY");
	static LSymbol FUNC_NAME;//("FUNC_NAME");
	static LSymbol FUNC_PAUSE;//("FUNC_PAUSE");

	ObjState currState;

	Room *currRoom;
	int *passSec;
	char name[50];
	char moderProgram[1000];
	char plrProgram[1000];
	//int roomId;

	LExpressionPackage *PhysPackage;
	LExpressionPackage *BehPackage;

	LListConstructor L;

	int PhysMark;
	int behMark;
	StepCont *avalCont;
public:
	LivingObject()
	:contPhys(0), contBeh(0), currState(NotReady),
	 PhysPackage(ModerPackage()), 
	 BehPackage(PlayerPackage(MAIN))
	{
		passSec = new int(0);
		avalCont = new StepCont(physic);
		sprintf(name, "NONAME");
	}
	~LivingObject(){}

	void ActivateBehObject();
	void ActivatePhysObject();
	void CheckAction(ActionType t);
	void PrintObject();
	void DoStep();
	void SayToAll(const char *str);
	void LoseSec(int s) {*passSec = s;}
	void ChangeContinuation(StepCont c) {*avalCont = c;printf("Change %d\n", c);}
	void ChangeAnswerContinuation();
	void DoPhysicFuncSay(const char* message);
	void DoPhysicFuncName();
	void DoPhysicFuncPause(int sec);



	void SetTitle(const char *t) {char tg[20]; strcpy(tg, t); strcpy(name, strtok(tg, "\n"));}
	void SetModerProgram(const char *t) 
	{
		strcpy(moderProgram, t); 
		currState = NotReady; 
		*avalCont = physic;
		*passSec = 0;
		//PhysMark = contPhys->GetMark();
	}
	void SetPlrProgram(const char *t) {strcpy(plrProgram, t);}
	void SetRoom(Room *r) {currRoom = r;}

	ObjState GetState() {return currState;}
	LispContinuation *GetBehCont() {return contBeh;}
	const char *GetName() {return name;}
	
private:
	
	LExpressionPackage *PlayerPackage(LSymbol &main);
	LExpressionPackage *ModerPackage();
	void ReadProgram(const char *prog, StepCont contKind);
};

#endif 