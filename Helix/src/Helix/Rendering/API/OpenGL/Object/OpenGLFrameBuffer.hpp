#pragma once

#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture.hpp"
#include "Helix/Rendering/API/OpenGL/Object/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/Object/FrameBuffer.hpp"

namespace hlx
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(FrameBufferBlueprint blueprint);
		~OpenGLFrameBuffer();

		void bind(FrameBufferTarget target) const override;
		void unbind() const override;
		bool isBound() const override;

		void bindTextures() const override;

		const std::shared_ptr<Texture> getTexture(const std::string& name) const override;
		const std::vector<std::shared_ptr<Texture>> getTextures() const override;
		const std::vector<std::shared_ptr<RenderBuffer>> getRenderBuffers() const override;

	private:
		void attach();

		int m_target;
		
		std::unordered_map<std::string, std::shared_ptr<OpenGLTexture>> m_textures;
		std::unordered_map<std::string, std::shared_ptr<OpenGLRenderBuffer>> m_renderBuffers;

		std::vector<unsigned int> m_attachments;
	};
}
