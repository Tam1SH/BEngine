export module RenderHelper;
import Vector3;

namespace BEbraEngine {
	export class RenderHelper {
	public:
		virtual void drawLine(
			const Vector3& from,
			const Vector3& to,
			const Vector3& color) = 0;
	};
}