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
	Renderer2D::DrawQuad(m_Sprite);
}
