#pragma once
#include "stdafx.h"
#include "BaseScript.hpp"


namespace BEbraEngine {
    class BaseScriptEngine {
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