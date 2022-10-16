// TODO: скрипт двигло
// TODO: сделать кластерный рендер
//TODO: начать делать хотя бы что-то со звуком 
//TODO: подумать на толчке о своей модели асинхронных задач в рендере.
//TODO: compile-time выбор рендера и связанных классов.
/*
TODO: подумать над реализацей:
****************************************************************************************
 * реализовать каким-то папочку в ведроиде, откуда данные таскать буду
****************************************************************************************

*/
#include <boost/filesystem.hpp>
#include "Engine.hpp"
#include <spdlog/spdlog.h>
import Debug;


#ifndef __ANDROID__
#undef main
#endif
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%H:%M:%S.%f] [%^%l%$] %v");
    //DEBUG_LOG1("BEGIN OF PIZDEC");
    BEbraEngine::Engine engine{};

    engine.Main({false,false});
    return 1337228;
}

