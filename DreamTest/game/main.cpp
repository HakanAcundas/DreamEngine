#include "core/Application.h"
#include "GameLayer.h"
using namespace dream;

int main(void)
{
    Application dreamEngine;
    Shader* shader = new Shader(
        "shaders/vertex.shader",
        "shaders/fragment.shader");

    Camera camera(-16.0f, 16.0f, -9.0f, 9.0f);
    camera.SetPosition(glm::vec3(4, 3, 0));
    dreamEngine.PushLayer(new GameLayer(shader, &camera));
    dreamEngine.Run();

    return 0;
}