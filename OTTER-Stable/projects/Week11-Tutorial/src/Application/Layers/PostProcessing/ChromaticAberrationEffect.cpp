#include "ChromaticAberrationEffect.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

ChromaticAberrationEffect::ChromaticAberrationEffect() :
	ChromaticAberrationEffect(true) { }


ChromaticAberrationEffect::ChromaticAberrationEffect(bool enabled) :
	PostProcessingLayer::Effect(),
	_shader(nullptr),
	_strength(3)
{
	Name = "Chromatic Aberration";
	Enabled = enabled;
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/Chromatic_Aberration.glsl" }
	});

}

ChromaticAberrationEffect::~ChromaticAberrationEffect() = default;

void ChromaticAberrationEffect::Apply(const Framebuffer::Sptr& gBuffer)
{
	_shader->Bind();
	_shader->SetUniform("u_Strength", _strength);
}

void ChromaticAberrationEffect::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat, "Strength", &_strength, -100, 100);
}

ChromaticAberrationEffect::Sptr ChromaticAberrationEffect::FromJson(const nlohmann::json& data)
{
	ChromaticAberrationEffect::Sptr result = std::make_shared<ChromaticAberrationEffect>(false);
	result->Enabled = JsonGet(data, "enabled", true);
	result->_strength = JsonGet(data, "strength", result->_strength);
	return result;
}

nlohmann::json ChromaticAberrationEffect::ToJson() const
{
	return {
		{ "enabled", Enabled },
		{ "strength", _strength }
	};
}
