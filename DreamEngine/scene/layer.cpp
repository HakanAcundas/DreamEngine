#include "layer.h"

namespace dream { namespace graphics {

	Layer::Layer(const std::string &name = "Dream Layer")
		: m_layer_name(name)
	{

	}

	void Layer::add_scene_object(SceneObject *object)
	{
		m_scene_objects.emplace_back(object);
	}

	void Layer::remove_scene_object(SceneObject *object)
	{
		auto it = std::find_if(m_scene_objects.begin(), m_scene_objects.end(),
			[object](const std::shared_ptr<SceneObject>& ptr) {
				return ptr.get() == object;
			});
		if (it != m_scene_objects.end())
			m_scene_objects.erase(it);
	}
}}
