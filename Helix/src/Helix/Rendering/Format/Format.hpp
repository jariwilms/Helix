#pragma once

#include "Helix/Core/Core.hpp"

namespace hlx
{
	enum class TextureFilter;
	using TextureMinFilter = TextureFilter;
	using TextureMagFilter = TextureFilter;
	
	enum class TextureType
	{
		Texture1D, 
		Texture2D, 
		Texture3D, 
		
		Texture1DArray, 
		Texture2DArray, 

		Texture2DMultisample, 
		Texture2DMultisampleArray, 

		TextureCubeMap, 
		TextureCubeMapArray, 

		TextureBuffer, 
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
		ClampToEdge, 
		ClampToBorder, 
		
		MirroredRepeat, 
		Repeat, 
		MirroredClampToEdge, 
	};
	enum class TextureFilter
	{
		Nearest, 
		Linear, 
		
		NearestMipmapNearest, 
		LinearMipmapNearest, 
		
		NearestMipmapLinear, 
		LinearMipmapLinear, 
	};
	
	enum class RenderBufferAttachment
	{
		Color,  
		Depth,  
		Stencil,  
		
		DepthStencil,  
	};
	enum class RenderBufferLayout
	{
		Depth16, 
		Depth24, 
		Depth32, 
		
		Depth24Stencil8, 
		Depth32Stencil8, 
		
		Stencil8, 
	};
}
