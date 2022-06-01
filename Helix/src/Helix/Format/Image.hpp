#pragma once

namespace hlx
{
	struct Image
	{
		Image() = default;
		~Image() { delete data; }

		int width;
		int height;
		int channels;

		unsigned char* data;
	};
}
