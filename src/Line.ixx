module;
export module Line;
import RenderBuffer;
import RenderBufferView;
import Vector3;


namespace BEbraEngine {
    export class Line {
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
        ~Line()
        {

        }


        Vector3 from;
        Vector3 to;
        Vector3 color;

        void update()
        {
            //_data = { from, to, color };

        }
        RenderBufferView* data;
        RenderBuffer* vertices;
       // std::shared_ptr<RenderBufferView> data;
        //std::shared_ptr<RenderBuffer> vertices;
    };



}