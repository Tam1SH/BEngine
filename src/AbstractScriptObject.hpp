#pragma once
class asILockableSharedBool;

namespace BEbraEngine {
	class AbstractScriptObject {
	public:
		virtual void addRef() { ++refCount; }
		virtual int release() {
			if (--refCount == 0)
			{
				delete this;
				return 0;
			}
			return refCount;
		}
		virtual asILockableSharedBool* getWeakRefFlag();
	protected:
		int refCount;
		asILockableSharedBool* weakRefFlag;
	};
}