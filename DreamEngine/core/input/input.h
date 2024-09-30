#include <glm/glm.hpp>
#include "key_codes.h"
#include "mouse_codes.h"

namespace dream {

	class Input
	{
	private:
		static Input* s_Input;
		Input();
	public:
		static Input* GetSingleton() { return s_Input; }

		bool IsKeyPressed(int keyCode);
		bool IsMouseButtonPressed(MouseCode button);
		glm::vec2 GetMousePosition();
		glm::vec2 GetMouseOffset();

		float GetMouseY();
		float GetMouseX();

		float GetXOffset();
		float GetYOffset();
	};
}

