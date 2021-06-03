#include "hlpch.h"
#include "SpriteRenderer.h"
#include "Heirloom/Renderer/Renderer2D.h"

Heirloom::SpriteRenderer::SpriteRenderer()
{
}

void Heirloom::SpriteRenderer::Update(Timestep)
{
}

void Heirloom::SpriteRenderer::Render()
{
	const glm::vec3 oldSpritePosition       = m_Sprite->Position;
	const glm::vec3 temporarySpritePosition = oldSpritePosition + glm::vec3{m_SpriteOffset, 0.0f};

	m_Sprite->Position = temporarySpritePosition;
	
	Renderer2D::DrawQuad(m_Sprite);

	m_Sprite->Position = oldSpritePosition;
}
