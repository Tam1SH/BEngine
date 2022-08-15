#include "platform.hpp"

export module GameComponent;
import <memory>;
import <list>;
import <string>;
using std::shared_ptr;
using std::string;
using std::list;

namespace BEbraEngine {
	class VisitorGameComponentDestroyer;
}
namespace BEbraEngine {

	export class GameComponent {
	public:

		//virtual void destroy(VisitorGameComponentDestroyer& destroyer) = 0;

		template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
		T& as() {
			T* p = dynamic_cast<T*>(this);
			if (p)
				return *p;
			throw std::exception();
		}

		virtual void addComponent(shared_ptr<GameComponent> component);

		virtual shared_ptr<GameComponent> removeComponent(shared_ptr<GameComponent> component);

		void setParent(GameComponent& parent) noexcept;

		GameComponent& getParent() const noexcept;

		virtual bool isComposite() const noexcept;

		string& getName() noexcept;

		void setName(const string& name);

		size_t getSize() const noexcept;

		virtual ~GameComponent() noexcept {}

		GameComponent() noexcept {}

	protected:
		string name_{};

		list<shared_ptr<GameComponent>> components_{};

	private:

		GameComponent* parent_{};


	};

	void GameComponent::addComponent(shared_ptr<GameComponent> component)
	{
		components_.push_back(component);
	}
	shared_ptr<GameComponent> GameComponent::removeComponent(shared_ptr<GameComponent> component)
	{
		components_.remove(component);
		return component;
	}
	void GameComponent::setParent(GameComponent& parent) noexcept
	{
		this->parent_ = &parent;
	}
	GameComponent& GameComponent::getParent() const noexcept
	{
		return *this->parent_;
	}
	bool GameComponent::isComposite() const noexcept
	{
		return components_.size() != 0;
	}
	string& GameComponent::getName() noexcept
	{
		return name_;
	}
	void GameComponent::setName(const string& name)
	{
		this->name_ = name;
	}
	size_t GameComponent::getSize() const noexcept
	{
		return components_.size();
	}
}