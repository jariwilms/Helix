#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "stb/stb_image.h"

#include "API/OpenGL/OpenGL.hpp"
#include "Helix/Format/Image.hpp"

namespace hlx
{
	struct Texture
	{
		enum
		{
			TEXTURE_WRAP_S, 
			TEXTURE_WRAP_T, 
			TEXTURE_MIN_FILTER, 
			TEXTURE_MAG_FILTER
		};

		Texture(const std::filesystem::path& path);
		~Texture();

		void bind() const;
		void unbind() const;

		const Image& getImage() const;

		bool verify() const;

	private:
		unsigned int m_textureId;
		std::shared_ptr<Image> m_texture;

		GLint m_internalFormat;
		GLenum m_dataFormat;

		bool m_status;
	};
}
