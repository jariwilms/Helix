#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Entity;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void update() {};
		virtual void render() {};

		virtual Entity& getParent()
		{
			return *m_parent;
		}
		virtual void setParent(Entity* parent)
		{
			m_parent = parent;
		}

#ifdef HLX_DEBUG
		virtual const std::string getName() const = 0;
		virtual const std::string toString() const = 0;
#endif
	protected:
		Component(Entity* parent)
		{
			setParent(parent);
		}

	private:
		Entity* m_parent;
	};
}

#ifdef HLX_DEBUG
#define COMPONENT_NAME(componentName)																		\
		virtual const std::string getName() const override { return std::string{ #componentName }; }		\

#define COMPONENT_DEBUG(debugOutput)																		\
	const std::string toString() const override																\
	{																										\
		std::stringstream ss;																				\
		ss << debugOutput;																					\
		return ss.str();																					\
	}																										\

#endif // HLX_DEBUG
