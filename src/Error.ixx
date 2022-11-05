#include <iostream>
export module Error;
import <string>;

export namespace BEbraEngine {

	enum struct CreateStateErrorCode {

	};
}
export namespace BEbraEngine {

	struct Error {

		void what(std::ostream& stream = std::cout) const noexcept {
			stream << message << std::endl;
		}

		constexpr Error(const char* message) noexcept {
			this->message = message;
		}

		constexpr Error(std::string_view& message) noexcept {
			this->message = message.data();
		}

		const char* message;
	};


	struct CreateStateError : Error {

		constexpr CreateStateError(CreateStateErrorCode code, std::string_view& message) : Error(message), code(code) { }
		constexpr CreateStateError(CreateStateErrorCode code, const char* message) : Error(message), code(code) { }
		CreateStateErrorCode code;
	};
}