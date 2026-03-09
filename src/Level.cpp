#include <Level.hpp>

namespace Tmpl8
{
	
	void Level::Init()
	{
		for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			tiles[y][x] = 0;
		}

		for (int x = 0; x < width; x++)
		{
			tiles[20][x] = 1;
		}
	}

	bool Level::IsSolid(int x, int y) const
	{
		if (x < 0 || y < 0 || x >= width || y >= height)
			return false;

		return tiles[y][x] == 1;
	}
}
