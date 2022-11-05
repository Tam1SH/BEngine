module;
#include <tbb.h>
export module utils;
import Collider;
//import FormattableToString;

namespace BEbraEngine {

    export namespace utils {

        //export std::string toString(FormattableToString auto& object) {
        //    return object.toString();
        //}

        size_t getCurrentThreadIndex()
        {

            int index = tbb::this_task_arena::current_thread_index();
            if (index >= tbb::this_task_arena::max_concurrency() || index < 0)
                index = 0;

            return index;
        }

        
        std::string toString(ColliderType type) {
            switch (type)
            {
            case BEbraEngine::ColliderType::Mesh:
                return "ColliderType::Mesh";
            case BEbraEngine::ColliderType::Cone:
                return "ColliderType::Cone";
            case BEbraEngine::ColliderType::Cylinder:
                return "ColliderType::Cylinder";
            case BEbraEngine::ColliderType::Capsule:
                return "ColliderType::Capsule";
            case BEbraEngine::ColliderType::Sphere:
                return "ColliderType::Sphere";
            case BEbraEngine::ColliderType::Box:
                return "ColliderType::Box";
            default:
                return "None";
            }
        }
        

    }
}