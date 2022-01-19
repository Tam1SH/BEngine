#include "stdafx.h"
#include "Debug.hpp"
#include <iomanip>
namespace BEbraEngine {
	std::vector<Debug::ObjectType> Debug::_disableLog;
	std::mutex Debug::m;
	void Debug::enableAll()
	{
		_disableLog.clear();
	}
	void Debug::disableAll()
	{
		for (int i = 1; i < (int)ObjectType::MaxValue; i++) {
			_disableLog.push_back((ObjectType)i);
		}

	}
	void Debug::disableLog(ObjectType type)
	{
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
	void Debug::enableLog(ObjectType type)
	{
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
	void Debug::log(const std::stringstream& stream) {
		time_t t = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &t);

		std::stringstream str;
		str << "INFO: ";
		str << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << ": ";

		str << stream.str();
		_log(str.str());
	}
	void Debug::log(const std::string& text)
	{
		std::stringstream str;
		time_t t = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &t);


		str << "INFO: ";
		str << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << ": ";
		str << text;

		log(-1, "", str.str(), 0, "", ObjectType::Empty, MessageType::Info);
	}
	void Debug::log(int line, const char* nameFile, const std::string&& text)
	{
		log(line, nameFile, text, 0, "", ObjectType::Empty, MessageType::Info);
	}
	void Debug::log(int line, const char* nameFile, const std::string& text, const void* handle, const std::string& name, ObjectType oType, MessageType mType)
	{
		std::stringstream str;
		if (auto item = std::find(_disableLog.begin(), _disableLog.end(), oType);
			item == _disableLog.end())
		{
			time_t t = std::time(nullptr);
			std::tm tm;
			localtime_s(&tm, &t);

			str << to_string(mType) << ": " << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << ": "
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
	void Debug::log(const std::string& text, const void* handle, const std::string& name, ObjectType oType, MessageType mType)
	{
		log(-1, "", text, handle, name, ObjectType::Empty, MessageType::Info);
	}
	void Debug::_log(const std::string& str)
	{
		std::lock_guard g(m);
		std::cout << str << std::endl;
	}
	std::string Debug::to_string(ObjectType type)
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
	std::string Debug::to_string(MessageType type)
	{
		switch (type) {
		case MessageType::Info: return "Info";
		case MessageType::Error: return "Error";
		}
		return "Unknown Type";
	}
}