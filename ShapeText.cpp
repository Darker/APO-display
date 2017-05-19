#include "ShapeText.h"
#include "ShapeRendering.h"
#include <iostream>
#include <fstream>
ShapeText::FontCache ShapeText::GLOBAL_CACHE = ShapeText::FontCache();
ShapeText::ShapeText(const std::string& text, const Color& color, double x, double y, const std::string& fontPath) :
      Shape()
    , internal_bitmap(nullptr)
    , color(color)
    , text(text)
    , x(x)
    , y(y)
    , fontPath(fontPath)
{
    GLOBAL_CACHE.getFontLater(fontPath);
}

void ShapeText::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{

    const stbtt_fontinfo font = GLOBAL_CACHE.getFont(fontPath);
    if(font.numGlyphs > 0) {
        int w, h;
        const int scale_y = 40;
        // offset increases as you print individual letters
        float xoffset = x;
        // offset increases if there's a newline (to be implemented @TODO)
        //int xoffset = x;

        float scale = stbtt_ScaleForPixelHeight(&font, scale_y);
        int ascent;
        stbtt_GetFontVMetrics(&font, &ascent,0,0);
        int baseline = (int) (ascent*scale);
        for(int i=0, l=text.length(); i<l; ++i) {
            const char character = text[i];
            if(character==' ') {
                xoffset+=(scale_y*4)/5;
                continue;
            }
            // copied from example codes
            int advance,lsb,x0,y0,x1,y1;
            float x_shift = xoffset - (float) floor(xoffset);
            stbtt_GetCodepointHMetrics(&font, character, &advance, &lsb);
            stbtt_GetCodepointBitmapBoxSubpixel(&font, character, scale,scale,x_shift,0, &x0,&y0,&x1,&y1);

            unsigned char* bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, scale_y), character, &w, &h, 0,0);

            for(int cy=0; cy<h; ++cy) {
                if(cy+y>=pixmapHeight)
                    break;
                for(int cx=0; cx<h; ++cx) {
                    if(cx+x>=pixmapWidth)
                        break;
                    const unsigned char opacity = bitmap[cy*w+cx];
                    if(opacity<1)
                        continue;
                    blendPixel(pixmap, color, cx+xoffset+x0, cy+y+y0, opacity, pixmapWidth);
                    //setPixel(pixmap, color, cx+x, cy+y, pixmapWidth);
                    //std::cout<< (" .:ioVM@"[bitmap[cy*w+cx]>>5]);

                }
                //std::cout<<('\n');
            }
            free(bitmap);
            xoffset+=w+1;
        }
    }
}

Shape*ShapeText::cloneNew() const
{
    return new ShapeText(*this);
}

stbtt_fontinfo ShapeText::FontCache::getFont(const std::string& fontPath)
{
    // If the font is not in cache yet, start loading it
    getFontLater(fontPath);
    stbtt_fontinfo font;
    font.cff.data = nullptr;
    font.numGlyphs = 0;
    //font = fontCache[fontPath].get();
    try {
        // wait until the font is loaded
        font = fontCache[fontPath].get();
    }
    catch (const std::future_error& e) {
        const char* msg = e.what();
        const std::error_code code = e.code();
        std::cout<<"ERROR: cannot read value from future font: "<<msg<<"\n";
    }
    return font;
}

void ShapeText::FontCache::getFontLater(const std::string& fontPath)
{
    std::map<std::string, font_future_shared>::iterator pos = fontCache.find(fontPath);
    if(pos==fontCache.end()) {
          font_future_shared shared = std::async(&ShapeText::FontCache::loadFont, this, fontPath).share();
          fontCache.insert(std::make_pair(fontPath, shared));
//        fontCache.insert(std::make_pair(fontPath, {[this, fontPath] () -> stbtt_fontinfo {
//            return loadFont(fontPath);
//        }}));
    }
}

stbtt_fontinfo ShapeText::FontCache::loadFont(const std::string& fontPath)
{
    // used to save parsed font
    stbtt_fontinfo font;
    font.cff.data = nullptr;
    font.numGlyphs = 0;

    std::ifstream input( fontPath, std::ios::binary );
    if(input.is_open()) {
        // copies all data into buffer
        std::vector<char> buffer((
                std::istreambuf_iterator<char>(input)),
                (std::istreambuf_iterator<char>()));
        const unsigned char* bufferC = (unsigned char*)(&(buffer[0]));
        unsigned char* newBuffer = (unsigned char*)malloc(buffer.size()*sizeof(char));
        memcpy(newBuffer, bufferC, buffer.size()*sizeof(char));
        stbtt_InitFont(&font, newBuffer, stbtt_GetFontOffsetForIndex(bufferC,0));
    }

    return font;
}
