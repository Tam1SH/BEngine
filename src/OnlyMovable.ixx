export module OnlyMovable;
import <concepts>;

namespace BEbraEngine {
	export template<class T>
		concept OnlyMovable = (std::movable<T> && !std::copyable<T>);
	
}