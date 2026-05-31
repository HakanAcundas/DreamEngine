//#pragma once
//
//#include <memory>
//#include <assert.h>
//#include <unordered_map>
//#include "signature.hpp"
//#include "system.hpp"
//
//class SystemManager
//{
//public:
//	template<typename T>
//	std::shared_ptr<T> register_system()
//	{
//		const char* type_name = typeid(T).name();
//		assert(m_systems.find(type_name) == m_systems.end() && "Registering system more than onece.");
//
//		std::shared_ptr<T> system = std::make_shared<T>();
//		m_systems.insert({ type_name, system });
//	
//		return system;
//	}
//
//	template<typename T>
//	void set_signature(Signature signature)
//	{
//		const char* type_name = typeid(T).name();
//		assert(m_systems.find(type_name) != m_systems.end() && "System used before registered.");
//
//		m_signatures.insert({ type_name, signature });
//	}
//
//	void entity_destroyed(Entity entity)
//	{
//		for (const std::pair<const char*, SystemPtr> pair : m_systems)
//		{
//			const SystemPtr system = pair.second;
//			system->m_entities.erase(entity);
//		}
//	}
//
//	void entity_signature_changed(Entity entity, Signature entity_signature)
//	{
//		for (const std::pair<const char*, SystemPtr> pair : m_systems)
//		{
//			const char* type = pair.first;
//			SystemPtr system = pair.second;
//			Signature system_signature = m_signatures[type];
//			
//			// Entity signature matches system signature - insert into set
//			if ((system_signature & entity_signature) == entity_signature)
//			{
//				system->m_entities.insert(entity);
//			}
//			// Entity signature does not match system signature - erase from set
//			else
//			{
//				system->m_entities.erase(entity);
//			}
//		}
//	}
//
//private:
//	using SystemPtr = std::shared_ptr<System>;
//	std::unordered_map<const char*, SystemPtr> m_systems;
//	std::unordered_map<const char*, Signature> m_signatures;
//};
