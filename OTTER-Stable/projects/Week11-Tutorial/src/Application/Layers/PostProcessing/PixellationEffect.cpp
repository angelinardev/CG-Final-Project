#include "PixellationEffect.h"
#include "Utils/ResourceManager/ResourceManager.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"

PixellationEffect::PixellationEffect() :
	PostProcessingLayer::Effect(),
	_shader(nullptr),
	_pixelSize(512)
{
	Name = "Pixellation";
	_format = RenderTargetType::ColorRgb8;

	_shader = ResourceManager::CreateAsset<ShaderProgram>(std::unordered_map<ShaderPartType, std::string>{
		{ ShaderPartType::Vertex, "shaders/vertex_shaders/fullscreen_quad.glsl" },
		{ ShaderPartType::Fragment, "shaders/fragment_shaders/post_effects/Pixellation.glsl" }
	}); 
}


PixellationEffect::~PixellationEffect() = default;

void PixellationEffect::Apply(const Framebuffer::Sptr& gBuffer)
{
	_shader->Bind();
	_shader->SetUniform("u_PixelNumber", _pixelSize);

	gBuffer->BindAttachment(RenderTargetAttachment::Depth, 1);

	//Can Link Buffers if we want :o
	//gBuffer->BindAttachment(RenderTargetAttachment::Color1, 2); // The normal buffer
}

void PixellationEffect::RenderImGui()
{
	LABEL_LEFT(ImGui::SliderFloat,  "Pixel Size", &_pixelSize, 512.f, 4000.f);

}

PixellationEffect::Sptr PixellationEffect::FromJson(const nlohmann::json& data)
{
	PixellationEffect::Sptr result = std::make_shared<PixellationEffect>();
	result->Enabled = JsonGet(data, "enabled", true);
	result->_pixelSize = JsonGet(data, "Pixel Size", result->_pixelSize);
	return result; 
}

nlohmann::json PixellationEffect::ToJson() const
{
	return {
		{ "enabled", Enabled },
		{ "Pixel Size", _pixelSize },
	};
}
