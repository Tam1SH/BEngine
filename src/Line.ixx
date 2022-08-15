

export module Line;
import <memory>;
import RenderBuffer;
import Vector3;
import Transform;

namespace BEbraEngine {
    /*
    class Line : public IRenderData {
    public:
        struct ShaderData {
            alignas(16) Vector3 from;
            alignas(16) Vector3 to;
            alignas(16) Vector3 color;
        };
    public:
        ShaderData _data;

        Line(const Vector3& from = Vector3(0), const Vector3& to = Vector3(0), const Vector3& color = Vector3(0)) :
            from(from), to(to), color(color) { }
        ~Line();

        const void* getData() noexcept override {

            _data.color = color;
            _data.from = from;
            _data.to = to;
            return &data;
        }
        size_t getDataSize() const noexcept override {
            return sizeof(ShaderData);
        }

        Vector3 from;
        Vector3 to;
        Vector3 color;

        void create(Render& render);

        void update();

        shared_ptr<RenderBufferView> data;
        shared_ptr<RenderBuffer> vertices;
        shared_ptr<Transform> transform;
    };
    */

}