#pragma once
#include "GameComponent.hpp"
namespace BEbraEngine {
	class BaseScript : public GameComponent {
	public:
		virtual ~BaseScript() {}

		virtual void SetActive(bool active) {
			isEnable = active;
		}
		virtual bool getActive() {
			return isEnable;
		}
	private:
		bool isEnable;
	};
}