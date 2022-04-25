#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"
#include "GLFW/glfw3.h"
#include "Gameplay/GameObject.h"
/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class SeekBehaviour : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<SeekBehaviour> Sptr;

	SeekBehaviour();
	virtual ~SeekBehaviour();
	Gameplay::Physics::RigidBody::Sptr _body;


	virtual void Awake() override;
	virtual void Update(float deltaTime) override;
	template<typename T>
	T Lerp(const T& p0, const T& p1, float t);
	virtual void RenderImGui() override;
	MAKE_TYPENAME(SeekBehaviour);
	virtual nlohmann::json ToJson() const override;
	static SeekBehaviour::Sptr FromJson(const nlohmann::json& blob);
	
	void seekTo(Gameplay::GameObject::Sptr& object);
protected:
	glm::vec3 _target;
};