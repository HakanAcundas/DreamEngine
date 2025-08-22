#include <application.h>
#include "game_layer.h"
using namespace dream;

int main(void)
{
    Application dream_engine;
    Shader *shader = new Shader(
        "../DreamTest/shaders/vertex.shader",
        "../DreamTest/shaders/fragment.shader");

    Camera camera(0.0f, 16.0f, 0.0f, 9.0f);
    camera.set_position(glm::vec3(4, 3, 0));

    Layer *game_layer = new GameLayer(shader, &camera);
    dream_engine.push_layer(game_layer);
    dream_engine.run();

    return 0;
}