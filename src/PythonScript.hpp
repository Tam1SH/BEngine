/*

#pragma once
#include "BaseScript.hpp"
#include "AbstractComponent.hpp"
#include <boost/python.hpp>
namespace BEbraEngine {
    using namespace boost::python;
    class PythonScript : public BaseScript
    {
    private:
        object main_module;
    public:
        PythonScript(object Module) : main_module(Module) { }
        void Initialization() override {
            try
            {
                PyObject* Init = object(main_module.attr("Init")).ptr();
                call<void>(Init);
            }
            catch (error_already_set) {
                PyErr_Print();

            }
        }
        void Run() override {
            try
            {
                PyObject* MainTick = object(main_module.attr("Tick")).ptr();
                call<void>(MainTick);
            }
            catch (error_already_set) {
                PyErr_Print();

            }
        }
        void Destroy() override { }
    };

}
*/