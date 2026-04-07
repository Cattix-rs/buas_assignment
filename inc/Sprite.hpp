#pragma once

#include "Image.hpp"
#include "BlendMode.hpp"
#include "Color.hpp"
#include "Rect.hpp"

#include "../template.h"
#include "../surface.h"

#include <filesystem>
#include <memory>
#include <span>

namespace Atlas
{
	class Sprite
	{
	public:
		Sprite() = default;
		explicit Sprite(const std::filesystem::path& fileName, const Tmpl8::RectI& rect, const BlendMode& blendMode = BlendMode{});
		explicit Sprite(std::shared_ptr<Image> image, const Tmpl8::RectI& rect, const BlendMode& blendMode = BlendMode {}) noexcept
			: m_Image {std::move(image)}
		, m_Rect{ rect }
		, m_BlendMode{blendMode}
		{}
		explicit Sprite(const std::filesystem::path& fileName, const BlendMode& blendMode = BlendMode{});
		explicit Sprite(std::shared_ptr<Image> image, const BlendMode& blendMode = BlendMode{}) noexcept
			: m_Image{ std::move(image) }
			, m_Rect{ 0, 0, m_Image->getWidth(), m_Image->getHeight() }
			, m_BlendMode{ blendMode }
		{}

		void Draw(Tmpl8::vec2f pos, Tmpl8::Surface* target, bool flipped = false) const;

		glm::ivec2 GetUV() const noexcept
		{
			return { m_Rect.left, m_Rect.top };
		}

		glm::ivec2 GetSize() const noexcept
		{
			return { m_Rect.width, m_Rect.height };
		}

		int GetWidth() const noexcept
		{
			return m_Rect.width;
		}

		int GetHeight() const noexcept
		{
			return m_Rect.height;
		}

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

		void SetColor(const Color& color) noexcept
		{
			m_Color = color;
		}

		const BlendMode& GetBlendMode() const noexcept
		{
			return m_BlendMode;
		}

		void SetBlendMode(const BlendMode& blendMode) noexcept
		{
			m_BlendMode = blendMode;
		}

		explicit operator bool() const noexcept
		{
			return m_Image != nullptr;
		}

	private:
		std::shared_ptr<Image> m_Image;

		Tmpl8::RectI m_Rect;

		Color m_Color{ Color::White };

		BlendMode m_BlendMode;
	};

	
}