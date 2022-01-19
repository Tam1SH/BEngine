#pragma once
#include "IScript.hpp"
#include "GameComponent.hpp"
namespace BEbraEngine {
	class BaseScript : public GameComponent, public IScript {
	private:
		bool isEnable;
	public:
		virtual ~BaseScript() {}

		virtual void SetActive(bool active) {
			isEnable = active;
		}
		virtual bool getActive() {
			return isEnable;
		}
	};
}