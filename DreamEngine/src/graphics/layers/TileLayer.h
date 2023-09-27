#pragma once
#include "Layer.h"

namespace dream {
	namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer();
			TileLayer(Shader* shader, Camera camera);
			~TileLayer();
		};
	}
}