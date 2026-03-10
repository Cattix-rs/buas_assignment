#include <Level.hpp>

namespace Tmpl8
{
	
	void Level::Init()
	{
		 
		colliders.push_back({
			{
				vec2f(0.0f, 400.0f), vec2f(400.0f, 432.0f)
			},
			ColliderType::Solid
			});

		colliders.push_back({
			{
				vec2f(200.0f, 300.0f), vec2f(400.0f, 320.0f)
			},
			ColliderType::OneWay
			});

		
	}
}
