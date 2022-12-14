
export module RenderBufferView;
import <memory>;
import RenderBuffer;


namespace BEbraEngine {

	export struct RenderBufferView {
		//RenderBuffer* buffer;
		std::shared_ptr<RenderBuffer> buffer;
		unsigned int availableRange{};
		unsigned int offset{};
		void setData(const void* data, unsigned int range, unsigned int offsetofData = 0) {
			if (range > availableRange) {
				//DEBUG_LOG1("the range is higher than acceptable: " + std::to_string(range) + " > " + std::to_string(availableRange));
			}
			else
				buffer->setData(data, range, offset + offsetofData);
		}

	};
}