#include "InvertEffect.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

InvertEffect::InvertEffect() :
	PostProcessingLayer::Effect(),
	_shader(nullptr)
{
	Name = "Invert Effect";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/invert.glsl" }
	});
	
}

InvertEffect::~InvertEffect() = default;

void InvertEffect::Apply(const Framebuffer::Sptr & gBuffer)
{
	_shader->Bind();
	
	gBuffer->BindAttachment(RenderTargetAttachment::Depth, 1);
	gBuffer->BindAttachment(RenderTargetAttachment::Color1, 2); // The normal buffer
}

void InvertEffect::RenderImGui()
{
	//LABEL_LEFT(ImGui::ColorEdit4, "Color", &_outlineColor.x);
	
}

InvertEffect::Sptr InvertEffect::FromJson(const nlohmann::json & data)
{
	InvertEffect::Sptr result = std::make_shared<InvertEffect>();
	result->Enabled = JsonGet(data, "enabled", true);
	
	return result;
}

nlohmann::json InvertEffect::ToJson() const
{
	return {
		{ "enabled", Enabled }		
	};
}
