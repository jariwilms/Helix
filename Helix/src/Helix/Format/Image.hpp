#pragma once

#include "stb/stb_image.h"

namespace hlx
{
	struct Image
	{
		Image() = default;
		~Image() { stbi_image_free(data); }

		int width;
		int height;
		int channels;

		unsigned char* data;
	};
}
