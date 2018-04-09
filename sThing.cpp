#ifndef STHING_CPP
#define STHING_CPP

#include "sThing.hpp"

typedef struct RefNode {
			LReference ref;
			struct RefNode *next;
} RefNode;

LSymbol LivingObject::MAIN("MAIN");

LFunctionalSymbol<LFunctionCompiledDefun>  DEFUN("DEFUN");
//LFunctionalSymbol<LFunctionSay>  SAY ("SAY");
LFunctionalSymbol<LFunctionSay1>  SAY1 ("SAY1");
// LFunctionalSymbol<LFunctionPause>  PAUSE ("PAUSE");
// LFunctionalSymbol<LFunctionWays> WAYS ("WAYS");

// void LivingObject::DoPhysicFunc(LReference ref)
// {
// 	PhysMark = contPhys->GetMark();
// 	//contPhys->Evaluate(ref);
// 	LListConstructor L;
// 	contPhys->PushTodo(LispContinuation::just_evaluate, ref);
// 	contPhys->PushTodo(LispContinuation::just_evaluate, (L| SAY, 9, 0));
// 	LSymbol OBJ("OBJ");
// 		LSymbol STR("STR");
// 		LReference refSayMeow = 
// 		(L| DEFUN, SAY, (L| OBJ, STR),
// 				(L| SAY1, OBJ, "MEOW")
// 			);
// }

void LivingObject::DoPhysicFuncSay(const char *message)
{

	printf("DOFUNCSAY\n");
	PhysMark = contPhys->GetMark();
	//contPhys->Evaluate(ref);
	LListConstructor L;
	//contPhys->PushTodo(LispContinuation::just_evaluate, ref);
	SReference ref2 = new SExpressionLivingObject(*this);
	//LSymbol MYSAY("MYSAY");
	//LSymbol HUY("HUY");
	//contPhys->PushTodo(LispContinuation::just_evaluate, (L| HUY, ref2, message));

///////////////////////////////////////////
	IntelibReader reader;
	LSymbol REFOBJ("REFOBJ");
	REFOBJ -> SetDynamicValue(ref2);
	(static_cast<LExpressionPackage*>(PhysPackage.GetPtr()))->Import(REFOBJ);
	reader.SetPackage(static_cast<LExpressionPackage*>(PhysPackage.GetPtr()));
	//contPhys = new LispContinuation;

	RefNode *refList = NULL, *refP;
	LReference ref;
	const char* fun = "(DEFUN MYSAY (OBJ STR) (SAY1 OBJ 10)) (MYSAY REFOBJ 4)";
	SStreamCharbuf bufProgram(/*moderProgram*/fun);

	ref = reader.Read(bufProgram);
	while (ref != IntelibReader::EofMarker) {
		printf("AZAZAZAZAAZ\n");
		refP = new RefNode;
		refP -> ref = ref;
		refP -> next = refList;
		refList = refP;
		ref = reader.Read(bufProgram);
	}
	//PhysMark = contPhys->GetMark();

	//LListConstructor L;
	//SReference ref2 = new SExpressionLivingObject(*this);
 	//contPhys -> PushTodo(LispContinuation::just_evaluate, (L| MAIN, ref2));
	while (refList != NULL) {
		printf("TTTTTTTT\n");
		contPhys->PushTodo(LispContinuation::just_evaluate, refList->ref);
		refP = refList->next;
		delete(refList);
		refList = refP;
	}


/////////////////////////////////////////////////////////////////







	LSymbol OBJ("OBJ");
	LSymbol STR("STR");
		// LReference refSayMeow = 
		// (L| DEFUN, MYSAY, (L| OBJ, STR),
		// 		(L| SAY1, OBJ, "MEOW")
		// 	);
		// LReference refSay =
		// 		(L| DEFUN, MYSAY, (L| OBJ, STR),
		// 			(L| SAY1, OBJ, STR)
		// 		);


		//contPhys->PushTodo(LispContinuation::just_evaluate, refSayMeow);
		//contPhys->PushTodo(LispContinuation::just_evaluate, refSay);
}

