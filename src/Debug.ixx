#include "platform.hpp"

#include <sstream>
#include <iostream>
export module Debug;
import <vector>;
import <mutex>;
using std::vector;
using std::string;
using std::mutex;
using std::stringstream;

#define DEBUG_LOG1(msg) BEbraEngine::Debug::log(__LINE__, __FILE__, msg);
#define DEBUG_LOG2(msg, pointer, name, oType, mType) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer, name, oType, mType)
#define DEBUG_LOG3(msg, pointer) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer);

#ifdef _DEBUG
#define DEBUG_DESTROY_CHECK_DECL() public: bool isDestroyed; private:
#define DEBUG_DESTROY_CHECK(msg, pointer, name, oType, mType) if(!isDestroyed) BEbraEngine::Debug::log(__LINE__, __FILE__, msg, pointer, name, oType, mType)	
//export DEBUG_DESTROY_CHECK_DECL;
//export DEBUG_DESTROY_CHECK;
#else
#define DEBUG_DESTROY_CHECK(msg, pointer, name, oType, mType) 
#define DEBUG_DESTROY_CHECK_DECL()
//export DEBUG_DESTROY_CHECK_DECL;
//export DEBUG_DESTROY_CHECK;
#endif



namespace BEbraEngine {




	export class Debug
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

		static void enableAll()
		{
			_disableLog.clear();
		}
		static void disableAll()
		{
			for (int i = 1; i < (int)ObjectType::MaxValue; i++) {
				_disableLog.push_back((ObjectType)i);
			}

		}
		static void disableLog(ObjectType type)
		{
			if (auto item = BE_STD::find(_disableLog.begin(), _disableLog.end(), type);
				item == _disableLog.end())
			{
				BE_STD::stringstream str;
				str << "already disabled type (" << to_string(type) << ") or it is not in list";
				log(str.str());
			}
			else
				_disableLog.push_back(type);

		}
		static void enableLog(ObjectType type)
		{
			if (auto item = std::find(_disableLog.begin(), _disableLog.end(), type);
				item != _disableLog.end())
			{
				BE_STD::stringstream str;
				str << "already enabled type (" << to_string(type) << ")";
				log(str.str());
			}
			else
				_disableLog.erase(item);

		}
		static void log(int line, const char* nameFile, const std::stringstream& stream) {
			time_t t = std::time(nullptr);
			BE_STD::tm tm{};
#ifndef __ANDROID__
			localtime_s(&tm, &t);
#endif


			std::stringstream str;
			str << "INFO: " << nameFile << "(" << line << ") | ";
			str << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " | ";

			str << stream.str();
			_log(str.str());
		}
		static void log(const std::string& text)
		{
			std::stringstream str;
			time_t t = std::time(nullptr);
			std::tm tm{};
#ifndef __ANDROID__
			localtime_s(&tm, &t);
#endif

			str << "INFO: ";
			str << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << ": ";
			str << text;

			log(-1, "", str.str(), 0, "", ObjectType::Empty, MessageType::Info);
		}
		static void log(int line, const char* nameFile, const std::string&& text)
		{
			log(line, nameFile, text, 0, "", ObjectType::Empty, MessageType::Info);
		}
		static void log(int line, const char* nameFile, const std::string& text, const void* handle, const std::string& name, ObjectType oType, MessageType mType)
		{
			std::stringstream str;
			if (auto item = std::find(_disableLog.begin(), _disableLog.end(), oType);
				item == _disableLog.end())
			{
				time_t t = std::time(nullptr);
				std::tm tm{};
#ifndef __ANDROID__
				localtime_s(&tm, &t);
#endif


				str << to_string(mType) << ": " << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << ": " << "(" << nameFile << ": " << line << ") "
					<< text << " | ";

				if (handle)
					str << "handle = " << handle << " | ";

				if (!name.empty())
					str << "name = " << name << " | ";
				if (oType != ObjectType::Empty)
					str << "type = " << to_string(oType);
				_log(str.str());
			}
		}
		static void log(const std::string& text, const void* handle, const std::string& name, ObjectType oType, MessageType mType)
		{
			log(-1, "", text, handle, name, ObjectType::Empty, MessageType::Info);
		}
		static void _log(const std::string& str)
		{
			std::lock_guard g(m);
			std::cout << str << std::endl;
		}
		static std::string to_string(ObjectType type)
		{
			switch (type) {
			case ObjectType::Buffer: return "Buffer";
			case ObjectType::GameObject: return "GameObject";
			case ObjectType::RenderObject: return "RenderObject";
			case ObjectType::Transform: return "Transform";
			case ObjectType::Collider: return "Collider";
			case ObjectType::RigidBody: return "RigidBody";
			case ObjectType::Script: return "Script";
			case ObjectType::Model: return "Model";
			case ObjectType::BufferPool: return "BufferPool";
			case ObjectType::DescriptorPool: return "DescriptorPool";
			}
			return "Unknown Type";
		}
		static std::string to_string(MessageType type)
		{
			switch (type) {
			case MessageType::Info: return "Info";
			case MessageType::Error: return "Error";
			}
			return "Unknown Type";
		}

		static mutex m;

		static vector<ObjectType> _disableLog;

	};
	BE_STD::vector<Debug::ObjectType> Debug::_disableLog;
	BE_STD::mutex Debug::m;


}