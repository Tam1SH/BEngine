module;
#include "stdafx.h"
export module OnlyMovable;


namespace BEbraEngine {
	export template<class T>
		concept OnlyMovable = (std::movable<T> && !std::copyable<T>);
	
}