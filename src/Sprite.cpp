#include <Sprite.hpp>
#include <resourceManager.hpp>

namespace Atlas
{

    Sprite::Sprite(const std::filesystem::path& fileName, const BlendMode& blendMode)
        : m_Image{ ResourceManager::loadImage(fileName) }
        , m_BlendMode{ blendMode }
    {
        if (m_Image)
            m_Rect = Tmpl8::RectI{ 0, 0, m_Image->getWidth(), m_Image->getHeight() };
    }

    Sprite::Sprite(const std::filesystem::path& fileName, const Tmpl8::RectI& rect, const BlendMode& blendMode)
        : m_Image{ ResourceManager::loadImage(fileName) }
        , m_Rect{ rect }
        , m_BlendMode{ blendMode }
    {}
}