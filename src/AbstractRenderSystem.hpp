#pragma once
#include "BaseRenderWindow.h"
namespace BEbraEngine {
	class AbstractRender {
	public:
		virtual void Create(BaseWindow* window) = 0;
	};
}