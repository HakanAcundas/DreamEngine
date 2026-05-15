#include <application.hpp>
#include "game_layer.hpp"
#include <iostream>

using namespace dream;

int main(void)
{
    Application dream_engine;

    Shader shader(
        "../DreamTest/shaders/vertex.shader",
        "../DreamTest/shaders/fragment.shader");
    Camera camera(0.0f, 16.0f, 0.0f, 9.0f);
    dream_engine.set_camera(camera);
    dream_engine.set_shader(shader);
    
    EventDispatcher& ed = dream_engine.get_event_dispatcher();
    ed.listen(EventType::MouseMovedEvent, std::bind(&Camera::on_event, camera, std::placeholders::_1));
    
    Layer* game_layer = new GameLayer(shader, camera);
    dream_engine.push_layer(game_layer);
    dream_engine.run();

    return 0;
}