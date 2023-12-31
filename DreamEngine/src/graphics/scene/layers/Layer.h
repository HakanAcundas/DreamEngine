#pragma once
#include "../Renderer2D.h"

namespace dream { namespace graphics {

		class Layer
		{
		protected:
			std::string m_LayerName;
			Renderer2D& m_Renderer;
			std::vector<Renderable*> m_Renderables;
		public:
			Layer(Renderer2D& renderer, const std::string& name);
			virtual ~Layer() = default;
			// virtual void Render();
			virtual void AddRenderable(Renderable* renderable);
			virtual void RemoveRenderable(Renderable* renderable);

			const std::string& GetName() const { return m_LayerName; }

		};
}}
