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
void LFunction_Say::DoApply(int paramsc,
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

void LFunction_Name::DoApply(int paramsc,
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

	// livObj->DoPhysicFuncSay(paramsv[1].GetString());
	// livObj->ChangeContinuation(LivingObject::physic);
	//livObj->ReturnToBeh()
	lf.RegularReturn(name);
	livObj->ChangeAnswerContinuation();
}

void LFunction_Pause::DoApply(int paramsc,
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
	lf.RegularReturn(*PTheEmptyList);
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



SString LFunction_Say::TextRepresentation() const
{
	return SString("#<FUNCTION _SAY>");
}

SString LFunctionSay::TextRepresentation() const
{
	return SString("#<FUNCTION SAY>");
}

SString LFunctionName::TextRepresentation() const
{
	return SString("#<FUNCTION NAME>");
}

SString LFunction_Name::TextRepresentation() const
{
	return SString("#<FUNCTION _NAME>");
}

SString LFunctionPause::TextRepresentation() const
{
	return SString("#<FUNCTION PAUSE>");
}

SString LFunction_Pause::TextRepresentation() const
{
	return SString("#<FUNCTION _PAUSE>");
}

// SString LFunctionWays::TextRepresentation() const
// {
// 	return SString("#<FUNCTION WAYS>");
// }
