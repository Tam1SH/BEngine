#include "stdafx.h"
#include "utils.hpp"
namespace BEbraEngine {
    namespace utils {
        size_t getCurrentThreadIndex()
        {

            int index = tbb::this_task_arena::current_thread_index();
            if (index >= tbb::this_task_arena::max_concurrency() || index < 0)
                index = 0;

            return index;
        }
    }

}