#pragma once
#include "Application/Layers/PostProcessingLayer.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Textures/Texture1D.h"

class PixellationEffect : public PostProcessingLayer::Effect {
public:
	MAKE_PTRS(PixellationEffect);

	PixellationEffect();
	virtual ~PixellationEffect();

	virtual void Apply(const Framebuffer::Sptr& gBuffer) override;
	virtual void RenderImGui() override;



	// Inherited from IResource

	PixellationEffect::Sptr FromJson(const nlohmann::json& data);
	virtual nlohmann::json ToJson() const override;

protected:
	ShaderProgram::Sptr _shader;
	float _pixelSize;


};


