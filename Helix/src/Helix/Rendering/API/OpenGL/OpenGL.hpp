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
				case TextureType::Texture1D:							return GL_TEXTURE_1D;
				case TextureType::Texture2D:							return GL_TEXTURE_2D;
				case TextureType::Texture3D:							return GL_TEXTURE_3D;

				case TextureType::Texture1DArray:						return GL_TEXTURE_1D_ARRAY;
				case TextureType::Texture2DArray:						return GL_TEXTURE_2D_ARRAY;

				case TextureType::Texture2DMultisample:					return GL_TEXTURE_2D_MULTISAMPLE;
				case TextureType::Texture2DMultisampleArray:			return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;

				case TextureType::TextureCubeMap:						return GL_TEXTURE_CUBE_MAP;
				case TextureType::TextureCubeMapArray:					return GL_TEXTURE_CUBE_MAP_ARRAY;

				case TextureType::TextureBuffer:						return GL_TEXTURE_BUFFER;

				default:												HLX_CORE_ASSERT(false, "Invalid Texture Type: {0}", static_cast<int>(type)); return -1;
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
				case TextureWrap::ClampToEdge:					return GL_CLAMP_TO_EDGE;
				case TextureWrap::ClampToBorder:				return GL_CLAMP_TO_BORDER;

				case TextureWrap::MirroredRepeat:				return GL_MIRRORED_REPEAT;
				case TextureWrap::Repeat:						return GL_REPEAT;
				case TextureWrap::MirroredClampToEdge:			return GL_MIRROR_CLAMP_TO_EDGE;
					
				default:										HLX_CORE_ASSERT(false, "Invalid Texture Wrap: {0}", static_cast<int>(wrap)); return -1;
			}
		}
		static constexpr int getTextureFilter(TextureFilter filter)
		{
			switch (filter)
			{
				case TextureFilter::Nearest:						return GL_NEAREST;
				case TextureFilter::Linear:							return GL_LINEAR;

				case TextureFilter::NearestMipmapNearest:			return GL_NEAREST_MIPMAP_NEAREST;
				case TextureFilter::LinearMipmapNearest:			return GL_LINEAR_MIPMAP_NEAREST;

				case TextureFilter::NearestMipmapLinear:			return GL_NEAREST_MIPMAP_LINEAR;
				case TextureFilter::LinearMipmapLinear:				return GL_NEAREST_MIPMAP_LINEAR;

				default:											HLX_CORE_ASSERT(false, "Invalid Texture Filter: {0}", static_cast<int>(filter)); return -1;
			}
		}

		static constexpr int getRenderBufferAttachment(RenderBufferAttachment attachment)
		{
			switch (attachment)
			{
				case RenderBufferAttachment::Color:					return GL_COLOR_ATTACHMENT0;
				case RenderBufferAttachment::Depth:					return GL_DEPTH_ATTACHMENT;
				case RenderBufferAttachment::Stencil:				return GL_STENCIL_ATTACHMENT;
				case RenderBufferAttachment::DepthStencil:			return GL_DEPTH_STENCIL_ATTACHMENT;

				default:											HLX_CORE_ASSERT(false, "Invalid Render Buffer attachment: {0}", static_cast<int>(attachment)); return -1;
			}
		}
		static constexpr int getRenderBufferLayout(RenderBufferLayout layout)
		{
			switch (layout)
			{
				case RenderBufferLayout::Depth16:					return GL_DEPTH_COMPONENT16;
				case RenderBufferLayout::Depth24:					return GL_DEPTH_COMPONENT24;
				case RenderBufferLayout::Depth32:					return GL_DEPTH_COMPONENT32F;
							
				case RenderBufferLayout::Depth24Stencil8:			return GL_DEPTH24_STENCIL8;
				case RenderBufferLayout::Depth32Stencil8:			return GL_DEPTH32F_STENCIL8;
					
				case RenderBufferLayout::Stencil8:					return GL_STENCIL_INDEX8;

				default:											HLX_CORE_ASSERT(false, "Invalid Render Buffer layout: {0}", static_cast<int>(layout)); return -1;
			}
		}
	};
}
