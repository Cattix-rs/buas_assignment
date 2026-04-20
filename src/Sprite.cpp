#include <Sprite.hpp>
#include <resourceManager.hpp>

namespace Atlas///this Code likewise came form C++ for games course resources
{

    Sprite::Sprite(const std::filesystem::path& fileName, const BlendMode& blendMode)
        : m_Image{ ResourceManager::loadImage(fileName) }
        , m_BlendMode{ blendMode }
    {
        if (m_Image)
            m_Rect = Tmpl8::RectI{ 0, 0, m_Image->getWidth(), m_Image->getHeight() };
    }

    void Sprite::Draw(Tmpl8::vec2f pos, Tmpl8::Surface* target, bool flipped) const
    {
		if (!m_Image || !m_Image->data()) return;
	    int startX = static_cast<int>(pos.x);
	    int startY = static_cast<int>(pos.y);

		Color* srcBuffer = m_Image->data();

	    for (int y = 0; y < m_Rect.height; y++)
	    {
	        for (int x = 0; x < m_Rect.width; x++)
	        {
	            // THE MIRROR LOGIC:
	            // If flipped, we read pixels from (width - 1 - x) instead of (x)
	            int sourceX = flipped ? (m_Rect.width - 1 - x) : x;

	            // Get the pixel from the source image
	            Color p = srcBuffer[(m_Rect.left + sourceX) + (m_Rect.top + y) * m_Image->getWidth()];

	            // Only draw if not transparent (AlphaBlend logic)
	            if ((p.rgba & 0xff000000) != 0)
	            {
	                target->Plot(startX + x, startY + y, p.rgba);
	            }
	        }
	    }
        
    } 

    Sprite::Sprite(const std::filesystem::path& fileName, const Tmpl8::RectI& rect, const BlendMode& blendMode)
        : m_Image{ ResourceManager::loadImage(fileName) }
        , m_Rect{ rect }
        , m_BlendMode{ blendMode }
    {}
}