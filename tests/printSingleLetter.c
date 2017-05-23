#include <stdio.h>
#define STB_TRUETYPE_IMPLEMENTATION  // force following include to generate implementation
#include "../libs/stb_truetype.h"
#include <cmath>
#include <string>
#include <iostream>
char ttf_buffer[1<<25];
std::string text;
int main1(int argc, char **argv);
int main2(int argc, char **argv);

void printDimensions(const int w, const int h) {
    std::cout<<"Dimensions of letter: "<<w<<" x "<<h<<'\n';
}

int main(int argc, char **argv) {
    std::cout<<"MAIN1:\n";
    int letter = argc > 1 ? atoi(argv[1]) : 'i';
    text+=(char)letter;
    main1(argc, argv);
    std::cout<<"______________________________________________________\nMAIN2:\n";
    main2(argc, argv);
    return 0;
}

int main1(int argc, char **argv)
{
   stbtt_fontinfo font;
   unsigned char *bitmap;
   const int character = argc > 1 ? atoi(argv[1]) : 'i';
   int w,h,scale_y = (argc > 2 ? atoi(argv[2]) : 20);

   fread(ttf_buffer, 1, 1<<25, fopen(argc > 3 ? argv[3] : "../diablo.ttf", "rb"));

   stbtt_InitFont(&font, (const unsigned char*)ttf_buffer, stbtt_GetFontOffsetForIndex((const unsigned char*)ttf_buffer,0));
   bitmap = stbtt_GetCodepointBitmap(&font, 0,stbtt_ScaleForPixelHeight(&font, scale_y), character, &w, &h, 0,0);

   printDimensions(w, h);
   for (int cy=0; cy < h; ++cy) {
      for (int cx=0; cx < w; ++cx)
         putchar(" .:ioVM@"[bitmap[cy*w+cx]>>5]);
      putchar('\n');
   }
   return 0;
}

int main2(int argc, char **argv) {
    //const stbtt_fontinfo font = GLOBAL_CACHE.getFont(fontPath);
    stbtt_fontinfo font;

    fread(ttf_buffer, 1, 1<<25, fopen("../diablo.ttf", "rb"));
    stbtt_InitFont(&font, (const unsigned char*)ttf_buffer, stbtt_GetFontOffsetForIndex((const unsigned char*)ttf_buffer,0));

    const int pixmapWidth = 5000;
    const int pixmapHeight = 5000;
    const int x = 0;
    const int y = 0;
    if(font.numGlyphs > 0) {
        int w, h;
        const int scale_y = 20;
        // offset increases as you print individual letters
        float xoffset = x;
        // offset increases if there's a newline (to be implemented @TODO)
        //int xoffset = x;

        float scale = stbtt_ScaleForPixelHeight(&font, scale_y);
        int ascent;
        stbtt_GetFontVMetrics(&font, &ascent,0,0);
        for(int i=0, l=text.length(); i<l; ++i) {
            const int character = text[i];
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
            printDimensions(w, h);

            for(int cy=0; cy<h; ++cy) {
                if(cy+y>=pixmapHeight)
                    break;
                for(int cx=0; cx<w; ++cx) {
                    if(cx+x>=pixmapWidth)
                        break;
                    const unsigned char opacity = bitmap[cy*w+cx];
                    putchar(" .:ioVM@"[bitmap[cy*w+cx]>>5]);
                    if(opacity<1)
                        continue;
                    //blendPixel(pixmap, color, cx+xoffset+x0, cy+y+y0, opacity, pixmapWidth);
                    //setPixel(pixmap, color, cx+x, cy+y, pixmapWidth);


                }
                putchar('\n');
            }
            //STBTT_free(bitmap, font.userdata);
            ((void)(font.userdata),free(bitmap));
            //free(bitmap);
            xoffset+=w+1;
        }
    }
}
