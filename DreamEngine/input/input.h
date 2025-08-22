#include <glm/glm.hpp>
#include "key_codes.h"
#include "mouse_codes.h"

namespace dream {

	class Input
	{
	private:
		static Input *s_input;
		Input();
	public:
		static Input* get_singleton() { return s_input; }

		bool is_key_pressed(int keyCode);
		bool is_mouse_button_pressed(MouseCode button);
		glm::vec2 get_mouse_position();
		glm::vec2 GetMouseOffset();

		float get_mouse_y();
		float get_mouse_x();

		float get_offset_x();
		float get_offset_y();
	};
}

