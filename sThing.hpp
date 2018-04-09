#ifndef STHING_HPP
#define STHING_HPP

#include "sIntelib.hpp"
#include <string.h>

enum ObjState {
	NotReady,
	Idle,
	Working
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

	int passSec;
	char name[50];
	char moderProgram[1000];
	char plrProgram[1000];


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
	void PrintObject();
	ObjState GetState() {return currState;}
	void ChangeContinuation(StepCont c) {avalCont = c;}
	//void DoPhysicFunc(LReference ref);
	void DoPhysicFuncSay(const char* message);
	void DoPhysicFuncName();
	//void ReadProgramPhys(const char *prog);
private:

	void Say(const char *str);
	LExpressionPackage *PlayerPackage(LSymbol &main);
	LExpressionPackage *ModerPackage();
	void ReadProgram(const char *prog, StepCont contKind);
};

#endif 