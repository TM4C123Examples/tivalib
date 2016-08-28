#ifndef _BOARD_TM4C123GXL_H
#define _BOARD_TM4C123GXL_H

#ifdef __cplusplus
extern "C" {
#endif

#define LED_BLACK (0x0)
#define LED_RED (0x1<<1)
#define LED_BLUE (0x1<<2)
#define LED_GREEN (0x1<<3)
#define LED_WHITE ((0x1<<1)|(0x1<<2)|(0x1<<3))

void led_init(void);
void buttons_init(void);

int get_button_sw1(int state);
int get_button_sw2(int state);
void led_set_color(int color);

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_TM4C123GXL_H */
