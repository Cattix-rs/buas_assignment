#pragma once
#include <filesystem>
#include <memory>
#include <span>
#include <vector>
#include "../surface.h"
#include "physics.hpp"

namespace Atlas
{
	class Sprite
	{
	public:
		Sprite() = default;
		explicit Sprite(const std::filesystem::path& fileName, const Tmpl8::RectI& rect, const BlendMode& blendMode = BlendMode{});
		explicit Sprite(std::shared_ptr<Image> image, const Tmpl8::RectI& rect, const BlendMode& blendMode = BlendMode {}) noexcept; // 
		explicit Sprite(const std::filesystem::path& fileName, const BlendMode& blendMode = BlendMode{});
		explicit Sprite(std::shared_ptr<Image> image, const BlendMode& blendMode = BlendMode{}) noexcept; // 

		const Tmpl8::RectI& GetRect() const noexcept
		{
			return m_Rect;
		}
		std::shared_ptr<Image> GetImage() const noexcept
		{
			return m_Image;
		}
		const Color& GetColor() const noexcept
		{
			return m_Color;
		}
		const BlendMode& GetBlendMode() const noexcept
		{
			return m_BlendMode;
		}
	private:
		std::shared_ptr<Image> m_Image;
		Tmpl8::RectI m_Rect;
		BlendMode m_BlendMode;
	};

	class SpriteSheet
	{
		SpriteSheet() = default;
		SpriteSheet(const std::filesystem::path& filePath, std::span<const Tmpl8::RectI> rects, const BlendMode& blendMode = BlendMode{});
		SpriteSheet(const std::shared_ptr<Image>& image, std::span<const Tmpl8::RectI> rects, const BlendMode& blendMode = BlendMode{});
		//SpriteSheet(const std::shared_ptr<Image>& image, std::optional<int> _spriteWidth, std::optional<int> _spriteHeight, int padding, int margin, const BlendMode& blendMode) {} dont know if its here or in cpp?
		
			
		
	};
}