#pragma once
namespace BEbraEngine {
	class GameObjectMediator;
}
namespace BEbraEngine {

	class GameObjectMediatorComponent {
	protected:
		GameObjectMediator* _mediator;
	public:


		GameObjectMediatorComponent() {}
		virtual ~GameObjectMediatorComponent() {}
	};
}