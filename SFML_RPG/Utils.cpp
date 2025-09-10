#include "stdafx.h"
#include "Utils.h"

namespace Utils {
    const GraphicsSettings* gfxSettings = nullptr;

	const unsigned calcCharSize(float size)
	{
		if (!gfxSettings)
			throw std::runtime_error("GraphicsSettings not initialized in Utils");

		if (size < 0.1f)
			size = 0.1f;
		else if (size > 5)
			size = 5;

		return static_cast<unsigned>((gfxSettings->resolution.size.x + gfxSettings->resolution.size.y) * size / 120);

	}
}