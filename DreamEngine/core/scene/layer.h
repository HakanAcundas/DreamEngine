#pragma once
#include "renderer2D.h"
#include "scene_object.h"

namespace dream { namespace graphics {

		class Layer
		{
		protected:
			std::string m_layer_name;
			std::vector<std::shared_ptr<SceneObject>> m_scene_objects;
		public:
			Layer(const std::string &name);
			virtual ~Layer() = default;

			virtual void add_scene_object(SceneObject *object);
			virtual void remove_scene_object(SceneObject *object);
			virtual void on_update() = 0;
			// virtual void on_event(Event &e) = 0;

			const std::string& get_name() const { return m_layer_name; }

		};
}}
