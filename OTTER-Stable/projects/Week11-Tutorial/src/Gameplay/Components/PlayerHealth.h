#pragma once
#include "Gameplay/Components/IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

/// <summary>
/// This will attached TO THE ENEMY to calculate player health and "attacking"
/// </summary>

class PlayerHealth : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<PlayerHealth> Sptr;

	PlayerHealth();
	virtual ~PlayerHealth();

	virtual void Awake() override;
	virtual void OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void Update(float deltaTime) override;

	virtual void RenderImGui() override;
	MAKE_TYPENAME(PlayerHealth);
	virtual nlohmann::json ToJson() const override;
	static PlayerHealth::Sptr FromJson(const nlohmann::json& blob);

	bool dead = false;
	
protected:
	
	
	Gameplay::Physics::RigidBody::Sptr _body;
	bool is_attacking = false;
	float speed = 1.0f;
	
	glm::vec3 direction;
	int health;
	//default is our body
	std::shared_ptr<Gameplay::Physics::RigidBody> body2 = nullptr;

};
