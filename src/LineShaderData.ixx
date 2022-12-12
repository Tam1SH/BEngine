export module LineShaderData;

namespace BEbraEngine {

    export struct Vector3LineSharedDataTrashMSFixThisShit { 
        int x, y, z; 
        Vector3LineSharedDataTrashMSFixThisShit(int x, int y, int z) : x(x), y(y), z(z) {}
        Vector3LineSharedDataTrashMSFixThisShit() {}
    };
    export struct LineShaderData {
        alignas(16) Vector3LineSharedDataTrashMSFixThisShit from;
        alignas(16) Vector3LineSharedDataTrashMSFixThisShit to;
        alignas(16) Vector3LineSharedDataTrashMSFixThisShit color;
    };
}