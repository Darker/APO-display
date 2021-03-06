#ifndef SHAPETEXT_H
#define SHAPETEXT_H
#include "Shape.h"
#include "libs/stb_truetype.h"
#include <string>
#include <future>
#include <memory>
#include <map>

//#include "Future.h"
typedef std::future<stbtt_fontinfo> font_future;
typedef std::shared_future<stbtt_fontinfo> font_future_shared;
//typedef std::shared_ptr<font_future> font_future_ptr;
class ShapeText : public Shape
{
public:
    ShapeText(const std::string& text, const Color& color, double x=0, double y=0, const std::string& fontPath = "default.ttf");

    double x;
    double y;
    double scale;
    Color color;

    virtual void render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const override;
    virtual Shape* cloneNew() const override;
    virtual void boundingRect(float& x0, float& y0, float& x1, float& y1) const;

    class FontCache {
    public:
        /**
         * @brief getFont tries to fetch the font from given path, blocks
         * @param fontPath
         * @return
         */
        stbtt_fontinfo getFont(const std::string& fontPath);
        /**
         * @brief getFontLater initiates loading of the font in separate thread
         * @param fontPath
         */
        void getFontLater(const std::string& fontPath);
    protected:
        stbtt_fontinfo loadFont(const std::string& fontPath);
        std::map<std::string, font_future_shared> fontCache;
    };

    static FontCache GLOBAL_CACHE;
    void setText(const std::string& value);

protected:
    std::string text;
    std::string fontPath;

    // Used to cache rendered text
    const unsigned char* internal_bitmap;

};

#endif // SHAPETEXT_H
