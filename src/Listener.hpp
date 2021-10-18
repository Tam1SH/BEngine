#pragma once
namespace BEbraEngine {
	struct IListenerOnRender {
		virtual void onUpdateFrame() = 0;
		virtual ~IListenerOnRender() {}
	};
	struct IListenerOnTick {
		virtual void onUpdateTick() = 0;
		virtual ~IListenerOnTick() {}

	};
	class INotifierFrame {
		virtual void attach(IListenerOnRender* listener) = 0;
		virtual void detach(IListenerOnRender* listener) = 0;
		virtual void notifyOnUpdateFrame() = 0;
	};
	class INotifierTick {
		virtual void attach(IListenerOnTick* listener) = 0;
		virtual void detach(IListenerOnTick* listener) = 0;
		virtual void notifyOnUpdateTick() = 0;
	};
}