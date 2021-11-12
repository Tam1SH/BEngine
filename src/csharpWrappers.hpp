#pragma once
#include "Vector3.hpp"
namespace BEbraEngine {
	namespace ScriptWrappers {
		class Vector3Wrapper{
		public:
			static Vector3 plus(Vector3 left, Vector3 right) {
				return left + right;
			}
			static Vector3 mult(Vector3 left, Vector3 right) {
				return left * right;
			}
			static Vector3 mult(Vector3 left, float right) {
				return left * right;
			}

		};
	}
}