#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Format/Format.hpp"

namespace hlx
{
	class OpenGL
	{
	public:
		static constexpr int getSizeOfType(GLenum type)
		{
			switch (type)
			{
				case GL_BOOL:					return sizeof(GLboolean);
				case GL_INT:					return sizeof(GLint);
				case GL_FLOAT:					return sizeof(GLfloat);

				case GL_UNSIGNED_INT:			return sizeof(GLuint);
				case GL_UNSIGNED_BYTE:			return sizeof(GLbyte);

				default:						HLX_CORE_ASSERT(false, "Invalid OpenGL type: {0}", static_cast<int>(type)); return -1;
			}
		}

		static constexpr int getTextureTarget(TextureType type)
		{
			switch (type)
			{
				case TextureType::TEXTURE_1D:								return GL_TEXTURE_1D;
				case TextureType::TEXTURE_2D:								return GL_TEXTURE_2D;
				case TextureType::TEXTURE_3D:								return GL_TEXTURE_3D;

				case TextureType::TEXTURE_1D_ARRAY:							return GL_TEXTURE_1D_ARRAY;
				case TextureType::TEXTURE_2D_ARRAY:							return GL_TEXTURE_2D_ARRAY;

				case TextureType::TEXTURE_2D_MULTISAMPLE:					return GL_TEXTURE_2D_MULTISAMPLE;
				case TextureType::TEXTURE_2D_MULTISAMPLE_ARRAY:				return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;

				case TextureType::TEXTURE_CUBE_MAP:							return GL_TEXTURE_CUBE_MAP;
				case TextureType::TEXTURE_CUBE_MAP_ARRAY:					return GL_TEXTURE_CUBE_MAP_ARRAY;

				case TextureType::TEXTURE_BUFFER:							return GL_TEXTURE_BUFFER;

				default:													HLX_CORE_ASSERT(false, "Invalid Texture Type: {0}", static_cast<int>(type)); return -1;
			}
		}
		static constexpr int getTextureLayout(TextureLayout layout)
		{
			switch (layout)
			{
				case TextureLayout::RGB8:				return GL_RGB8;
				case TextureLayout::RGB16:				return GL_RGB16;
				case TextureLayout::RGB32:				return GL_RGB32F;
					
				case TextureLayout::RGBA8:				return GL_RGBA8;
				case TextureLayout::RGBA16:				return GL_RGBA16;
				case TextureLayout::RGBA32:				return GL_RGBA32F;

				default:								HLX_CORE_ASSERT(false, "Invalid Texture Layout: {0}", static_cast<int>(layout)); return -1;
			}
		}
		static constexpr int getTextureBaseLayout(int channels)
		{
			switch (channels)
			{
				case 1:				return GL_RED;
				case 2:				return GL_RG;
				case 3:				return GL_RGB;
				case 4:				return GL_RGBA;
					
				default:			HLX_CORE_ASSERT(false, "Invalid number of channels: {0}", channels); return -1;
			}
		}
		static constexpr int getTextureWrap(TextureWrap wrap)
		{
			switch (wrap)
			{
				case TextureWrap::CLAMP_TO_EDGE:					return GL_CLAMP_TO_EDGE;
				case TextureWrap::CLAMP_TO_BORDER:					return GL_CLAMP_TO_BORDER;
				case TextureWrap::MIRRORED_REPEAT:					return GL_MIRRORED_REPEAT;
				case TextureWrap::REPEAT:							return GL_REPEAT;
				case TextureWrap::MIRROR_CLAMP_TO_EDGE:				return GL_MIRROR_CLAMP_TO_EDGE;
					
				default:											HLX_CORE_ASSERT(false, "Invalid Texture Wrap: {0}", static_cast<int>(wrap)); return -1;
			}
		}
		static constexpr int getTextureFilter(TextureFilter filter)
		{
			switch (filter)
			{
				case TextureFilter::NEAREST:							return GL_NEAREST;
				case TextureFilter::LINEAR:								return GL_LINEAR;
				case TextureFilter::NEAREST_MIPMAP_NEAREST:				return GL_NEAREST_MIPMAP_NEAREST;
				case TextureFilter::LINEAR_MIPMAP_NEAREST:				return GL_LINEAR_MIPMAP_NEAREST;
				case TextureFilter::NEAREST_MIPMAP_LINEAR:				return GL_NEAREST_MIPMAP_LINEAR;
				case TextureFilter::LINEAR_MIPMAP_LINEAR:				return GL_NEAREST_MIPMAP_LINEAR;

				default:												HLX_CORE_ASSERT(false, "Invalid Texture Filter: {0}", static_cast<int>(filter)); return -1;
			}
		}

		static constexpr int getRenderBufferAttachment(RenderBufferAttachment attachment)
		{
			switch (attachment)
			{
				case RenderBufferAttachment::COLOR:						return GL_COLOR_ATTACHMENT0;
				case RenderBufferAttachment::DEPTH:						return GL_DEPTH_ATTACHMENT;
				case RenderBufferAttachment::STENCIL:					return GL_STENCIL_ATTACHMENT;
				case RenderBufferAttachment::DEPTH_STENCIL:				return GL_DEPTH_STENCIL_ATTACHMENT;

				default:												HLX_CORE_ASSERT(false, "Invalid Render Buffer attachment: {0}", static_cast<int>(attachment)); return -1;
			}
		}
		static constexpr int getRenderBufferLayout(RenderBufferLayout layout)
		{
			switch (layout)
			{
				case RenderBufferLayout::DEPTH16:					return GL_DEPTH_COMPONENT16;
				case RenderBufferLayout::DEPTH24:					return GL_DEPTH_COMPONENT24;
				case RenderBufferLayout::DEPTH32:					return GL_DEPTH_COMPONENT32F;
							
				case RenderBufferLayout::DEPTH24_STENCIL8:			return GL_DEPTH24_STENCIL8;
				case RenderBufferLayout::DEPTH32_STENCIL8:			return GL_DEPTH32F_STENCIL8;
					
				case RenderBufferLayout::STENCIL8:					return GL_STENCIL_INDEX8;

				default:											HLX_CORE_ASSERT(false, "Invalid Render Buffer layout: {0}", static_cast<int>(layout)); return -1;
			}
		}
	};
}
