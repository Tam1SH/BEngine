#pragma once
#include "BaseScript.hpp"
#include <string>
#include <fstream>
//#include <filesystem>
//Вся эта хуйня похожа на абстрактую фабрику
//TODO: бля надо скрипты и на плюсах писать а то чё я бебра?
//бля а реально фабрика
namespace BEbraEngine {
    class IScriptFactory {
    public:
        virtual BaseScript* CreateScript(std::string code) = 0;
        //TODO: string bad идея для этого ( как и весь алгоритм)
        /*
        virtual std::string DownloadScript(const std::filesystem::path& path) {
            std::string code;
            std::string line;
            std::ifstream in(path);
            if (in.is_open())
            {
                while (getline(in, line))
                {
                    code += line + "\n";
                }
            }
            in.close();
            return code;
        }
        */
    };
}