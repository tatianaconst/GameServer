#ifndef STHING_CPP
#define STHING_CPP

#include "sThing.hpp"
#include "sRoom.hpp"

typedef struct RefNode {
			LReference ref;
			struct RefNode *next;
} RefNode;

LSymbol LivingObject::MAIN("MAIN");
LSymbol LivingObject::FUNC_SAY("FUNC_SAY");
LSymbol LivingObject::FUNC_NAME("FUNC_NAME");
LSymbol LivingObject::FUNC_PAUSE("FUNC_PAUSE");



LFunctionalSymbol<LFunctionCompiledDefun>  DEFUN("DEFUN");
LFunctionalSymbol<LFunctionCond>  COND("COND");
LFunctionalSymbol<LFunctionEq>  EQ("EQ");
LFunctionalSymbol<LFunctionEql>  EQL("EQL");

LFunctionalSymbol<LFunctionDefaultSay>  DEFAULT_SAY ("DEFAULT_SAY");
LFunctionalSymbol<LFunctionDefaultPause>  DEFAULT_PAUSE ("DEFAULT_PAUSE");
LFunctionalSymbol<LFunctionDefaultName>  DEFAULT_NAME ("DEFAULT_NAME");

void LivingObject::ReadProgram(const char *prog, StepCont contKind)
{
	IntelibReader reader;
	if (contKind == behavior) {
		reader.SetPackage(BehPackage);//
	}
	else {
		LSymbol MYOBJ("MYOBJ");
		SReference ref = new SExpressionLivingObject(this);
		MYOBJ->SetDynamicValue(ref);
		PhysPackage->Import(MYOBJ);
		reader.SetPackage(PhysPackage);
	}
	RefNode *refList = NULL, *refP;
	SStreamCharbuf bufProgram(prog);

	LReference ref = reader.Read(bufProgram);
	while (ref != IntelibReader::EofMarker) {
		refP = new RefNode;
		refP -> ref = ref;
		refP -> next = refList;
		refList = refP;
		ref = reader.Read(bufProgram);
	}
	while (refList != NULL) {
		if (contKind == behavior) {
			contBeh->PushTodo(LispContinuation::just_evaluate, refList->ref);//
		}
		else {
			contPhys->PushTodo(LispContinuation::just_evaluate, refList->ref);
		}
		refP = refList->next;
		delete(refList);
		refList = refP;
	}
}

void LivingObject::CheckAction(ActionType t)
{	
	char funCall[1000];
	switch(t) {
		case touch:
			sprintf(funCall, "(REACTION MYOBJ \"TOUCH\")");
			break;
	}
	
	ReadProgram(funCall, physic);
	ChangeContinuation(physic);
}




void LivingObject::ChangeAnswerContinuation() 
{
	printf("ChangeAnswer\n");
	SReference ref, refNil;
	contPhys->PopResult(ref);
	contBeh->PopResult(refNil);
	printf("PhysRes: %s\n", ref.GetPtr()->TextRepresentation().c_str());
	printf("BehRes: %s\n", refNil.GetPtr()->TextRepresentation().c_str());
	contPhys->PushResult(ref);
	contBeh->PushResult(ref);
}


void LivingObject::DoPhysicFuncSay(const char *message)
{	
	SReference MyObj = new SExpressionLivingObject(this);
	SReference Str = new SExpressionString(message);
	//LListConstructor L;
	SReference sayCall = (L| FUNC_SAY, MyObj, Str);
	//printf("Im HERE: %s\n", sayCall.GetPtr()->TextRepresentation().c_str());
	contPhys -> PushTodo(LispContinuation::just_evaluate, sayCall);
}

void LivingObject::DoPhysicFuncName()
{
	//ReadProgram("(FUNC_NAME MYOBJ)", physic);

	SReference MyObj = new SExpressionLivingObject(this);
	SReference nameCall = (L| FUNC_NAME, MyObj);
	
	contPhys -> PushTodo(LispContinuation::just_evaluate, nameCall);
}

void LivingObject::DoPhysicFuncPause(int sec)
{
	//PhysMark = contPhys->GetMark();

	SReference Pause = PhysPackage->FindSymbol("FUNC_PAUSE");
	SReference MyObj = new SExpressionLivingObject(this);
	SReference Sec = new SExpressionInt(sec);
	//LListConstructor L;
	SReference pauseCall = (L| Pause, MyObj, Sec);
	contPhys -> PushTodo(LispContinuation::just_evaluate, pauseCall);
}

