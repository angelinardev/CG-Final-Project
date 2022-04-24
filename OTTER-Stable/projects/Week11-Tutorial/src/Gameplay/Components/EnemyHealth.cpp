#include "Gameplay/Components/EnemyHealth.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Application/Application.h"
#include "JumpBehaviour.h"

void EnemyHealth::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>(); //Gets the Physics Body that it's attached to
	if (_body == nullptr) {
		IsEnabled = false;
	}
	/*_body->SetLinearDamping(0.9f);
	_body->SetAngularDamping(1.f);*/
}

void EnemyHealth::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	if (body->GetGameObject()->Name == "Enemy" && !dead) //player has come in contact with the health box
	{
		if (GetGameObject()->Get<JumpBehaviour>()->in_air) //player is in air
		{
			was_hit = true;
		}
	}
}

void EnemyHealth::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	if (body->GetGameObject()->Name == "Enemy" && !dead) //player has come in contact with the health box
	{
		was_hit = false;
	}
}

void EnemyHealth::RenderImGui() {
	return;
}

nlohmann::json EnemyHealth::ToJson() const {
	return {
	};
}

EnemyHealth::EnemyHealth() :
	IComponent(), health(100)
	
{ }

EnemyHealth::~EnemyHealth() = default;

EnemyHealth::Sptr EnemyHealth::FromJson(const nlohmann::json & blob) {
	EnemyHealth::Sptr result = std::make_shared<EnemyHealth>();
	
	return result;
}


void EnemyHealth::Update(float deltaTime) {

	Application& app = Application::Get();
	if (was_hit)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, 0.0f, 2.0f));
		health -= 25;
		std::cout << "Enemy health = " << health << std::endl;
		was_hit = false;
		if (health <= 0)
		{
			dead = true;
		}
	}
	
}

