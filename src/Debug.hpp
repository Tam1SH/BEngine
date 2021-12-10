#pragma once
#include "stdafx.h"
namespace BEbraEngine {


#ifdef _DEBUG
#define DEBUG_DESTROY_CHECK_DECL() public: bool isDestroyed; private:
#else
#define DEBUG_DESTROY_CHECK_DECL()
#endif



#ifdef _DEBUG
#define DEBUG_DESTROY_CHECK(msg, handle, name, oType, mType) if(!isDestroyed) Debug::log(msg, handle, name, oType, mType)		
#else
#define DEBUG_DESTROY_CHECK(msg, handle, name, oType, mType) 
#endif

   

	class Debug
	{
	public:
		enum class ObjectType {
			Empty,
			GameObject,
			RenderObject,
			Transform,
			Collider,
			RigidBody,
			Script,
			Model,
			Buffer,
			BufferPool,
			DescriptorPool,
			MaxValue
		};
		enum class MessageType {
			Error,
			Info
		};
	public:
		static void enableAll();

		static void disableAll();
		
		static void disableLog(ObjectType type);

		static void enableLog(ObjectType type);

		static void log(std::string text);

		static void log(const std::string&& text, const void* handle, const std::string& name, ObjectType oType, MessageType mType);

	private:
		static void _log(const std::string& str);


		static std::string to_string(ObjectType type);

		static std::string to_string(MessageType type);

		static std::mutex m;

		static std::vector<ObjectType> _disableLog;

	};
	

}
