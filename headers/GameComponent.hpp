#pragma once
#include "platform.hpp"

using BE_STD::shared_ptr;
using BE_STD::string;
using BE_STD::list;

BE_NAMESPACE_STD_BEGIN
    template <class T>
    class shared_ptr;
    template<class T, class Alloc>
    class list;

BE_NAMESPACE_STD_END

namespace BEbraEngine {
    class IVisitorGameComponentDestroyer;
}

namespace BEbraEngine {

    class GameComponent {
    public:

        virtual void destroy(IVisitorGameComponentDestroyer& destroyer) = 0;

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
}