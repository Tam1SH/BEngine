
export module GameComponent;
import OnlyMovable;
//import Logger;
import <memory>;
import <list>;
import <string>;
import <concepts>;
import <optional>;

using std::optional;
using std::shared_ptr;
using std::string;
using std::list;



namespace BEbraEngine {

	export struct GameComponent {

		template<typename ComponentType, typename Destroyer>
			requires std::is_base_of_v<GameComponent, ComponentType>
		void destroy(Destroyer& destroyer) noexcept {
			static_cast<ComponentType&>(*this).destroy(destroyer);
		}

		template<typename RequiredType>
			requires std::is_base_of_v<GameComponent, RequiredType>
		RequiredType& as() noexcept {

			if (auto p = dynamic_cast<RequiredType*>(this); p)
				return *p;

			//«ащита от дурака(себ€)
			//Logger::error("Failed to cast the object to this type.");
			throw std::bad_cast();
		}

		virtual void addComponent(shared_ptr<GameComponent> component) noexcept;

		virtual optional<shared_ptr<GameComponent>> removeComponent(shared_ptr<GameComponent> component) noexcept;

		virtual bool isComposite() const noexcept;

		std::string& getName() noexcept;

		int getSize() noexcept;

		GameComponent& getParent() noexcept;

		void setParent(GameComponent& parent) noexcept;

		void setName(string name) noexcept;

		GameComponent(string name) noexcept;

		constexpr GameComponent() noexcept = default;

		virtual ~GameComponent() noexcept;

		GameComponent(GameComponent&& o) noexcept = default;
		GameComponent& operator=(GameComponent&& o) noexcept = default;

		GameComponent(const GameComponent& o) = delete;
		GameComponent& operator=(const GameComponent& o) = delete;

	protected:
		//должен быть вызван в конструкторе производного класса.
		void itWasDestroyed() { __isDestroyed = true; }

		string name_{};

		list<shared_ptr<GameComponent>> components_{};

	private:

		GameComponent* parent_{};
		bool __isDestroyed;

	};
	
	void GameComponent::setName(string name) noexcept
	{
		this->name_ = name;
	}
	GameComponent::GameComponent(string name) noexcept
	{
		name_ = name;
	}

	void GameComponent::addComponent(shared_ptr<GameComponent> component) noexcept
	{
		//Logger::debug("another object({}) has been added to the object({})", component->name_, name_);
		components_.push_back(component);
	}

	optional<shared_ptr<GameComponent>> GameComponent::removeComponent(shared_ptr<GameComponent> component) noexcept
	{
		if (components_.remove(component)) {
			return component;
		}

		//Logger::warn("The object({}) did not have this object({}) inside it", name_, component->name_);
		return std::nullopt;
	}

	std::string& GameComponent::getName() noexcept
	{
		return name_;
	}

	int GameComponent::getSize() noexcept
	{
		return components_.size();
	}

	GameComponent& GameComponent::getParent() noexcept
	{
		return *parent_;
	}

	void GameComponent::setParent(GameComponent& parent) noexcept
	{
		//Logger::debug("The object({}) now has a new parent({}) instead of this({})", name_, parent.name_, parent_->name_);
		this->parent_ = &parent;
	}

	bool GameComponent::isComposite() const noexcept
	{
		return components_.size() != 0;
	}


	GameComponent::~GameComponent() noexcept
	{
		//if (!__isDestroyed)
			//Logger::warn("object({}) was not destroyed or itWasDestroyed was not called.", name_);
	}
	
}


