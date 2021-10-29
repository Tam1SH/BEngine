#include "stdafx.h"
/*

#include "PythonEngine.hpp"
#include "BaseScriptEngine.hpp"
#include "BaseScript.hpp"
#include "PythonScript.hpp"
#include <boost/python.hpp>
#include <string>
namespace BEbraEngine {
    using std::string;


    using namespace boost::python;

    //inline void printMessage(const std::string& s) {
    //    printf(s.c_str());
    //}

    PythonEngine::PythonEngine()
    {
        //PyImport_AppendInittab("BebraEngine", &PyInit_example);
        Py_Initialize();
    }

    BaseScript* PythonEngine::CreateScript(std::string code)
    {
        try
        {


            object main_module((
                handle<>(borrowed(PyImport_AddModule("__main__")))));

            object main_namespace = main_module.attr("__dict__");
            //object BebraEngine_module((handle<>(PyImport_ImportModule("BebraEngine"))));

            //main_namespace["BebraEngine"] = BebraEngine_module;

            handle<> ignored((PyRun_String(code.c_str(), Py_file_input,
                main_namespace.ptr(),
                main_namespace.ptr())));
            return new PythonScript(main_module);

        }
        catch (error_already_set) {
            PyErr_Print();

        }
    }
}
*/