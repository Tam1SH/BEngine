
#include "BEbraAndroid.h"
#include <vulkan/vulkan.h>
#include <oneapi/tbb.h>
#include "Engine.hpp"
#include "AbstractRender.hpp"
#include <Physics/btBulletCollisionCommon.h>
#include "Physics.hpp"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "BEbraAndroid", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "BEbraAndroid", __VA_ARGS__))

#include "platform.hpp"
extern "C" {

	/* Эта тривиальная функция возвращает ABI платформы, для которой скомпилирована эта динамическая библиотека с машинным кодом.*/
	const char * BEbraAndroid::getPlatformABI()
	{
	#if defined(__arm__)
	#if defined(__ARM_ARCH_7A__)
	#if defined(__ARM_NEON__)
		#define ABI "armeabi-v7a/NEON"
	#else
		#define ABI "armeabi-v7a"
	#endif
	#else
		#define ABI "armeabi"
	#endif
	#elif defined(__i386__)
		#define ABI "x86"
	#else
		#define ABI "unknown"
	#endif
		btVector3 d;
		LOGI("This dynamic shared library is compiled with ABI: %s", ABI);
		vkCmdDraw(0, 0, 0, 0, 0);
		tbb::parallel_for(0, 0, [](size_t) {});
		BEbraEngine::Engine eng;
		//eng.Main();
		return "This native library is compiled with ABI: %s" ABI ".";
	}

	void BEbraAndroid()
	{
	}

	BEbraAndroid::BEbraAndroid()
	{
	}

	BEbraAndroid::~BEbraAndroid()
	{
	}
}
