module;
#include "platform.hpp"
#include <exception>
#include <typeinfo>
#include <memory>
#include <string>
#include <optional>

export module GameObject;
import GameComponent;


using std::shared_ptr;
using std::string;
using std::optional;


namespace BEbraEngine {

    export class GameObject : public GameComponent { 
    public:

        template<typename Destroyer>
        void destroy(Destroyer& destroyer) {
            destroyer.destroyGameObject(*this);
        }

        template<typename RequiredType>
            requires std::is_base_of_v<GameComponent, RequiredType>
        shared_ptr<RequiredType> getComponentCheckedPtr() const noexcept(false) {

            for (auto& component : components_) {
                if (auto p = std::dynamic_pointer_cast<RequiredType>(component); p) {
                    return p;
                }
            }
            throw std::bad_cast();
        }

        template<typename RequiredType>
            requires std::is_base_of_v<GameComponent, RequiredType>
        RequiredType& getComponentChecked() const noexcept(false) {

            for (auto& component : components_) {
                if (auto p = dynamic_cast<RequiredType*>(component.get()); p) {
                    return *p;
                }
            }
            throw std::bad_cast();
        }

        template<typename RequiredType>
            requires std::is_base_of_v<GameComponent, RequiredType>
        optional<RequiredType*> getComponent() const noexcept {

            for (auto& component : components_) {
                if (auto p = dynamic_cast<RequiredType*>(component.get()); p) {
                    return std::make_optional(p);
                }
            }
            return std::nullopt;
        }

        GameComponent* getComponentByName(const string& name) const noexcept;


        bool isComposite() const noexcept override;

        GameObject() noexcept;

        GameObject(const string& name) noexcept
        {
            this->name_ = name;
        }

        ~GameObject() noexcept
        {
        }


    };




}