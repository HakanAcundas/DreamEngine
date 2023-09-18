#pragma once

#include "Layer.h"
#include "../renderer/Renderer2D.h"

namespace dream {
	namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};
	}
}