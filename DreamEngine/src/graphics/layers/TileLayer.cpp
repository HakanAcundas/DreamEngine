#include "TileLayer.h"

namespace dream {
	namespace graphics {

		TileLayer::TileLayer()
			: Layer(new Renderer2D(), m_Shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{

		}

		TileLayer::TileLayer(Shader* shader, Camera camera)
			: Layer(new Renderer2D(), shader, camera)
		{

		}

		TileLayer::~TileLayer()
		{

		}
	}
}