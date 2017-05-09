#ifndef DISPLAY_MAGIC_H
#define DISPLAY_MAGIC_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#define SPILED_REG_BASE_PHYS 0x43c40000
#define SPILED_REG_SIZE      0x00004000

#define SPILED_REG_LED_LINE_o           0x004
#define SPILED_REG_LED_RGB1_o           0x010
#define SPILED_REG_LED_RGB2_o           0x014
#define SPILED_REG_LED_KBDWR_DIRECT_o   0x018

#define SPILED_REG_KBDRD_KNOBS_DIRECT_o 0x020
#define SPILED_REG_KNOBS_8BIT_o         0x024

#define PARLCD_REG_BASE_PHYS 0x43c00000
#define PARLCD_REG_SIZE      0x00004000

#define PARLCD_REG_CMD_o                0x0008
#define PARLCD_REG_DATA_o               0x000C
void *map_phys_address(off_t region_base, size_t region_size, int opt_cached);
void parlcd_write_cmd(unsigned char *parlcd_mem_base, uint16_t cmd);
void parlcd_write_data(unsigned char *parlcd_mem_base, uint16_t data);
void parlcd_write_data2x(unsigned char *parlcd_mem_base, uint32_t data);
void parlcd_delay(int msec);
void parlcd_hx8357_init(unsigned char *parlcd_mem_base);


class parlcd_KnobValues {
  public:
  // Example of knob values    R G B
  //  int   16574668 uint 0x00fce8cc
  //  Human readable: RGB 252 232 204
  // First byte is apparently unused
  
  // Using the information above, we can see that we
  // need to move bitmask to desired byte
  // perform & operation and move the result back to 1st byte
    parlcd_KnobValues(const uint32_t rawData) :
        red  ((rawData&0x00FF0000)>>16)
      , green((rawData&0x0000FF00)>>8)
      , blue ((rawData&0x000000FF))
    {}
    parlcd_KnobValues() :
        red(0)
      , green(0)
      , blue(0)
    {}
    parlcd_KnobValues(const uint8_t r, const uint8_t g, const uint8_t b) :
        red(r)
      , green(g)
      , blue(b)
    {}
    uint8_t red;
    uint8_t blue;
    uint8_t green;
};

parlcd_KnobValues parlcd_knob_values(unsigned char *parlcd_mem_base);
#endif // DISPLAY_MAGIC_H
