
#include "platform.hpp"
export module BitMap;

namespace BEbraEngine {


	export struct BitMap {

		struct Rows {
			struct pixel {
				char x, y, z;
			};
			unsigned int* rows;
			pixel operator[](size_t index) const {
				auto pixel_ = rows + index;
				auto comp_ = pixel{
					*((char*)pixel_ + 2),
					*((char*)pixel_ + 1),
					*((char*)pixel_)
				};
				return comp_;
			}
		};
		Rows& operator[](int index)
		{
			return at(index);
		}

		virtual Rows& at(int index) = 0;
		virtual ~BitMap() {}
	};

}