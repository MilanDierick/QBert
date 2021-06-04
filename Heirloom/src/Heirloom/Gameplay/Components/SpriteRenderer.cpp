#include "hlpch.h"
#include "SpriteRenderer.h"

#include "Heirloom/Gameplay/GameObject.h"
#include "Heirloom/Renderer/Renderer2D.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Heirloom::SpriteRenderer::SpriteRenderer()
	: m_SpriteOffset(0.0f), m_Parent(nullptr)
{
}

Heirloom::SpriteRenderer::~SpriteRenderer()
{
	HL_TRACE("SpriteRenderer destroyed");
}

void Heirloom::SpriteRenderer::Update(Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	m_Sprite->Position = m_Parent->GetTransform()->GetPosition();
}

void Heirloom::SpriteRenderer::Render()
{
	// TODO: Add a SpritePositionOffset to Sprite itself and move this to the renderer
	const glm::vec3 oldSpritePosition       = m_Sprite->Position;
	const glm::vec3 temporarySpritePosition = oldSpritePosition + m_SpriteOffset;
	
	m_Sprite->Position = temporarySpritePosition;
	
	Renderer2D::DrawQuad(m_Sprite);

	m_Sprite->Position = oldSpritePosition;
}
