#pragma once
#include "stdafx.h"
class Debug
{
public:
	enum class ObjectType {
		GameObject,
		RenderObject,
		Script,
		Model,
		Buffer,
		BufferPool
	};
	enum class MessageType {
		Error,
		Info
	};
public:
	static void Log(std::string text) {
		std::cout << "INFO: " << text << std::endl;
	}
	static void log(const std::string&& text, const void* handle,std::string&& name,  ObjectType oType, MessageType mType) {

		std::cout << to_string(mType) << " | "
		<< handle << " | "
		<< name << " | "
		<< to_string(oType) << " | "
		<< text << std::endl;
	}
private:
	static std::string to_string(ObjectType type){
		switch (type) {
		case ObjectType::Buffer: return "Buffer";
		case ObjectType::GameObject: return "GameObject";
		case ObjectType::RenderObject: return "RenderObject";
		case ObjectType::Script: return "Script";
		case ObjectType::Model: return "Model";
		case ObjectType::BufferPool: return "BufferPool";
		}
	}
	static std::string to_string(MessageType type) {
		switch (type) {
		case MessageType::Info: return "Info";
		case MessageType::Error: return "Error";
		}
	}

};

