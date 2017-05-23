#include "ShapeText.h"
#include "ShapeRendering.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
ShapeText::FontCache ShapeText::GLOBAL_CACHE = ShapeText::FontCache();
ShapeText::ShapeText(const std::string& text, const Color& color, double x, double y, const std::string& fontPath) :
      Shape()
    , internal_bitmap(nullptr)
    , color(color)
    , text(text)
    , x(x)
    , y(y)
    , fontPath(fontPath)
    , scale(40.0)
{
    GLOBAL_CACHE.getFontLater(fontPath);
}
char ttf_buffer[1<<25];
void ShapeText::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) const
{

    const stbtt_fontinfo font = GLOBAL_CACHE.getFont(fontPath);
//    stbtt_fontinfo font;

//    fread(ttf_buffer, 1, 1<<25, fopen(fontPath.c_str(), "rb"));
//    stbtt_InitFont(&font, (const unsigned char*)ttf_buffer, stbtt_GetFontOffsetForIndex((const unsigned char*)ttf_buffer,0));

    if(font.numGlyphs > 0) {
        int w, h;
        const int scale_y = (int)std::round(scale);
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
            float x_shift = xoffset - (float) std::floor(xoffset);
            stbtt_GetCodepointHMetrics(&font, character, &advance, &lsb);
            stbtt_GetCodepointBitmapBoxSubpixel(&font, character, scale,scale,x_shift,0, &x0,&y0,&x1,&y1);

            unsigned char* bitmap = stbtt_GetCodepointBitmap(&font, 0, stbtt_ScaleForPixelHeight(&font, scale_y), character, &w, &h, 0,0);

            for(int cy=0; cy<h; ++cy) {
                if(cy+y>=pixmapHeight)
                    break;
                for(int cx=0; cx<w; ++cx) {
                    if(cx+x>=pixmapWidth)
                        break;
                    const unsigned char opacity = bitmap[cy*w+cx];
                    if(opacity<1)
                        continue;
                    blendPixel(pixmap, color, cx+xoffset+x0, cy+y+y0+baseline, opacity, pixmapWidth);
                    //setPixel(pixmap, color, cx+x, cy+y, pixmapWidth);
                    //std::cout<< (" .:ioVM@"[bitmap[cy*w+cx]>>5]);

                }
                //std::cout<<('\n');
            }
            //STBTT_free(bitmap, font.userdata);
            ((void)(font.userdata),free(bitmap));
            //free(bitmap);
            xoffset+=w+1;
        }
    }
}

Shape*ShapeText::cloneNew() const
{
    return new ShapeText(*this);
}

void ShapeText::boundingRect(float& x0, float& y0, float& x1, float& y1) const
{
    const stbtt_fontinfo font = GLOBAL_CACHE.getFont(fontPath);
    if(font.numGlyphs > 0) {
        const int scale_y = (int)std::round(scale);
        // offset increases as you print individual letters
        int minx = 1e8;
        int miny = 1e8;
        int maxx = 0;
        int maxy = 0;
        int xoffset = 0;

        for(int i=0, l=text.length(); i<l; ++i) {
            const char character = text[i];

            // copied from example codes
            int cx0,cy0,cx1,cy1;
            if(character==' ') {
                //cx0 = 0;
            }
            else {
                float x_shift = xoffset - (float) std::floor(xoffset);
                stbtt_GetCodepointBitmapBoxSubpixel(&font, character, scale,scale,x_shift,0, &cx0,&cy0,&cx1,&cy1);
            }
            if(minx>cx0)
                minx=cx0;
            if(miny>cy0)
                miny=cy0;
            if(maxx>cx1)
                maxx=cx1;
            if(maxy>cy1)
                maxy=cy1;
        }
    }
    return;
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
        std::memcpy(newBuffer, bufferC, buffer.size()*sizeof(char));
        stbtt_InitFont(&font, newBuffer, stbtt_GetFontOffsetForIndex(bufferC,0));
    }
    else {
        std::cout<<"ERROR: cannot open font "<<fontPath<<"\n";
        exit(0);
    }

    return font;
}
