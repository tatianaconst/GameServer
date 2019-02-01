#include "sIntelib.hpp"
#include "sThing.hpp"

IntelibTypeId SExpressionLivingObject::TypeId(&SExpression::TypeId);

SExpressionLivingObject::SExpressionLivingObject()
	: SExpression(TypeId)
{
	obj = new LivingObject();
}

SExpressionLivingObject::SExpressionLivingObject(const LivingObject &object)
	: SExpression(TypeId)
{
	obj = new LivingObject(object);
}

SExpressionLivingObject::SExpressionLivingObject(LivingObject *object)
	: SExpression(TypeId)
{
	obj = object;
}

SExpressionLivingObject::~SExpressionLivingObject()
{
	//delete obj;
}

SString SExpressionLivingObject::TextRepresentation() const
{
	return SString("#<LIVING OBJECT>");
}

SReference SExpressionLivingObject::Clone(bool /*force*/) const
{
    return new SExpressionLivingObject(*obj);
}

// IntelibTypeId SExpressionRoomExit::TypeId(&SExpression::TypeId);

// SExpressionRoomExit::SExpressionRoomExit()
// 	: SExpressionLivingObject()
// {
// 	exit = new RoomExit();
// }

// SExpressionRoomExit::SExpressionRoomExit(const RoomExit &ex)
// 	: SExpressionLivingObject()
// {
// 	exit = new RoomExit(ex);
// }

// SExpressionRoomExit::~SExpressionRoomExit()
// {
// 	delete exit;
// }

// SString SExpressionRoomExit::TextRepresentation() const
// {
// 	return SString("#<ROOM EXIT>");
// }

// SReference SExpressionRoomExit::Clone(bool /*force*/) const
// {
//     return new SExpressionRoomExit(*exit);
// }
void LFunctionDefaultSay::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApply_SAY\n");
	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("not a living object");

	LivingObject *livObj = objExp -> Get();

	livObj -> SayToAll(paramsv[1].GetString());
	printf("_SAY: %s\n", paramsv[1].GetString());
	//printf("SAY: MEOW\n");
	lf.RegularReturn(*PTheEmptyList);
}

void LFunctionDefaultName::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApply_NAME\n");
	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("not a living object");

	LivingObject *livObj = objExp -> Get();

	char name[20];
	strcpy(name, livObj->GetName());
	printf("_NAME: %s\n", name);
	// livObj->DoPhysicFuncSay(paramsv[1].GetString());
	// livObj->ChangeContinuation(LivingObject::physic);
	//livObj->ReturnToBeh()
	lf.RegularReturn(*PTheEmptyList);
	LispContinuation *lsp = livObj->GetBehCont();
	// LReference ref;
	// lsp->PopResult(ref);
	//lsp->ReferenceReturn(name);
	lsp->RegularReturn(new SExpressionString(name));
	//livObj->ChangeAnswerContinuation();
}

void LFunctionDefaultPause::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApply_PAUSE\n");
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("not a living object");
	LivingObject *obj = objExp -> Get();
	obj -> LoseSec(paramsv[1].GetInt());
	lf.RegularReturn(*PTheEmptyList);
}

//////////////////////////////////////////////////////////////


void LFunctionSay::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApplySAY\n");
	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("not a living object");
	//LivingObject *livObj = objExp -> Get();
	//livObj -> Say(paramsv[1].GetString());
	printf("SAY: %s\n", paramsv[1].GetString());

	LivingObject *livObj = objExp -> Get();

	livObj->ChangeContinuation(physic);
	livObj->DoPhysicFuncSay(paramsv[1].GetString());
	lf.RegularReturn(*PTheEmptyList);
}

void LFunctionName::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApplyNAME\n");
	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("Not a living object");

	LivingObject *livObj = objExp -> Get();

	livObj->ChangeContinuation(physic);
	livObj->DoPhysicFuncName();

	//lf.RegularReturn(*PTheEmptyList);
	//lf.RegularReturn(name);
}

void LFunctionPause::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApplyPAUSE\n");
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("not a living object");
	LivingObject *livObj = objExp -> Get();


	livObj->ChangeContinuation(physic);
	livObj->DoPhysicFuncPause(paramsv[1].GetInt());
	lf.RegularReturn(*PTheEmptyList);
}



// void LFunctionWays::DoApply(int paramsc,
// 		const SReference paramsv[],
// 		IntelibContinuation &lf) const
// {
// 	//printf("DoApplySAY\n");
// 	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
// 	SExpressionGameObject *objExp =
// 		paramsv[0].DynamicCastGetPtr<SExpressionGameObject>();
// 	if(!objExp)
// 	    throw IntelibX("not a game object");
// 	BaseObject *base_obj = objExp -> Get();
// 	Object *obj  = dynamic_cast<Object*>(base_obj);
// 	if(!obj)
// 	    throw IntelibX("not an object");
// 	RoomExit *ways = obj -> Ways();
// 		SReference refWay = new SExpressionRoomExit(*ways);
// 		SReference t = *PTheEmptyList;
// 		t,refWay;
// 	lf.RegularReturn(t);//TODO Add Vectors to utils
// }



SString LFunctionDefaultSay::TextRepresentation() const
{
	return SString("#<FUNCTION DEFAULT_SAY>");
}

SString LFunctionSay::TextRepresentation() const
{
	return SString("#<FUNCTION SAY>");
}

SString LFunctionName::TextRepresentation() const
{
	return SString("#<FUNCTION NAME>");
}

SString LFunctionDefaultName::TextRepresentation() const
{
	return SString("#<FUNCTION DEFAULT_NAME>");
}

SString LFunctionPause::TextRepresentation() const
{
	return SString("#<FUNCTION PAUSE>");
}

SString LFunctionDefaultPause::TextRepresentation() const
{
	return SString("#<FUNCTION DEFAULT_PAUSE>");
}

// SString LFunctionWays::TextRepresentation() const
// {
// 	return SString("#<FUNCTION WAYS>");
// }
