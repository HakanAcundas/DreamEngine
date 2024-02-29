#pragma once
#include "Renderer2D.h"

namespace dream { namespace graphics {

		class Layer
		{
		protected:
			std::string m_LayerName;
			std::vector<Renderable*> m_Renderables;
		public:
			Layer(const std::string& name);
			virtual ~Layer() = default;

			virtual void AddRenderable(Renderable* renderable);
			virtual void RemoveRenderable(Renderable* renderable);
			virtual void OnUpdate() {}
			virtual void OnEvent() {}

			const std::string& GetName() const { return m_LayerName; }

		};
}}
