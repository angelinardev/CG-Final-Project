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
	if (body->GetGameObject()->Name == "ThingProjectile") //projectile was shot back
	{
		std::cout << "\nYou won!!\n";
		Application& app = Application::Get();
		//delete itself
		Gameplay::GameObject::Sptr context = GetGameObject()->SelfRef();
		app.CurrentScene()->RemoveGameObject(context);
	}
}

void EnemyHealth::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{

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


	
}

