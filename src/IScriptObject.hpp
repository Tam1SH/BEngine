#pragma once
#include <string>

//TODO: бля, а нормальный кейс такой хуйнёй заниматься?
// не хуйня всё это надо удалить у других
//TODO: либы для юзания питона может и без такой хуйни обойтись, видимо как и луа
template<
    typename Function,
    typename Getter,
    typename Setter
    >
class IScriptObject {
public:
    virtual IScriptObject* SetProperty(std::string name, Getter get, Setter set) = 0;
    virtual IScriptObject* SetFunction(std::string name, Function func) = 0;
   // virtual IScriptObject* SetHandler(void* handler) = 0;
};