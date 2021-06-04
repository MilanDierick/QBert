#include "hlpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

void Heirloom::BufferLayout::CalculateOffsetsAndStride()
{
	HL_PROFILE_FUNCTION()

	uint32_t offset = 0;
	m_Stride        = 0;

	for (auto& element : m_Elements)
	{
		element.Offset = offset;
		offset += element.Size;
		m_Stride += element.Size;
	}
}

Heirloom::Ref<Heirloom::VertexBuffer> Heirloom::VertexBuffer::Create(float* vertices, const uint32_t size)
{
	HL_PROFILE_FUNCTION()

	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Heirloom::Ref<Heirloom::IndexBuffer> Heirloom::IndexBuffer::Create(uint32_t* indices, const uint32_t size)
{
	HL_PROFILE_FUNCTION()

	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, size);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
