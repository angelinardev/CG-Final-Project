#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Textures/Texture3D.h"

class ChromaticAberrationEffect : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(ChromaticAberrationEffect);

	ChromaticAberrationEffect(bool enabled);

	ChromaticAberrationEffect();
	virtual ~ChromaticAberrationEffect();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;
	virtual void RenderImGui() override;

	// Inherited from IResource

	ChromaticAberrationEffect::Sptr FromJson(const nlohmann::json& data);
	virtual nlohmann::json ToJson() const override;

protected:
	ShaderProgram::Sptr _shader;
	float _strength;
};

