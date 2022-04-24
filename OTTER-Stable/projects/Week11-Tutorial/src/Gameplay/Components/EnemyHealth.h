#pragma once
#include "Gameplay/Components/IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

/// <summary>
/// Component That Controls the First Player
/// </summary>

class EnemyHealth : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<EnemyHealth> Sptr;

	EnemyHealth();
	virtual ~EnemyHealth();

	virtual void Awake() override;
	virtual void OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void Update(float deltaTime) override;

	virtual void RenderImGui() override;
	MAKE_TYPENAME(EnemyHealth);
	virtual nlohmann::json ToJson() const override;
	static EnemyHealth::Sptr FromJson(const nlohmann::json& blob);

	bool dead = false;
	
protected:
	
	
	Gameplay::Physics::RigidBody::Sptr _body;

	int health;
	bool was_hit = false;
	

};
