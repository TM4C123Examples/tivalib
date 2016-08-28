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

int button_get_sw1(void);
int button_get_sw2(void);
void led_set_color(int color);

void buttons_interupt_init(void (*callback_p)(int,int));

#ifdef __cplusplus
}
#endif

#endif /* _BOARD_TM4C123GXL_H */
