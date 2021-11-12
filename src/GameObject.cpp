#include "stdafx.h"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
namespace BEbraEngine {

    bool GameObject::IsComposite() const
    {
        return true;
    }

    GameObject::GameObject()
    {
        name = "GameObject";
    }
    GameObject::~GameObject()
    {
    }
}