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


#endif // DISPLAY_MAGIC_H
