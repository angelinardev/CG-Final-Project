#include "Gameplay/Components/ProjectileBehaviour.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Application/Application.h"
#include "Application/Layers/PostProcessingLayer.h"
#include "Application/Layers/PostProcessing/ChromaticAberrationEffect.h"
#include "Application/Timing.h"
#include "Gameplay/InputEngine.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/Material.h"
#include "Gameplay/MeshResource.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Graphics/Textures/Texture2D.h"
#include "Utils/GlmDefines.h"
#include "Gameplay/Components/SeekBehaviour.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/Colliders/SphereCollider.h"

void ProjectileBehaviour::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void ProjectileBehaviour::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse", &_impulse, 1.0f);
}

nlohmann::json ProjectileBehaviour::ToJson() const {
	return {
		{ "impulse", _impulse }
	};
}

ProjectileBehaviour::ProjectileBehaviour() :
	IComponent(),
	_impulse(10.0f)
{ }
void ProjectileBehaviour::PassMaterial(Gameplay::Material::Sptr mat) {
	ProjectileMat = mat;
}

void ProjectileBehaviour::SpawnThing() {
	using namespace Gameplay;
	Application& app = Application::Get();

	GameObject::Sptr Thing = app.CurrentScene()->CreateGameObject("ThingProjectile");
	{
		MeshResource::Sptr sphere = ResourceManager::CreateAsset<MeshResource>();
		sphere->AddParam(MeshBuilderParam::CreateIcoSphere(ZERO, ONE, 5));
		sphere->GenerateMesh();
		Thing->SetScale(glm::vec3(0.25f));
		Thing->SetPostion(GetGameObject()->GetPosition()-glm::vec3(1.f));

		// Add a render component
		RenderComponent::Sptr renderer = Thing->Add<RenderComponent>();
		renderer->SetMesh(sphere);
		renderer->SetMaterial(ProjectileMat);

		SeekBehaviour::Sptr seek = Thing->Add<SeekBehaviour>();
		
		seek->seekTo(app.CurrentScene()->FindObjectByName("Player"));
		seek->IsEnabled = true;

		// Add a dynamic rigid body to this monkey
		Gameplay::Physics::RigidBody::Sptr physics = Thing->Add<Gameplay::Physics::RigidBody>(RigidBodyType::Dynamic);
		Gameplay::Physics::SphereCollider::Sptr Sphere = Gameplay::Physics::SphereCollider::Create();
		Sphere->SetRadius(Sphere->GetRadius() / 4);

		physics->AddCollider(Sphere);

		Thing->Get<Gameplay::Physics::RigidBody>()->SetAngularFactor(glm::vec3(0.0f, 0.0f, 0.0f));
		Thing->Get<Gameplay::Physics::RigidBody>()->SetLinearDamping(0.9f);
		//GetGameObject()->AddChild(Thing);

	}
}

ProjectileBehaviour::~ProjectileBehaviour() = default;

ProjectileBehaviour::Sptr ProjectileBehaviour::FromJson(const nlohmann::json& blob) {
	ProjectileBehaviour::Sptr result = std::make_shared<ProjectileBehaviour>();
	result->_impulse = blob["impulse"];
	return result;
}

void ProjectileBehaviour::Update(float deltaTime) {
	_timer += deltaTime;
	Application& app = Application::Get();
	ChromaticAberrationEffect::Sptr Chromatic = app.GetLayer<PostProcessingLayer>()->GetEffect<ChromaticAberrationEffect>();
			
	Chromatic->_strength = _timer * 10;

	//LOG_INFO(_timer);
	if (_timer >= 5.0f) {
		LOG_WARN("the thing was spawned");
		_timer -= 5.0f;
		SpawnThing();
	}
}

