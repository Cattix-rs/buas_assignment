#pragma once
#include <filesystem>
#include <span>

#include "BlendMode.hpp"
#include "Image.hpp"
#include "Rect.hpp"
#include "Sprite.hpp"

namespace Atlas
{

	class SpriteSheet
	{
	public:
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

		size_t GetNumberSprites() const noexcept
		{
			return m_Sprites.size();
		}

		int getSpriteWidth(size_t spriteId = 0) const noexcept
		{
			if (spriteId < m_Sprites.size())
				return m_Sprites[spriteId].getWidth();

			return 0;
		}

		int getSpriteHeight(size_t spriteId = 0) const noexcept
		{
			if (spriteId < m_Sprites.size())
				return m_Sprites[spriteId].getHeight();

			return 0;
		}

		void addSprite(const Sprite& sprite);

		const Sprite& getSprite(size_t index) const noexcept;

		const Sprite& operator[](size_t index) const noexcept;

		const Sprite& operator[](size_t i, size_t j) const noexcept;
	private:
		int m_Columns = 0;
		int m_Rows = 0;

		std::vector<Sprite> m_Sprites;
	};
}
