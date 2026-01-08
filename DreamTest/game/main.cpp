#include <application.hpp>
#include "game_layer.hpp"
#include <iostream>

using namespace dream;

int main(void)
{
    Application dream_engine;
    Shader *shader = new Shader(
        "shaders/vertex.shader",
        "shaders/fragment.shader");

    Layer *game_layer = new GameLayer(shader);
    dream_engine.push_layer(game_layer);
    dream_engine.run();

    return 0;
}