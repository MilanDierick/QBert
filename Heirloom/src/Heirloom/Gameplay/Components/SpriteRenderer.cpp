#include "hlpch.h"
#include "SpriteRenderer.h"

// #include "Heirloom/Renderer/Renderer.h"

Heirloom::SpriteRenderer::SpriteRenderer()
{
	// TODO: This ID should be unique and gotten from some static class that distributes ID's
}

void Heirloom::SpriteRenderer::Update(Timestep)
{
}

void Heirloom::SpriteRenderer::Render() const
{
	// m_Texture->Bind();
	// Heirloom::Renderer::Submit(m_Texture);
}

void Heirloom::SpriteRenderer::LoadTextureFromPath(const std::string/* path*/)
{
	// m_Texture = Texture2D::Create(path);
}
