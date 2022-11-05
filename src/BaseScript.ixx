
export module BaseScript;

import GameComponent;
namespace BEbraEngine {
	export class BaseScript : public GameComponent {
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