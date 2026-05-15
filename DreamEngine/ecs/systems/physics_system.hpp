#include "../system.hpp"
#include "../entity.hpp"
#include "../ecs_manager.hpp"

class PhysicsSystem : public System
{
public:

	void update(const float& dt, ECSManager& ecsm);
	//void EntityDestroyed(Entity entity);
};
