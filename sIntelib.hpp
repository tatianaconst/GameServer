#ifndef SINTELIB_HPP
#define SINTELIB_HPP


#include <intelib/lisp/lreader.hpp>
#include <intelib/lisp/lpackage.hpp>
#include <intelib/lisp/lcont.hpp>
#include <intelib/lfun_std.hpp>
#include <intelib/tools/sstream.hpp>



class LivingObject;


class SExpressionLivingObject : public SExpression {
	class LivingObject *obj;
public:
	static IntelibTypeId TypeId;

	SExpressionLivingObject();
	SExpressionLivingObject(LivingObject *obj);
	~SExpressionLivingObject();
	SExpressionLivingObject(const LivingObject &obj);

	virtual SString TextRepresentation() const;
	virtual SReference Clone(bool force) const;

	class LivingObject *Get() const {return obj;}
};


class LFunction_Say : public SExpressionFunction {
public:
	LFunction_Say() : SExpressionFunction(2, 2) {}
	virtual void DoApply(int paramsc,
	                     const SReference paramsv[],
	                     IntelibContinuation &lf) const;
	virtual SString TextRepresentation() const;
};

class LFunctionSay : public SExpressionFunction {
public:
	LFunctionSay() : SExpressionFunction(2, 2) {}
	virtual void DoApply(int paramsc,
	                     const SReference paramsv[],
	                     IntelibContinuation &lf) const;
	virtual SString TextRepresentation() const;
};

class LFunctionName : public SExpressionFunction {
public:
	LFunctionName() : SExpressionFunction(1, 1) {}
	virtual void DoApply(int paramsc,
	                     const SReference paramsv[],
	                     IntelibContinuation &lf) const;
	virtual SString TextRepresentation() const;
};

class LFunction_Name : public SExpressionFunction {
public:
	LFunction_Name() : SExpressionFunction(1, 1) {}
	virtual void DoApply(int paramsc,
	                     const SReference paramsv[],
	                     IntelibContinuation &lf) const;
	virtual SString TextRepresentation() const;
};


// class LFunctionWays : public SExpressionFunction {
// public:
// 	LFunctionWays() : SExpressionFunction(1, 1) {}
// 	virtual void DoApply(int paramsc,
// 	                     const SReference paramsv[],
// 	                     IntelibContinuation &lf) const;
// 	virtual SString TextRepresentation() const;
// };

class LFunctionPause : public SExpressionFunction {
public:
	LFunctionPause() : SExpressionFunction(2, 2) {}
	virtual void DoApply(int paramsc,
	                     const SReference paramsv[],
	                     IntelibContinuation &lf) const;
	virtual SString TextRepresentation() const;
};

class LFunction_Pause : public SExpressionFunction {
public:
	LFunction_Pause() : SExpressionFunction(2, 2) {}
	virtual void DoApply(int paramsc,
	                     const SReference paramsv[],
	                     IntelibContinuation &lf) const;
	virtual SString TextRepresentation() const;
};

// class SExpressionRoomExit : public SExpressionGameObject {
// 	struct RoomExit *exit;
// public:
// 	static IntelibTypeId TypeId;

// 	SExpressionRoomExit();
// 	~SExpressionRoomExit();

// 	virtual SString TextRepresentation() const;
// 	virtual SReference Clone(bool force) const;

// struct RoomExit *Get() const {return exit;}
// //private:
// 	SExpressionRoomExit(const RoomExit &exit);
// };



#endif
