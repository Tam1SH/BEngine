#include "stdafx.h"
#include "GameComponent.hpp"
namespace BEbraEngine {

	void GameComponent::addComponent(shared_ptr<GameComponent> component)
	{
		components_.push_back(component);
	}
	void GameComponent::removeComponent(shared_ptr<GameComponent> component)
	{
		components_.remove(component);
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
