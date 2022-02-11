#pragma once
class asILockableSharedBool;
#define DECLARATE_SCRIPT_OBJECT_DEFAULT_BEHAVIOR(ObjectType)	\
int refCount{};										\
void addRef() { ++refCount; }			\
int release() {						\
		if (--refCount == 0)						\
		{											\
			delete this;							\
			return 0;								\
		}											\
			return refCount;						\
}													\

namespace BEbraEngine { 
	class AbstractScriptObject {
	public:
		virtual asILockableSharedBool* getWeakRefFlag();
	protected:

		asILockableSharedBool* weakRefFlag;
	};
}