#include "stdafx.h"
#include "AbstractScriptObject.hpp"
#include <angelscript.h>
asILockableSharedBool* BEbraEngine::AbstractScriptObject::getWeakRefFlag()
{
	if (!weakRefFlag)
		weakRefFlag = asCreateLockableSharedBool();

	return weakRefFlag;
}
