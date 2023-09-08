#include "stdafx.hpp"

#include "OpenGLPipeline.hpp"

namespace hlx
{
	OpenGLPipeline::OpenGLPipeline()
	{
		glCreateProgramPipelines(1, &m_id);
	}
	OpenGLPipeline::OpenGLPipeline(std::initializer_list<const std::shared_ptr<Shader>> shaders)
	{
		glCreateProgramPipelines(1, &m_id);

		std::for_each(shaders.begin(), shaders.end(), [this](const auto& shader) { stage(shader); });
	}
	OpenGLPipeline::~OpenGLPipeline()
	{
		glDeleteProgramPipelines(1, &m_id);
	}

	void OpenGLPipeline::bind() const
	{
		if (m_id == s_boundPipelineId) return;

		glBindProgramPipeline(m_id);
		s_boundPipelineId = m_id;
	}
	void OpenGLPipeline::unbind() const
	{
		glBindProgramPipeline(0);
	}
	bool OpenGLPipeline::is_bound() const
	{
		return false;
	}

	void OpenGLPipeline::stage(const std::shared_ptr<Shader> shader)
	{
		const auto stage = OpenGL::shader_stage(shader->type());
		glUseProgramStages(m_id, stage, shader->id());

		switch (shader->type())
		{
			case Shader::Type::Vertex:                 m_shaders.at(0) = shader; break;
			case Shader::Type::TessellationControl:    m_shaders.at(1) = shader; break;
			case Shader::Type::TessellationEvaluation: m_shaders.at(2) = shader; break;
			case Shader::Type::Geometry:               m_shaders.at(3) = shader; break;
			case Shader::Type::Fragment:               m_shaders.at(4) = shader; break;

			default:                                   throw std::invalid_argument{ "Invalid shader stage!" };
		}
	}
}
