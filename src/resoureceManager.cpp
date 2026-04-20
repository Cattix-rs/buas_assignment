#include <resourceManager.hpp>
#include <hash.hpp>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
///this Code likewise came form C++ for games course resources
    struct FontKey
    {
        std::filesystem::path fontFile;
        float                 size;

        bool operator==(const FontKey& other) const
        {
            return fontFile == other.fontFile && size == other.size;
        }
    };

    // Hasher for a FontKey.
    template<>
    struct std::hash<FontKey>
    {
        size_t operator()(const FontKey& key) const noexcept
        {
            std::size_t seed = 0;

            hash_combine(seed, key.fontFile);
            hash_combine(seed, key.size);

            return seed;
        }
    };

    namespace
    {

        // Image store.
        std::unordered_map<std::filesystem::path, std::shared_ptr<Atlas::Image>> g_ImageMap;

        // Font store.
        // std::unordered_map<FontKey, std::shared_ptr<Font>> g_FontMap;

    }  // namespace

    namespace Atlas::ResourceManager
    {
        std::shared_ptr<Atlas::Image> ResourceManager::loadImage(const std::filesystem::path& filePath)
        {
            const auto iter = g_ImageMap.find(filePath);

            if (iter == g_ImageMap.end())
            {
                auto image = std::make_shared<Atlas::Image>(filePath);

                g_ImageMap.insert({ filePath, image });

                return image;
            }

            return iter->second;
        }

        std::shared_ptr<Atlas::SpriteSheet> ResourceManager::loadSpriteSheet(const std::filesystem::path& filePath, std::optional<int> spriteWidth, std::optional<int> spriteHeight, int padding, int margin, const Atlas::BlendMode& blendMode)
        {
            auto image = loadImage(filePath);
            return std::make_shared<Atlas::SpriteSheet>(image, spriteWidth, spriteHeight, padding, margin, blendMode);
        }

        std::shared_ptr<Atlas::SpriteSheet> ResourceManager::loadSpriteSheet(const std::filesystem::path& filePath, std::span<const Tmpl8::RectI> rects, const Atlas::BlendMode& blendMode)
        {
            auto image = loadImage(filePath);
            return std::make_shared<Atlas::SpriteSheet>(image, rects, blendMode);
        }
    }
    /*
    std::shared_ptr<Font> ResourceManager::loadFont( const std::filesystem::path& filePath, float size )
    {
        FontKey    key { filePath, size };
        const auto iter = g_FontMap.find( key );

        if (iter == g_FontMap.end())
        {
            auto font = std::make_shared<Font>( filePath, size );
            g_FontMap[key] = font;

            return font;
        }

        return iter->second;
    }

    */

    std::shared_ptr<Atlas::SpriteSheet> Atlas::ResourceManager::loadSpriteSheetFromTxt(
        const std::string& txtPath,
        const std::string& imagePath,
        Atlas::BlendMode mode)
    {
        auto texture = loadImage(imagePath);
        if (!texture) return nullptr;

        // 2. Parse the .txt file into a temp vector of Rects
        std::vector<Tmpl8::RectI> rects;
        std::ifstream file(txtPath);
        std::string line;

        if (!file.is_open()) return nullptr;

        while (std::getline(file, line))
        {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::stringstream ss(line);
            std::string junk;
            int x, y, w, h;
            if (ss >> junk >> x >> y >> w >> h)
            {
                rects.push_back({ x,y,w,h });
            }
            
        }

       //returns sprite objs
        return std::make_shared<Atlas::SpriteSheet>(texture, rects, mode);
    }
