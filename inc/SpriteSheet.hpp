#pragma once
#include <filesystem>
#include <span>

#include "BlendMode.hpp"
#include "Image.hpp"
#include "physics.hpp"

namespace Atlas
{

	class SpriteSheet
	{
		SpriteSheet() = default;
		SpriteSheet(const std::filesystem::path& filePath, std::span<const Tmpl8::RectI> rects, const BlendMode& blendMode = BlendMode{});

		SpriteSheet(const std::shared_ptr<Image>& image, std::span<const Tmpl8::RectI> rects, const BlendMode& blendMode = BlendMode{});

		explicit SpriteSheet(const std::shared_ptr<Image>& image, std::optional<int> _spriteWidth, std::optional<int> _spriteHeight, int padding, int margin, const BlendMode& blendMode = BlendMode{});

		explicit SpriteSheet(const std::filesystem::path& filePath, std::optional<int> spriteWidth = {}, std::optional<int> spriteHeight = {}, int padding = 0, int margin = 0, const BlendMode& blendMode = BlendMode{});

		int GetRows() const noexcept
		{
			return m_Rows;
		}

		int GetColumns() const noexcept
		{
			return m_Columns;
		}


	private:
		int m_Columns = 0;
		int m_Rows = 0;
	};
}
