#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/Material.h"


/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class ProjectileBehaviour : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<ProjectileBehaviour> Sptr;

	std::weak_ptr<Gameplay::IComponent> Panel;

	ProjectileBehaviour();
	virtual ~ProjectileBehaviour();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;
	void SpawnThing();
	void PassMaterial(Gameplay::Material::Sptr mat);
public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(ProjectileBehaviour);
	virtual nlohmann::json ToJson() const override;
	static ProjectileBehaviour::Sptr FromJson(const nlohmann::json& blob);

protected:
	float _impulse;
	float _timer=0;
	Gameplay::Material::Sptr ProjectileMat;

	bool _isPressed = false;
	Gameplay::Physics::RigidBody::Sptr _body;
};