#pragma once
#include "renderer2D.h"

namespace dream { namespace graphics {

		class Layer
		{
		protected:
			std::string m_LayerName;
			std::vector<std::shared_ptr<Entity>> m_Entities;
		public:
			Layer(const std::string& name);
			virtual ~Layer() = default;

			virtual void AddRenderable(Entity* entity);
			virtual void RemoveRenderable(Entity* entity);
			virtual void OnUpdate() {}
			virtual void OnEvent(Event& e) {}

			const std::string& GetName() const { return m_LayerName; }

		};
}}
