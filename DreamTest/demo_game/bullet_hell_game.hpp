#pragma once

#include <application.hpp>
#include "layers/game_layer.hpp"
#include <iostream>

using namespace dream;

class BulletHellGame
{
public:
    void run();

private:
    Application m_dream_engine;
    std::shared_ptr<GameLayer> m_game_layer;
    // TODO: UI Layer
    //Layer* m_ui_layer;
};
