export module Asset;
import <string>;
import <optional>;

namespace BEbraEngine {
	export class AssetInfo {
		std::string filename;
		std::string localDirectory;
	};


	export template<typename T>
	class Asset {
		std::optional<T*> get() { return value; }
		Asset(std::optional<T*> value) : value(value) {}
	private:
		std::optional<T*> value;
	};
}