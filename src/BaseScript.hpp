#pragma once
#include "IScript.hpp"
#include "AbstractComponent.hpp"
#include "WorkSpace.hpp"
namespace BEbraEngine {
	class BaseScript : public GameObjectComponent, public IScript {
	private:
		bool isEnable;
	protected:
		static inline std::shared_ptr<WorkSpace> workspace;
	public:
		static void SetWorkSpace(std::shared_ptr<WorkSpace> workspace) {
			BaseScript::workspace = workspace;
		}
		virtual ~BaseScript() {}

		virtual void SetActive(bool active) {
			isEnable = active;
		}
		virtual bool GetActive() {
			return isEnable;
		}
	};
}