#pragma once

#include "Image.hpp"
// #include "Font.hpp"
#include "SpriteSheet.hpp"

#include <filesystem>  // For std::filesystem::path
#include <memory>      // For std::shared_ptr

namespace Atlas
{

	namespace ResourceManager
	{


		std::shared_ptr<Image> loadImage(const std::filesystem::path& filePath);


		std::shared_ptr<SpriteSheet> loadSpriteSheet(const std::filesystem::path& filePath, std::optional<int> spriteWidth = {}, std::optional<int> spriteHeight = {}, int padding = 0, int margin = 0, const BlendMode& blendMode = BlendMode{});


		std::shared_ptr<SpriteSheet> loadSpriteSheet(const std::filesystem::path& filePath, std::span<const Tmpl8::RectI> rects, const BlendMode& blendMode = BlendMode{});


		// std::shared_ptr<Font> loadFont( const std::filesystem::path& filePath, float size = 12.0f );

	}  // namespace ResourceManager
}