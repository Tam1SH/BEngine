#pragma once
#include "stdafx.h"
namespace BEbraEngine {

	class Debug
	{
	public:
		enum class ObjectType {
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
		static void enableAll() {
			_disableLog.clear();
		}
		static void disableAll() {
			for (int i = 0; i < (int)ObjectType::MaxValue; i++) {
				_disableLog.push_back((ObjectType)i);
			}

		}
		
		static void disableLog(ObjectType type) {
			if (auto item = std::find(_disableLog.begin(), _disableLog.end(), type);
				item == _disableLog.end()) 
			{
				std::stringstream str;
				str << "already disabled type (" << to_string(type) << ") or it is not in list";
				log(str.str());
			}
			else 
				_disableLog.push_back(type);

		}
		static void enableLog(ObjectType type) {
			if (auto item = std::find(_disableLog.begin(), _disableLog.end(), type);
				item != _disableLog.end())
			{
				std::stringstream str;
				str << "already enabled type (" << to_string(type) << ")";
				log(str.str());
			}
			else 
				_disableLog.erase(item);

		}
		static void log(std::string text) {
			std::stringstream str;
			str << "INFO: " << text;
			_log(str.str());
		}
		static void log(const std::string&& text, const void* handle, const std::string& name, ObjectType oType, MessageType mType) {

			std::stringstream str;
			if (auto item = std::find(_disableLog.begin(), _disableLog.end(), oType);
				item == _disableLog.end())
			{

				str << to_string(mType) << ": "
					<< text << " | ";

				if (handle)
					str << "handle = " << handle << " | ";

				if (!name.empty())
					str << "name = " << name << " | ";

				str << "type = " << to_string(oType);
				_log(str.str());
			}
		}
	private:
		static void _log(const std::string& str) {
			std::lock_guard g(m);
			std::cout << str << std::endl;
		}

		static std::string to_string(ObjectType type) {
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
		static std::string to_string(MessageType type) {
			switch (type) {
			case MessageType::Info: return "Info";
			case MessageType::Error: return "Error";
			}
			return "Unknown Type";
		}
		static std::mutex m;
		static std::vector<ObjectType> _disableLog;

	};
	

}
