#pragma once

namespace Moai
{
    class HelloTriangleRenderer
    {
    public:
        HelloTriangleRenderer();
        ~HelloTriangleRenderer();
        void Draw();
        void UpdateWindowSize(GLsizei width, GLsizei height);

    private:
        GLuint mProgram;
    };
}