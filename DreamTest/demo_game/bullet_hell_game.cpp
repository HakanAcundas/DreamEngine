#include "bullet_hell_game.hpp"

void BulletHellGame::run()
{
    Shader shader(
        "../DreamTest/shaders/vertex.shader",
        "../DreamTest/shaders/fragment.shader");
    Camera camera(0.0f, 16.0f, 0.0f, 9.0f);

    m_dream_engine.set_camera(camera);
    m_dream_engine.set_shader(shader);

    ECSManager ecsm = m_dream_engine.get_ecs_manager();
    EventDispatcher& ed = m_dream_engine.get_event_dispatcher();
    PhysicsEngine2D& ps = m_dream_engine.get_physic_engine();

    m_game_layer = new GameLayer(shader, camera, ecsm, ed, ps);
    m_dream_engine.push_layer(m_game_layer);
    m_dream_engine.run();
}
