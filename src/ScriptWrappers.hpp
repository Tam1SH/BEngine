#pragma once
#include "stdafx.h"
#include "AngelScriptEngine.hpp"
#include "AbstractScriptObject.hpp"
#include "RenderObject.hpp"
#include "GameObject.hpp"
#include "RigidBoby.hpp"
namespace BEbraEngine {
	namespace Wrappers {
		template<typename T>
		T* defaultFactory() {
			return new T();
		}
		template<typename T>
		void defaultRelease(T* t) {
			if (t) delete t;
		}

		template<typename T>
		void defaultAllocate(void* memory) {
			
			new(memory)T();
			std::cout << memory << std::endl;
		}
		template<typename T>
		void defaultDeallocate(void* memory) {
			std::cout << memory << std::endl;
			((T*)memory)->~T();

		}

		class _GameObject : public AbstractScriptObject {
			std::weak_ptr<GameObject> instance;
		};
		class _RigidBody : public AbstractScriptObject {
			std::weak_ptr<RigidBody> instance;
		};

		class _Vector3 : public AbstractScriptObject {
		public:
			static constexpr const char* __name = "Vector3";

			Vector3 instance{};

			static void registerObj(asIScriptEngine* engine) {

				int r = engine->RegisterObjectType(__name,
					sizeof(_Vector3), asOBJ_REF | asOBJ_SCOPED); assert(r >= 0);

				r = engine->RegisterObjectBehaviour(__name,
					asBEHAVE_FACTORY, "Vector3@ f()", asFUNCTION(defaultFactory<_Vector3>), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour(__name,
					asBEHAVE_RELEASE, "void f()", asFUNCTION(defaultRelease<_Vector3>), asCALL_CDECL_OBJLAST); assert(r >= 0);
				
				r = engine->RegisterObjectMethod(__name, 
					"Vector3& opAdd(const Vector3& in)", asMETHOD(_Vector3, operator+), asCALL_THISCALL); assert(r >= 0);
				
				r = engine->RegisterObjectMethod(__name,
					"Vector3& opSub(const Vector3& in)", asMETHOD(_Vector3, operator-), asCALL_THISCALL); assert(r >= 0);
				
				r = engine->RegisterObjectMethod(__name,
					"Vector3& opMul(const Vector3& in)", asMETHODPR(_Vector3, operator*, (const _Vector3&) const noexcept, _Vector3&), asCALL_THISCALL); assert(r >= 0);
				
				r = engine->RegisterObjectMethod(__name,
					"Vector3& opMul(float)", asMETHODPR(_Vector3, operator*, (float) const noexcept, _Vector3&), asCALL_THISCALL); assert(r >= 0);

				r = engine->RegisterObjectMethod(__name,
					"Vector3& opAddAssign(const Vector3& in)", asMETHOD(_Vector3, operator+=), asCALL_THISCALL); assert(r >= 0);
				
				r = engine->RegisterObjectMethod(__name,
					"Vector3& opMulAssign(const Vector3& in)", asMETHOD(_Vector3, operator*=), asCALL_THISCALL); assert(r >= 0);

				r = engine->RegisterObjectMethod(__name,
					"Vector3& opSubAssign(const Vector3& in)", asMETHOD(_Vector3, operator-=), asCALL_THISCALL); assert(r >= 0);


				r = engine->RegisterObjectProperty(__name,
					"float x", asOFFSET(Vector3, x), asOFFSET(_Vector3, instance), false); assert(r >= 0);

				r = engine->RegisterObjectProperty(__name,
					"float y", asOFFSET(Vector3, y), asOFFSET(_Vector3, instance), false); assert(r >= 0);

				r = engine->RegisterObjectProperty(__name,
					"float z", asOFFSET(Vector3, z), asOFFSET(_Vector3, instance), false); assert(r >= 0);
			}

			_Vector3(const _Vector3& vec) {
				instance = vec.instance;
			}

			_Vector3(const Vector3& vec) {
				instance = vec;
			}
			_Vector3(const Vector3&& vec) {

				instance = vec;
			}
			_Vector3() {}

			_Vector3& operator+(_Vector3& other) const noexcept {

				return _Vector3(std::move(instance + other.instance));
			}

			_Vector3& operator-(const _Vector3& other) const noexcept {

				return _Vector3(std::move(instance - other.instance));
			}

			_Vector3& operator*(const _Vector3& other) const noexcept {

				return _Vector3(std::move(instance * other.instance));
			}

			_Vector3& operator*(float scalar) const noexcept {

				return _Vector3(std::move(instance * scalar));
			}

			_Vector3* operator*=(const _Vector3& other) noexcept {
				*this = instance * other.instance;
				return this;
			}

			_Vector3* operator+=(const _Vector3& other) noexcept {
				*this = instance + other.instance;
				return this;
			}

			_Vector3* operator-=(const _Vector3& other) noexcept {
				*this = instance - other.instance;
				return this;
			}
		};
	}
}