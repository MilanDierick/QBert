#include "hlpch.h"
#include "Renderer2D.h"
#include "RenderCommand.h"

void Heirloom::Renderer2D::Init()
{
	HL_PROFILE_FUNCTION()

	s_Data = new Renderer2DStorage();

	s_Data->QuadVertexArray = VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f,
		-0.5f,
		0.0f,
		0.0f,
		0.0f,
		0.5f,
		-0.5f,
		0.0f,
		1.0f,
		0.0f,
		0.5f,
		0.5f,
		0.0f,
		1.0f,
		1.0f,
		-0.5f,
		0.5f,
		0.0f,
		0.0f,
		1.0f
	};

	Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof squareVertices);
	squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float2, "a_TexCoord"}});
	s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6]       = {0, 1, 2, 2, 3, 0};
	const Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof squareIndices / sizeof(uint32_t));
	s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

	s_Data->WhiteTexture      = Texture2D::Create(1, 1);
	uint32_t whiteTextureData = 0xffffffff;
	s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof whiteTextureData);

	s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
	s_Data->TextureShader->Bind();
	s_Data->TextureShader->SetInt("u_Texture", 0);
}

void Heirloom::Renderer2D::Shutdown()
{
	HL_PROFILE_FUNCTION()

	delete s_Data;
}

void Heirloom::Renderer2D::BeginScene(OrthographicCamera& camera)
{
	HL_PROFILE_FUNCTION()

	s_Data->TextureShader->Bind();
	s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
}

void Heirloom::Renderer2D::EndScene()
{
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({position.x, position.y, 0.0f}, size, color);
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	HL_PROFILE_FUNCTION()

	s_Data->TextureShader->SetFloat4("u_Color", color);
	s_Data->TextureShader->SetFloat("u_TexTilingFactor", 1.0f);

	s_Data->WhiteTexture->Bind();

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) * /* rotation * */ scale(glm::mat4(1.0f),
		{size.x, size.y, 1.0f});

	s_Data->TextureShader->SetMat4("u_Transform", transform);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec2& position,
									const glm::vec2& size,
									const Ref<Texture2D>& texture,
									const float tilingFactor,
									const glm::vec4& tintColor)
{
	DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
}

void Heirloom::Renderer2D::DrawQuad(const glm::vec3& position,
									const glm::vec2& size,
									const Ref<Texture2D>& texture,
									const float tilingFactor,
									const glm::vec4& tintColor)
{
	HL_PROFILE_FUNCTION()

	s_Data->TextureShader->SetFloat4("u_Color", tintColor);
	s_Data->TextureShader->SetFloat("u_TexTilingFactor", tilingFactor);

	texture->Bind();

	const float aspectRatio = static_cast<float>(texture->GetWidth()) / static_cast<float>(texture->GetHeight());

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) * /* rotation * */ scale(glm::mat4(1.0f),
		{size.x, size.y / aspectRatio, 1.0f});

	s_Data->TextureShader->SetMat4("u_Transform", transform);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

void Heirloom::Renderer2D::DrawQuad(const Ref<Sprite> sprite)
{
	DrawQuad(sprite->Position, sprite->Size, sprite->Texture, sprite->TilingFactor, sprite->TintColor);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec2& position,
										   const glm::vec2& size,
										   const float rotation,
										   const glm::vec4& color)
{
	DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec3& position,
										   const glm::vec2& size,
										   const float rotation,
										   const glm::vec4& color)
{
	HL_PROFILE_FUNCTION()

	s_Data->TextureShader->SetFloat4("u_Color", color);
	s_Data->TextureShader->SetFloat("u_TexTilingFactor", 1.0f);

	s_Data->WhiteTexture->Bind();

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) * rotate(
		glm::mat4(1.0f),
		rotation,
		{0.0f, 0.0f, 1.0f}) * scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

	s_Data->TextureShader->SetMat4("u_Transform", transform);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec2& position,
										   const glm::vec2& size,
										   const float rotation,
										   const Ref<Texture2D>& texture,
										   const float tilingFactor,
										   const glm::vec4& tintColor)
{
	DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
}

void Heirloom::Renderer2D::DrawRotatedQuad(const glm::vec3& position,
										   const glm::vec2& size,
										   const float rotation,
										   const Ref<Texture2D>& texture,
										   const float tilingFactor,
										   const glm::vec4& tintColor)
{
	HL_PROFILE_FUNCTION()

	s_Data->TextureShader->SetFloat4("u_Color", tintColor);
	s_Data->TextureShader->SetFloat("u_TexTilingFactor", tilingFactor);

	texture->Bind();

	const float aspectRatio = static_cast<float>(texture->GetWidth()) / static_cast<float>(texture->GetHeight());

	const glm::mat4 transform = translate(glm::mat4(1.0f), position) *
		rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * scale(glm::mat4(1.0f),
																	  {size.x, size.y / aspectRatio, 1.0f});

	s_Data->TextureShader->SetMat4("u_Transform", transform);

	s_Data->QuadVertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
}

void Heirloom::Renderer2D::DrawRotatedQuad(Sprite& sprite)
{
	DrawRotatedQuad(sprite.Position,
					sprite.Size,
					sprite.Rotation,
					sprite.Texture,
					sprite.TilingFactor,
					sprite.TintColor);
}
