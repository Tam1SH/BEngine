
#include "platform.hpp"


export module GameObject;
import <typeinfo>;
import <memory>;
import <string>;
import <optional>;
import Debug;
import GameComponent;
//import ÑVisitorComponentDestroyer;

using BE_STD::shared_ptr;
using BE_STD::string;
using BE_STD::optional;
namespace BEbraEngine {

    export class GameObject : public GameComponent { 
        //DEBUG_DESTROY_CHECK_DECL()
    public:

        //void destroy(IVisitorGameComponentDestroyer& destroyer) { } //override;

        //void destroy(ÑVisitorComponentDestroyer auto& destroyer) {
        //    for (auto& comp : components_) {
        //        comp->destroy(destroyer);
        //    }
        //    
        //    destroyer.destroyGameObject(*this);
        //}
        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        shared_ptr<T> getComponentCheckedPtr() const noexcept {
            for (auto& component : components_) {
                if (std::dynamic_pointer_cast<T>(component)) {
                    return std::static_pointer_cast<T>(component);
                }
            }
            throw std::exception();
        }

        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        T& getComponentChecked() const {
            for (auto& component : components_) {
                if (dynamic_cast<T*>(component.get())) {
                    return *static_cast<T*>(component.get());
                }
            }
            throw std::exception();
        }

        template<typename T, class _ = typename BE_STD::enable_if<BE_STD::is_base_of<GameComponent, T>::value>::type>
        optional<T*> getComponent() const noexcept {
            for (auto& component : components_) {
                if (dynamic_cast<T*>(component.get())) {
                    return optional<T*>(static_cast<T*>(component.get()));
                }
            }
            return optional<T*>();
        }
        GameComponent* getComponentByName(const string& name) const noexcept
        {
            for (auto& component : components_) {

                //TODO: íåñòðîãîå ñðàâíåíèå íàçâàíèé êëàññîâ, â áóäóùåì ìîãó íà ýòîì ïîñîñàòü.
                const std::string componentName = typeid(*component).name();

                if (componentName.find(name) != string::npos) {
                    return component.get();
                }
            }
            return nullptr;
        }


        bool isComposite() const noexcept override
        {
            return true;
        }

        GameObject() noexcept
        {
            name_ = "GameObject";
        }

        GameObject(const string& name) noexcept
        {
            this->name_ = name;
        }

        ~GameObject() noexcept
        {
            //DEBUG_DESTROY_CHECK("GameObject has not destroyed", this, name_, Debug::ObjectType::GameObject, Debug::MessageType::Info);
        }


    };

    
}

