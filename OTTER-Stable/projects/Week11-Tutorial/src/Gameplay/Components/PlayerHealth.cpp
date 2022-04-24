#include "Gameplay/Components/PlayerHealth.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Application/Application.h"
#include "JumpBehaviour.h"

void PlayerHealth::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>(); //Gets the Physics Body that it's attached to
	if (_body == nullptr) {
		IsEnabled = false;
	}
	/*_body->SetLinearDamping(0.9f);
	_body->SetAngularDamping(1.f);*/
}

void PlayerHealth::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	if (body->GetGameObject()->Name == "Player" && !dead) //this trigger has entered to the player
	{
		if (!body->GetGameObject()->Get<JumpBehaviour>()->in_air)//not jumping
		{
			is_attacking = true;
			body2 = body;
		} 
	}
}

void PlayerHealth::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	if (body->GetGameObject()->Name == "Player" && !dead) //this trigger has entered to the player
	{
		is_attacking = false;
	}
}

void PlayerHealth::RenderImGui() {
	return;
}

nlohmann::json PlayerHealth::ToJson() const {
	return {
	};
}

PlayerHealth::PlayerHealth() :
	IComponent(), health(100)
	
{ }

PlayerHealth::~PlayerHealth() = default;

PlayerHealth::Sptr PlayerHealth::FromJson(const nlohmann::json & blob) {
	PlayerHealth::Sptr result = std::make_shared<PlayerHealth>();
	
	return result;
}


void PlayerHealth::Update(float deltaTime) {

	Application& app = Application::Get();
	if (is_attacking)
	{
		health -= 25;
		std::cout << "Player health = " << health << std::endl;

		glm::mat3 globalRot = glm::mat3_cast(GetGameObject()->GetRotation());
		direction = glm::normalize(glm::vec3(globalRot[2][0], globalRot[2][1], globalRot[2][2]));
		direction *= -1.0f;
		direction *= speed;
		body2->ApplyImpulse(direction); //PUSH THE PLAYER BACK
		is_attacking = false;
		if (health <= 0)
		{
			dead = true;
		}
	}
	
}

