#include <iostream>
#include <map>
#include <vector>
#include "../window/Window.h"
#include <GLFW/glfw3.h>


namespace dream {
    class KeyInput {
    private:
        void setIsKeyDown(int key, bool isDown);
        std::map<int, bool> _keys;
        Window* m_Window;
        bool _isEnabled;
        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static std::vector<KeyInput*> _instances;
    public:
        KeyInput(std::vector<int> keysToMonitor);
        ~KeyInput();

        bool getIsKeyDown(int key);
        bool getIsEnabled() { return _isEnabled; }
        Window* getWindow() { return m_Window; }

        void setIsEnabled(bool value) { _isEnabled = value; }
        void setupKeyInputs(Window& window);
        void setKeys(std::vector<int> keysToMonitor)
        {
            for (int key : keysToMonitor) {
                _keys[key] = false;
            }
        }
    };
}
