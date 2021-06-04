#include "hlpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

// =================================================================================================================
// ==== VertexBuffer ===============================================================================================
// =================================================================================================================

Heirloom::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, const uint32_t size)
{
	HL_PROFILE_FUNCTION()

	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Heirloom::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	HL_PROFILE_FUNCTION()

	glDeleteBuffers(1, &m_RendererID);
}

void Heirloom::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Heirloom::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// =================================================================================================================
// ==== IndexBuffer ================================================================================================
// =================================================================================================================

Heirloom::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, const uint32_t count)
	: m_Count(count)
{
	HL_PROFILE_FUNCTION()

	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Heirloom::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	HL_PROFILE_FUNCTION()

	glDeleteBuffers(1, &m_RendererID);
}

void Heirloom::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Heirloom::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}