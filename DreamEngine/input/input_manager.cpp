#include "input_manager.h"
#include <iostream>
namespace dream {

    InputManager& InputManager::get() {
        static InputManager instance;
        return instance;
    }

    void InputManager::bind_action(InputAction action, int key) {
        auto result = actionBindings.insert({action, key});
        if (!result.second) {
            std::cout << "Warning: action already bound. Overwriting." << std::endl;
        }
    }

    void InputManager::update() {
        previousState = currentState;

        for (const auto& [action, key] : actionBindings) {
            currentState[key] = Input::is_key_pressed(key);
        }
    }

    bool InputManager::is_action_pressed(InputAction action) const {
        auto it = actionBindings.find(action);
        if (it == actionBindings.end()) return false;
        int key = it->second;
        auto itCurrent = currentState.find(key);
        return itCurrent != currentState.end() && itCurrent->second;
    }

    bool InputManager::is_action_just_pressed(InputAction action) const {
        auto it = actionBindings.find(action);
        if (it == actionBindings.end())
            return false;
        int key = it->second;
        return currentState.at(key) && !previousState.at(key);
    }

    bool InputManager::is_action_just_released(InputAction action) const {
        auto it = actionBindings.find(action);
        if (it == actionBindings.end()) return false;
        int key = it->second;
        return !currentState.at(key) && previousState.at(key);
    }

}