void LivingObject::ActivatePhysObject() 
{
	//SStreamCharbuf bufProgram(moderProgram);

	try {
		IntelibReader reader;
		reader.SetPackage(static_cast<LExpressionPackage*>(PhysPackage.GetPtr()));
		contPhys = new LispContinuation;

		RefNode *refList = NULL, *refP;
		LReference ref;
		// ref = reader.Read(bufProgram);
		// while (ref != IntelibReader::EofMarker) {
		// 	refP = new RefNode;
		// 	refP -> ref = ref;
		// 	refP -> next = refList;
		// 	refList = refP;
		// 	ref = reader.Read(bufProgram);
		// }
		PhysMark = contPhys->GetMark();

		LListConstructor L;
		//SReference ref2 = new SExpressionLivingObject(*this);
	 	//contPhys -> PushTodo(LispContinuation::just_evaluate, (L| MAIN, ref2));
		while (refList != NULL) {
			printf("NotNULL\n");
			//contPhys->PushTodo(LispContinuation::just_evaluate, refList->ref);
			refP = refList->next;
			delete(refList);
			refList = refP;
		}

		LSymbol OBJ("OBJ");
		LSymbol STR("STR");
		// contPhys->PushTodo(LispContinuation::just_evaluate, refsay);
		//contPhys->PushTodo(LispContinuation::just_evaluate, refSayMeow);
		//contPhys->PushTodo(LispContinuation::just_evaluate, refSay);
		printf("Physic activated\n");
	}
	catch(...) {
		printf("Error catched in ActivatePhysbject\n");
	}
}

void LivingObject::ActivateBehObject() 
{
	SStreamCharbuf bufProgram(plrProgram);

	try {
		IntelibReader reader;
		reader.SetPackage(static_cast<LExpressionPackage*>(BehPackage.GetPtr()));
		contBeh = new LispContinuation;

		typedef struct RefNode {
			LReference ref;
			struct RefNode *next;
		} RefNode;

		RefNode *refList = NULL, *refP;
		LReference ref;
		ref = reader.Read(bufProgram);
		while (ref != IntelibReader::EofMarker) {
			refP = new RefNode;
			refP -> ref = ref;
			refP -> next = refList;
			refList = refP;
			ref = reader.Read(bufProgram);
		}
		behMark = contBeh -> GetMark();

		LListConstructor L;
		SReference ref2 = new SExpressionLivingObject(*this);
	 	contBeh -> PushTodo(LispContinuation::just_evaluate, (L| MAIN, ref2));

		while (refList != NULL) {
			contBeh -> PushTodo(LispContinuation::just_evaluate, refList -> ref);
			refP = refList -> next;
			delete(refList);
			refList = refP;
		}
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
	p->Import(SAY);
	// p->Import(PAUSE);
	p->Import(main);
	// p->Import(WAYS);

	// SReference ref = new SExpressionGameObject(*this);
	// OBJ -> SetDynamicValue(ref);
	// p->Import(OBJ);
	return p;
}

LExpressionPackage *LivingObject::ModerPackage()
{
	LExpressionPackage *p = new LExpressionPackageIntelib;
	p->Import(DEFUN);
	p->Import(SAY1);
	// p->Import(PAUSE);
	//p->Import(MAIN);
	// p->Import(WAYS);

	// SReference ref = new SExpressionGameObject(*this);
	// OBJ -> SetDynamicValue(ref);
	// p->Import(OBJ);
	return p;
}

void LivingObject::PrintObject() {
	printf("Name:%s\nBehavior:%s\bPhysic:%s\n", name, plrProgram, moderProgram);
}

const int stepsPerAction = 50;

void LivingObject::DoStep() {
//добавить работу второй континуации
	printf("DUBSTEP\n");
	if (passSec > 0)
		--passSec;

	bool notEmpty = true;
	try {
		for (int steps = 0; steps < stepsPerAction && passSec == 0; ++steps) {
			//printf("STEPAN\n");
			if ((avalCont == behavior) && (!contBeh->Ready(behMark))) {
				//printf("behStep\n");
				contBeh->Step();
			}
			else { // availCont == physic
				// if(!contPhys->Ready(PhysMark)) {
						//printf("contPhysStep\n");
					bool notEmpty = contPhys->Step();
					//printf("%d\n", notEmpty);
					if (!notEmpty) {
						avalCont = behavior;
					}
				// }
				// else {
				// 	avalCont = behavior;
				// }
			}
		}
	}
	catch(IntelibX &x) {
		printf("\nCaught IntelibX: %s\n", x.Description() );
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

// void LivingObject::Say() {

// }



#endif 