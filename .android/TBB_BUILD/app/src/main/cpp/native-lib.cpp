
#include "Physics/btBulletDynamicsCommon.h"
#include <tbb/tbb.h>
#include <jni.h>
#include <string>
#include "SDL2-2.0.16/include/SDL.h"
#include <vulkan/vulkan.h>
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_tbb_1build_MainActivity_JNI(JNIEnv *env, jobject) {



    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher;

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache;

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* solver;

    btDiscreteDynamicsWorld* dynamicsWorld;

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    std::string str;
    tbb::parallel_invoke([&]{str = "PIZDA 1";},
                         [&]{str = "PIZDA 2";});



    SDL_Log("INVOKE");
    return  env->NewStringUTF(str.c_str());

}

extern "C"
JNIEXPORT jint JNICALL
Java_org_libsdl_app_SDLActivity_nativeRunMain__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_Object_2(
        JNIEnv *env, jclass clazz, jstring library, jstring function, jobject arguments) {
    return main(2, reinterpret_cast<char **>(arguments));
}

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{

    SDL_log(argv[0][0]);
    SDL_Log("START");
    return 0;
}



