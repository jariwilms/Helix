#pragma once

#include "Helix/Core/Core.hpp"

namespace hlx
{
	enum class TextureFilter;
	using TextureMinFilter = TextureFilter;
	using TextureMagFilter = TextureFilter;
	
	enum class TextureType
	{
		TEXTURE_1D, 
		TEXTURE_2D, 
		TEXTURE_3D, 

		TEXTURE_1D_ARRAY, 
		TEXTURE_2D_ARRAY, 

		TEXTURE_2D_MULTISAMPLE, 
		TEXTURE_2D_MULTISAMPLE_ARRAY, 

		TEXTURE_CUBE_MAP, 
		TEXTURE_CUBE_MAP_ARRAY, 

		TEXTURE_BUFFER, 
	};
	enum class TextureLayout
	{
		RGB8, 
		RGB16, 
		RGB32, 

		RGBA8, 
		RGBA16, 
		RGBA32, 
	};
	enum class TextureWrap
	{
		CLAMP_TO_EDGE, 
		CLAMP_TO_BORDER, 
		
		MIRRORED_REPEAT, 
		REPEAT, 
		MIRROR_CLAMP_TO_EDGE, 
	};
	enum class TextureFilter
	{
		NEAREST, 
		LINEAR, 
		
		NEAREST_MIPMAP_NEAREST, 
		LINEAR_MIPMAP_NEAREST, 
		
		NEAREST_MIPMAP_LINEAR, 
		LINEAR_MIPMAP_LINEAR, 
	};
	
	enum class RenderBufferAttachment
	{
		COLOR,  
		DEPTH,  
		STENCIL,  
		
		DEPTH_STENCIL,  
	};
	enum class RenderBufferLayout
	{
		DEPTH16, 
		DEPTH24, 
		DEPTH32, 
		
		DEPTH24_STENCIL8, 
		DEPTH32_STENCIL8, 
		
		STENCIL8, 
	};
}
