#include "stdafx.hpp"
#include "OpenGLTexture.hpp"

#include "Helix/Rendering/API/OpenGL/OpenGL.hpp"

namespace hlx
{
	OpenGLTexture::OpenGLTexture(TextureBlueprint blueprint, unsigned char* data)
	{
		glGenTextures(1, &m_id);

		
		
		m_type = blueprint.type;
		m_layout = blueprint.layout;
		m_dimensions = blueprint.dimensions;
		m_channels = blueprint.channels;
		m_mipmapLevels = blueprint.mipmapLevels;

		

		m_target = OpenGL::getTextureTarget(m_type);
		m_internalFormat = OpenGL::getTextureLayout(m_layout);
		m_format = OpenGL::getTextureBaseLayout(m_channels);



		bind();
		allocate();

		if (data)
		{
			setSubData(data);

			glGenerateMipmap(m_target);
			glTexParameteri(m_target, GL_TEXTURE_WRAP_S, OpenGL::getTextureWrap(blueprint.wrapS));
			glTexParameteri(m_target, GL_TEXTURE_WRAP_T, OpenGL::getTextureWrap(blueprint.wrapT));
		}
		
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, OpenGL::getTextureFilter(blueprint.minFilter));
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, OpenGL::getTextureFilter(blueprint.magFilter));
		
		unbind();
	}
	OpenGLTexture::~OpenGLTexture()
	{
		if (isBound()) unbind();
		
		glDeleteTextures(1, &m_id);
	}

	void OpenGLTexture::bind() const
	{
		if (isBound()) return;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(m_target, m_id);
	}
	void OpenGLTexture::bindUnit(unsigned int index) const
	{
		glBindTextureUnit(index, m_id);
	}
	void OpenGLTexture::unbind() const 
	{ 
		glBindTexture(m_target, 0);
	}
	bool OpenGLTexture::isBound() const
	{
		return false;
	}

	void OpenGLTexture::allocate()
	{
		switch (m_type)
		{
			case TextureType::Texture1D: glTextureStorage1D(m_id, m_mipmapLevels, m_internalFormat, m_dimensions.x);														return;
			case TextureType::Texture2D: glTextureStorage2D(m_id, m_mipmapLevels, m_internalFormat, m_dimensions.x, m_dimensions.y);										return;
			case TextureType::Texture3D: glTextureStorage3D(m_id, m_mipmapLevels, m_internalFormat, m_dimensions.x, m_dimensions.y, m_dimensions.z);						return;
				
			default:					 HLX_CORE_ASSERT(false, "Texture Type not supported");
		}
	}
	void OpenGLTexture::setSubData(unsigned char* data)
	{
		switch (m_type)
		{
			case TextureType::Texture1D: glTextureSubImage1D(m_id, 0, 0, 0, m_format, GL_UNSIGNED_BYTE, data);																return;
			case TextureType::Texture2D: glTextureSubImage2D(m_id, 0, 0, 0, m_dimensions.x, m_dimensions.y, m_format, GL_UNSIGNED_BYTE, data);								return;
			case TextureType::Texture3D: glTextureSubImage3D(m_id, 0, 0, 0, 0, m_dimensions.x, m_dimensions.y, m_dimensions.z, m_format, GL_UNSIGNED_BYTE, data);			return;
				
			default:					 HLX_CORE_ASSERT(false, "Texture Type not supported");
		}
	}
}
