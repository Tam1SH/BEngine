#include "stdafx.h"
#include "Debug.hpp"
namespace BEbraEngine {
	std::vector<Debug::ObjectType> Debug::_disableLog;
	std::mutex Debug::m;
}