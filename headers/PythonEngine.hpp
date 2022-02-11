#pragma once
#include "BaseScriptEngine.hpp"
#include "BaseScript.hpp"

namespace BEbraEngine {
    class PythonEngine : public IScriptFactory
    {
    private:

    public:
        PythonEngine();

        BaseScript* CreateScript(std::string code) override;
    };
}