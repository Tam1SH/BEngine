// TODO: скрипт двигло
// TODO: сделать кластерный рендер
//TODO: начать делать хотя бы что-то со звуком 
/*
TODO: подумать над реализацей:
****************************************************************************************
 * реализовать каким-то папочку в ведроиде, откуда данные таскать буду
****************************************************************************************

*/
#include <boost/filesystem.hpp>
#include "Engine.hpp"
import Debug;
import Logger;

#ifndef __ANDROID__
#undef main
#endif
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char* argv[])
{
    BEbraEngine::Logger::init();

    //DEBUG_LOG1("BEGIN OF PIZDEC");
    BEbraEngine::Engine engine{};

    engine.Main({false,false});
    return 1337228;
}

