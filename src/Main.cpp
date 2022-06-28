// TODO: скрипт двигло
// TODO: сделать кластерный рендер
//TODO: начать делать хотя бы что-то со звуком 
//TODO: реализовать систему частиц(партикле сустемXD) 
//TODO: подумать на толчке о своей модели асинхронных задач в рендере.
/*
TODO: подумать над реализацей:
****************************************************************************************
 * реализовать каким-то хуем папочку в ведроиде, откуда данные таскать буду
****************************************************************************************

*/

#include "stdafx.h"
#include "Engine.hpp"
#include "Debug.hpp"


#ifndef __ANDROID__
#undef main
#endif
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char* argv[])
{
    DEBUG_LOG1("BEGIN OF PIZDEC");
    BEbraEngine::Engine engine;
    engine.Main({false,true});
    return 1337228;
}

