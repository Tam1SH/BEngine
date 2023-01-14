export module PoolObject;
import <type_traits>;
import <functional>;
import Logger;
namespace BEbraEngine {
    struct Za4em_9_Takim_Zanimaus777 {};

    //Указание того, что ресурсы объекта будут освобождены после разрушения.
	export template<typename T, typename Deleter = Za4em_9_Takim_Zanimaus777,
                                typename = std::enable_if<std::is_function_v<Deleter>>>
    //Хотелось сделать unique_ptr, но не хочется менять контракт заводов.
    struct PoolObject {

        static constexpr void setDeleter(auto&& deleter) {
            gDeleter = deleter;
        }

        virtual ~PoolObject() {

            if constexpr (!std::is_same_v<Deleter, Za4em_9_Takim_Zanimaus777>) {
                if (deleter) {
                    deleter(static_cast<T&>(*this));
                    return;
                }
            }

            if (gDeleter)
                gDeleter(static_cast<T&>(*this));
            else {
                Logger::debug("Object was not destroyed, {}", this);
            }
        }
        private:
            [[no_unique_address]] Deleter deleter;
            static inline std::function<void(T&)> gDeleter;

    };
}