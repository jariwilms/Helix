#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

#include "Helix/Core/Type.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"

namespace hlx
{
    class OpenGL
    {
    public:
        using Target         = GLenum;
        using Format         = GLenum;
        using InternalFormat = GLenum;
        using Bitfield       = GLbitfield;

        static constexpr GLsizei type_size(GLenum type)
        {
            switch (type)
            {
                case GL_BOOL:		   return sizeof(GLboolean);
                case GL_INT:		   return sizeof(GLint);
                case GL_FLOAT:		   return sizeof(GLfloat);

                case GL_UNSIGNED_INT:  return sizeof(GLuint);
                case GL_UNSIGNED_BYTE: return sizeof(GLbyte);

                default:			   throw std::invalid_argument{ "Invalid type!" };
            }
        }

        static constexpr GLenum buffer_access(VertexContainer::AccessFlag flags)
        {
            GLenum result{};
            const auto f = static_cast<std::underlying_type<VertexContainer::AccessFlag>::type>(flags);

            if (f & 0x1) result |= GL_MAP_READ_BIT;
            if (f & 0x2) result |= GL_MAP_WRITE_BIT;

            return result;
        }

        static constexpr GLenum texture_format(Texture::Format format)
        {
            switch (format)
            {
                case Texture::Format::R:	return GL_RED;
                case Texture::Format::RG:	return GL_RG;
                case Texture::Format::RGB:	return GL_RGB;
                case Texture::Format::RGBA:	return GL_RGBA;

                default:			        throw std::invalid_argument{ "Invalid format!" };
            }
        }
        static constexpr GLenum texture_layout(Texture::Layout layout)         //== InternalFormat
        {
            switch (layout)
            {
                case Texture::Layout::RGB8:   return GL_RGB8;
                case Texture::Layout::RGB16:  return GL_RGB16F;
                case Texture::Layout::RGB32:  return GL_RGB32F;
                                              
                case Texture::Layout::RGBA8:  return GL_RGBA8;
                case Texture::Layout::RGBA16: return GL_RGBA16F;
                case Texture::Layout::RGBA32: return GL_RGBA32F;

                default:                      throw std::invalid_argument{ "Invalid layout!" };
            }
        }
        static constexpr GLenum texture_wrapping(Texture::Wrapping wrapping)
        {
            switch (wrapping)
            {
                case Texture::Wrapping::ClampToEdge:		 return GL_CLAMP_TO_EDGE;
                case Texture::Wrapping::ClampToBorder:		 return GL_CLAMP_TO_BORDER;
                                                             
                case Texture::Wrapping::MirroredRepeat:		 return GL_MIRRORED_REPEAT;
                case Texture::Wrapping::Repeat:              return GL_REPEAT;
                case Texture::Wrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
                                                             
                default:									 throw std::invalid_argument{ "Invalid wrapping!" };
            }
        }
        static constexpr GLenum texture_filter(Texture::Filter filter)
        {
            switch (filter)
            {
                case Texture::Filter::Nearest:              return GL_NEAREST;
                case Texture::Filter::Linear:               return GL_LINEAR;

                case Texture::Filter::NearestMipmapNearest:	return GL_NEAREST_MIPMAP_NEAREST;
                case Texture::Filter::LinearMipmapNearest:  return GL_LINEAR_MIPMAP_NEAREST;
                                                            
                case Texture::Filter::NearestMipmapLinear:  return GL_NEAREST_MIPMAP_LINEAR;
                case Texture::Filter::LinearMipmapLinear:   return GL_NEAREST_MIPMAP_LINEAR;

                default:                                    throw std::invalid_argument{ "Invalid filter!" };
            }
        }

        static constexpr GLenum renderbuffer_type(RenderBuffer::Type type)
        {
            switch (type)
            {
                case RenderBuffer::Type::Color:		   return GL_COLOR_ATTACHMENT0;
                case RenderBuffer::Type::Depth:		   return GL_DEPTH_ATTACHMENT;
                case RenderBuffer::Type::Stencil:	   return GL_STENCIL_ATTACHMENT;
                case RenderBuffer::Type::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;

                default:                               throw std::invalid_argument{ "Invalid type!" };
            }
        }
        static constexpr GLenum renderbuffer_layout(RenderBuffer::Layout layout)
        {
            switch (layout)
            {
                case RenderBuffer::Layout::Depth16:         return GL_DEPTH_COMPONENT16;
                case RenderBuffer::Layout::Depth24:			return GL_DEPTH_COMPONENT24;
                case RenderBuffer::Layout::Depth32:			return GL_DEPTH_COMPONENT32;
                case RenderBuffer::Layout::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
                case RenderBuffer::Layout::Depth32Stencil8:	return GL_DEPTH32F_STENCIL8;
                case RenderBuffer::Layout::Stencil8:		return GL_STENCIL;

                default:                                    throw std::invalid_argument{ "Invalid layout!" };
            }
        }

        static constexpr GLenum framebuffer_target(FrameBuffer::Target target)
        {
            switch (target)
            {
                case FrameBuffer::Target::Default: return GL_FRAMEBUFFER;
                case FrameBuffer::Target::Read:	   return GL_READ_FRAMEBUFFER;
                case FrameBuffer::Target::Write:   return GL_DRAW_FRAMEBUFFER;

                default:                           throw std::invalid_argument{ "Invalid target!" };
            }
        }

        static constexpr GLenum shader_type(Shader::Type type)
        {
            switch (type)
            {
                case Shader::Type::Vertex:                 return GL_VERTEX_SHADER;
                case Shader::Type::TessellationControl:    return GL_TESS_CONTROL_SHADER;
                case Shader::Type::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
                case Shader::Type::Geometry:               return GL_GEOMETRY_SHADER;
                case Shader::Type::Fragment:			   return GL_FRAGMENT_SHADER;
                case Shader::Type::Compute:				   return GL_COMPUTE_SHADER;

                default:                                   throw std::invalid_argument{ "Invalid type!" };
            }
        }
        static constexpr GLenum shader_stage(Shader::Type type)
        {
            switch (type)
            {
                case Shader::Type::Vertex:                 return GL_VERTEX_SHADER_BIT;
                case Shader::Type::TessellationControl:    return GL_TESS_CONTROL_SHADER_BIT;
                case Shader::Type::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER_BIT;
                case Shader::Type::Geometry:			   return GL_GEOMETRY_SHADER_BIT;
                case Shader::Type::Fragment:			   return GL_FRAGMENT_SHADER_BIT;
                case Shader::Type::Compute:				   return GL_COMPUTE_SHADER_BIT;

                default:                                   throw std::invalid_argument{ "Invalid type!" };
            }
        }
        static constexpr GLint  shader_parameter(GLuint shader, GLenum parameter)
        {
            GLint result{};
            glGetShaderiv(shader, parameter, &result);

            return result;
        }
        static constexpr GLint  program_parameter(GLuint program, GLenum parameter)
        {
            GLint result{};
            glGetProgramiv(program, parameter, &result);

            return result;
        }
    };
}
