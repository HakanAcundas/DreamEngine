#pragma once
#include <unordered_map>
#include "input.h"

namespace dream {

enum class InputAction {
    MoveCameraUp,
    MoveCameraDown,
    MoveCameraLeft,
    MoveCameraRight,
    Jump,
    Attack,
    Pause,
    COUNT
};

class InputManager {
    public:
        static InputManager& get();

        void bind_action(InputAction action, int key);
        void update();

        bool is_action_pressed(InputAction action) const;
        bool is_action_just_pressed(InputAction action) const;
        bool is_action_just_released(InputAction action) const;

    private:
        std::unordered_map<InputAction, int> actionBindings;
        std::unordered_map<int, bool> currentState;
        std::unordered_map<int, bool> previousState;

        InputManager() = default;
};
}