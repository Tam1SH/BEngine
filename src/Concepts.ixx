export module Concepts;
import <concepts>;

namespace BEbraEngine {
	template<class T>
	concept OnlyMovable = (std::movable<T> && !std::copyable<T>);
	
}