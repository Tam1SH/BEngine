module;
#include <source_location>
//https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0478r0.pdf
//в следующей жизни.
#include <spdlog/spdlog.h>
#include <tbb.h>
#include <sstream>;
#include <string>;
export module Logger;

namespace BEbraEngine {

	namespace Logger {
		
		export void init() {
			spdlog::set_level(spdlog::level::debug);
			spdlog::set_pattern("[%H:%M:%S.%f] [%^%l%$] %v");
		}

		std::string format(const std::source_location& loc) {
			std::stringstream ss;
			ss << "[thread #" << tbb::this_task_arena::current_thread_index() << "] " << "[" << loc.file_name() << ", " << loc.line() << "] ";
			return ss.str();
		}
		
		export template <typename FormatString, typename... Args>
			struct error {
			error(FormatString&& t, Args&&... args, const std::source_location& loc = std::source_location::current()) {
				spdlog::error(fmt::runtime(format(loc) + t), std::forward<Args>(args)...);
			}
		};

		export template <typename FormatString, typename... Args>
		struct warn {
			warn(FormatString&& t, Args&&... args, const std::source_location& loc = std::source_location::current()) {
				spdlog::warn(fmt::runtime(format(loc) + t), std::forward<Args>(args)...);
			}
		};

		export template <typename FormatString, typename... Args>
		struct info {
			info(FormatString&& t, Args&&... args, const std::source_location& loc = std::source_location::current()) {
				spdlog::info(fmt::runtime(format(loc) + t), std::forward<Args>(args)...);
			}
		};

		export template <typename FormatString, typename... Args>
			struct debug {
			debug(FormatString&& t, Args&&... args, const std::source_location& loc = std::source_location::current()) {
				spdlog::debug(fmt::runtime(format(loc) + t), std::forward<Args>(args)...);
			}
		};

		template <typename FormatString, typename... Args>
		info(FormatString&&, Args&&...)->info<FormatString, Args...>;

		template <typename FormatString, typename... Args>
		error(FormatString&&, Args&&...)->error<FormatString, Args...>;

		template <typename FormatString, typename... Args>
		debug(FormatString&&, Args&&...)->debug<FormatString, Args...>;

		template <typename FormatString, typename... Args>
		warn(FormatString&&, Args&&...)->warn<FormatString, Args...>;
		
		
	}
}