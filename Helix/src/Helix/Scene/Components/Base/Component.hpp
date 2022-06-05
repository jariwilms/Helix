#pragma once

#include "stdafx.hpp"

namespace hlx
{
	class Component
	{
	public:
		enum class Type
		{
			None, 

			Transform
		};

		virtual ~Component() = default;

		virtual void update() {};
		virtual void render() {};

#ifdef HLX_DEBUG
		virtual const std::string getName() const = 0;
		virtual const std::string toString() const = 0;
#endif
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

#else
#define COMPONENT_TYPE(componentType)																		\
		static Component::Type getStaticType() { return componentType; }									\
		Component::Type getEventType() const override { return getStaticType(); }							\

#define EVENT_DEBUG(debugOutput)																			\

#endif // HLX_DEBUG
