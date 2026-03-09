#pragma once

#include "../surface.h"

namespace Tmpl8
{
	class Level
	{
	public:
		void Init();

		void Draw(Surface* screen);

		bool IsSolid(int x, int y) const;

	private:
		static const int width = 32;
		static const int height = 32;

		int tiles[height][width];
	};
}
