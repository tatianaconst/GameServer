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

SExpressionLivingObject::~SExpressionLivingObject()
{
	delete obj;
}

SString SExpressionLivingObject::TextRepresentation() const
{
	return SString("#<LIVING OBJECT>");
}

SReference SExpressionLivingObject::Clone(bool /*force*/) const
{
    return new SExpressionLivingObject(*obj);
}

// IntelibTypeId SExpressionGameObject::TypeId(&SExpression::TypeId);

// SExpressionGameObject::SExpressionGameObject()
// 	: SExpression(TypeId)
// {
// 	obj = new Object();
// }

// SExpressionGameObject::SExpressionGameObject(const Object &object)
// 	: SExpression(TypeId)
// {
// 	obj = new Object(object);
// }

// SExpressionGameObject::~SExpressionGameObject()
// {
// 	delete obj;
// }

// SString SExpressionGameObject::TextRepresentation() const
// {
// 	return SString("#<GAME OBJECT>");
// }

// SReference SExpressionGameObject::Clone(bool /*force*/) const
// {
//     return new SExpressionGameObject(*obj);
// }

// IntelibTypeId SExpressionRoomExit::TypeId(&SExpression::TypeId);

// SExpressionRoomExit::SExpressionRoomExit()
// 	: SExpressionGameObject()
// {
// 	exit = new RoomExit();
// }

// SExpressionRoomExit::SExpressionRoomExit(const RoomExit &ex)
// 	: SExpressionGameObject()
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
void LFunctionSay1::DoApply(int paramsc,
		const SReference paramsv[],
		IntelibContinuation &lf) const
{
	printf("DoApplySAY1\n");
	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
	SExpressionLivingObject *objExp =
		paramsv[0].DynamicCastGetPtr<SExpressionLivingObject>();
	if(!objExp)
	    throw IntelibX("not a living object");
	//LivingObject *livObj = objExp -> Get();
	//livObj -> Say(paramsv[1].GetString());
	printf("SAY1: %s\n", paramsv[1].GetString());
	//printf("SAY: MEOW\n");
	lf.RegularReturn(*PTheEmptyList);
}


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
	LListConstructor L;
	LSymbol  SAY("SAY");
	LSymbol  SAY1("SAY1");
	LReference ref = (L| SAY, objExp, "Something");
	//LReference ref = (L| NIL);
	// livObj->DoPhysicFunc(ref);
	livObj->DoPhysicFuncSay(paramsv[1].GetString());
	livObj->ChangeContinuation(LivingObject::physic);
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

// SString LFunctionPause::TextRepresentation() const
// {
// 	return SString("#<FUNCTION PAUSE>");
// }

// void LFunctionPause::DoApply(int paramsc,
// 		const SReference paramsv[],
// 		IntelibContinuation &lf) const
// {
// 	//printf("DoApplyPAUSE\n");
// 	//lf.RegularReturn(new SExpressionPermGen(paramsv[0].GetInt()));
// 	SExpressionGameObject *objExp =
// 		paramsv[0].DynamicCastGetPtr<SExpressionGameObject>();
// 	if(!objExp)
// 	    throw IntelibX("not a game object");
// 	Object *obj = objExp -> Get();
// 	obj -> LoseSec(paramsv[1].GetInt());
// 	//printf("%d\n", paramsv[1].GetInt());
// 	lf.RegularReturn(*PTheEmptyList);
// }

SString LFunctionSay1::TextRepresentation() const
{
	return SString("#<FUNCTION SAY1>");
}

SString LFunctionSay::TextRepresentation() const
{
	return SString("#<FUNCTION SAY>");
}

// SString LFunctionWays::TextRepresentation() const
// {
// 	return SString("#<FUNCTION WAYS>");
// }