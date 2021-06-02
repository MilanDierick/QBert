// Author: Milan Dierick
// Created: 04/03/2021 10:58 PM
// Solution: HeirloomEngine

#pragma once
#include "OrthographicCamera.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "VertexArray.h"

namespace Heirloom
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads    = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices  = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		static const uint32_t MaxTextureSlots = 32;

		uint32_t QuadIndexCount           = 0;
		QuadVertex* pQuadVertexBufferBase = nullptr;
		QuadVertex* pQuadVertexBuffer     = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture
	};

	static Renderer2DData s_Data;

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position,
							 const glm::vec2& size,
							 const Ref<Texture2D>& texture,
							 float tilingFactor         = 1.0f,
							 const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position,
							 const glm::vec2& size,
							 const Ref<Texture2D>& texture,
							 float tilingFactor         = 1.0f,
							 const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(Ref<Sprite> sprite);

		static void DrawRotatedQuad(const glm::vec2& position,
									const glm::vec2& size,
									float rotation,
									const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position,
									const glm::vec2& size,
									float rotation,
									const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position,
									const glm::vec2& size,
									float rotation,
									const Ref<Texture2D>& texture,
									float tilingFactor         = 1.0f,
									const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position,
									const glm::vec2& size,
									float rotation,
									const Ref<Texture2D>& texture,
									float tilingFactor         = 1.0f,
									const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(Sprite& sprite);

	private:
		static void ConfigureAndIncrementQuadVertexBufferPtr(const glm::vec3& position,
															 const glm::vec4& color,
															 const glm::vec2& texCoord,
															 float texIndex,
															 float tilingFactor);
	};
}
