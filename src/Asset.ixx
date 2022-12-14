export module Asset;
import <string>;
import <optional>;

namespace BEbraEngine {
	export struct AssetInfo {
		std::string filename;
		std::string localDirectory;
	};


	export template<typename T>
	struct Asset {

		std::optional<T> get() { return value; }
		Asset(std::optional<T> value) : value(value) {}
	private:
		std::optional<T> value;
	};
}