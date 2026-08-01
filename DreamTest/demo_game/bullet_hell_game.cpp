#include "bullet_hell_game.hpp"
#include <memory>

void BulletHellGame::run()
{
  Renderer2D& renderer = m_dream_engine.get_renderer();
  ECManager& ecm = m_dream_engine.get_ecs_manager();
  EventDispatcher& ed = m_dream_engine.get_event_dispatcher();
  PhysicsEngine2D& ps = m_dream_engine.get_physic_engine();

  m_game_layer = std::make_shared<GameLayer>(renderer, ecm, ps, ed);;
  m_dream_engine.push_layer(m_game_layer);
  m_dream_engine.run();
}
