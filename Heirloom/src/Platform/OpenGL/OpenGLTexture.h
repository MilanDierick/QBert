// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include "OpenGLShader.h"

#include "Heirloom/Renderer/Texture.h"

namespace Heirloom
{
	class OpenGLTexture2D final : public Texture2D
	{
	public:
		explicit OpenGLTexture2D(uint32_t width, uint32_t height);
		explicit OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		OpenGLTexture2D(const OpenGLTexture2D& other)                = delete;
		OpenGLTexture2D(OpenGLTexture2D&& other) noexcept            = delete;
		OpenGLTexture2D& operator=(const OpenGLTexture2D& other)     = delete;
		OpenGLTexture2D& operator=(OpenGLTexture2D&& other) noexcept = delete;

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) override;

		bool operator==(const Texture& other) const override;

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
