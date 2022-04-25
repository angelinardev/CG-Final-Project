#include "Gameplay/Components/SeekBehaviour.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "SeekBehaviour.h"
#include "Gameplay/Physics/RigidBody.h"
void SeekBehaviour::Awake()
{
    _body = GetComponent<Gameplay::Physics::RigidBody>();
    if (_body == nullptr) {
        IsEnabled = false;
    }
}

void SeekBehaviour::RenderImGui() {

}

nlohmann::json SeekBehaviour::ToJson() const {
    return {
    };
}
// Constructor Initializes Values for LERP and Set Position but Only SetPosition is being used atm
SeekBehaviour::SeekBehaviour() :
    IComponent()

{ }

SeekBehaviour::~SeekBehaviour() = default;

SeekBehaviour::Sptr SeekBehaviour::FromJson(const nlohmann::json & blob) {
    SeekBehaviour::Sptr result = std::make_shared<SeekBehaviour>();
    return result;
}

void SeekBehaviour::seekTo(Gameplay::GameObject::Sptr& object) {
    _target = object->GetPosition();
}

void SeekBehaviour::Update(float deltaTime)
{

    _target= GetGameObject()->GetScene()->FindObjectByName("Player")->GetPosition();

    glm::vec3 difference = _target-(_body->GetGameObject()->GetPosition()-glm::vec3(0.0f,0.0f,1.5f));
    //if 
    if (cbrt((difference.x * difference.x) + (difference.y * difference.y)+ (difference.z * difference.z))<1.0f) {
        difference = -difference;
   }

    _body->SetLinearVelocity(difference);
    GetGameObject()->LookAt(_target);

}

// Templated LERP function returns positon at current time for LERP
template <typename T>
T SeekBehaviour::Lerp(const T & p0, const T & p1, float t)
{
    return (1.0f - t) * p0 + t * p1;
}