void LivingObject::ActivatePhysObject() 
{
	try {
		contPhys = new LispContinuation;
		ReadProgram(moderProgram, physic);


		SReference Defun = PhysPackage->FindSymbol("DEFUN");


		//SReference Func_Say = PhysPackage->FindSymbol("FUNC_SAY");
		SReference Obj = PhysPackage->Intern("OBJ");
		SReference Str = PhysPackage->Intern("STR");
		SReference Default_Say = PhysPackage->FindSymbol("DEFAULT_SAY");
		SReference progSay = (L| DEFUN, FUNC_SAY, (L| Obj, Str), (L| Default_Say, Obj, Str));
		contPhys -> PushTodo(LispContinuation::just_evaluate, progSay);


		//SReference Func_Pause = PhysPackage->FindSymbol("FUNC_PAUSE");
		SReference Sec = PhysPackage->Intern("SEC");
		SReference Default_Pause = PhysPackage->FindSymbol("DEFAULT_PAUSE");
		SReference progPause = (L| DEFUN, FUNC_PAUSE, (L| Obj, Sec), (L| Default_Pause, Obj, Sec));
		contPhys -> PushTodo(LispContinuation::just_evaluate, progPause);


		SReference Default_Name = PhysPackage->FindSymbol("DEFAULT_NAME");
		SReference progName = (L| DEFUN, FUNC_NAME, (L| Obj), (L| Default_Name, Obj));
		contPhys -> PushTodo(LispContinuation::just_evaluate, progName);

		// SReference progName = (L| Defun, Func_Say, (Obj, Str), (Default_Say, Obj, Str));
		// contPhys -> PushTodo(LispContinuation::just_evaluate, progSay);

		// const char funcSay[] = "(DEFUN SAY (OBJ STR) (_SAY OBJ STR))";
		// ReadProgram(funcSay, physic);
		// const char funcPause[] = "(DEFUN PAUSE (OBJ SEC) (_PAUSE OBJ SEC))";
		// ReadProgram(funcPause, physic);
		// const char funcName[] = "(DEFUN NAME (OBJ SEC) (_NAME OBJ SEC))";
		// ReadProgram(funcName, physic);
		currState = Idle;
		printf("Physic activated\n");
	}
	catch(...) {
		printf("Error catched in ActivatePhysbject\n");
	}
}

void LivingObject::ActivateBehObject() 
{
	//SStreamCharbuf bufProgram(plrProgram);

	try {
		contBeh = new LispContinuation;
		behMark = contBeh -> GetMark();

		//LListConstructor L;
		SReference ref2 = new SExpressionLivingObject(this);
	 	contBeh -> PushTodo(LispContinuation::just_evaluate, (L| MAIN, ref2));


	 	ReadProgram(plrProgram, behavior);

	 	const char funcMain[] = "(DEFUN MAIN (OBJ) ())";
		ReadProgram(funcMain, physic);

		currState = Working;
		printf("Behavior activated\n");
	}
	catch(...) {
		printf("Error catched in ActivateObject\n");
	}
}

LExpressionPackage *LivingObject::PlayerPackage(LSymbol &main)
{
	LExpressionPackage *p = new LExpressionPackageIntelib;
	p->Import(DEFUN);
	LFunctionalSymbol<LFunctionSay>  SAY ("SAY");
	LFunctionalSymbol<LFunctionPause>  PAUSE ("PAUSE");
	LFunctionalSymbol<LFunctionName>  NAME ("NAME");
	p->Import(SAY);
	p->Import(NAME);
	p->Import(PAUSE);
	p->Import(COND);
	p->Import(EQ);
	p->Import(EQL);

	p->Import(main);
	return p;
}

LExpressionPackage *LivingObject::ModerPackage()
{
	LExpressionPackage *p = new LExpressionPackageIntelib;
	p->Import(DEFUN);
	p->Import(DEFAULT_SAY);
	p->Import(FUNC_SAY);
	p->Import(DEFAULT_NAME);
	p->Import(FUNC_NAME);
	p->Import(DEFAULT_PAUSE);
	p->Import(FUNC_PAUSE);
	p->Import(COND);
	p->Import(EQ);
	p->Import(EQL);

	return p;
}

void LivingObject::PrintObject() 
{
	printf("Name:%s\nBehavior:%s\bPhysic:%s\n", name, plrProgram, moderProgram);
}

const int stepsPerAction = 50;

void LivingObject::DoStep() 
{
//добавить работу второй континуации
	printf("DUBSTEP %d\n", *passSec);
	if (*passSec > 0)
		--*passSec;

	bool notEmpty = true;
	try {
		for (int steps = 0; steps < stepsPerAction && *passSec == 0; ++steps) {
			//printf("Cont %d\n", *avalCont);
			if ((*avalCont == behavior) && (!contBeh->Ready(behMark))) {
				//printf("behStep\n");
				contBeh->Step();
			}
			else { // availCont == physic
				if(!contPhys->Ready(PhysMark)) {
					//printf("physStep\n");
					bool notEmpty = contPhys->Step();
					//printf("%d\n", notEmpty);
					if (!notEmpty && currState == Working) {
						//printf("Change to beh\n");
						*avalCont = behavior;
					}
				}
				else if (currState == Working){
					//printf("Change to beh\n");
					*avalCont = behavior;
				}
			}
		}
	}
	catch(IntelibX &x) {
		printf("\n[DoStep %d]: Caught IntelibX: %s\n",*avalCont, x.Description() );
		if(x.Parameter().GetPtr()) {
			printf("%s\n", x.Parameter()->TextRepresentation().c_str());
 		}
		if(x.Stack().GetPtr()) {
            printf("%s\n", x.Stack()->TextRepresentation().c_str());
		}
	}
	catch(...) {
		printf("Error catched in DoStep\n");
	}
}

void LivingObject::SayToAll(const char *message) 
{
	currRoom->SayToAll(message, 0, name);
}



#endif 