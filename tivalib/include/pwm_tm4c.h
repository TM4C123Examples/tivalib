#ifndef _PWM_TM4C_H
#define _PWM_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

#define PWMCHANNEL_P0PWM0 0x0000
#define PWMCHANNEL_P0PWM1 0x0001
#define PWMCHANNEL_P0PWM2 0x0002
#define PWMCHANNEL_P0PWM3 0x0003
#define PWMCHANNEL_P0PWM4 0x0004
#define PWMCHANNEL_P0PWM5 0x0005
#define PWMCHANNEL_P0PWM6 0x0006
#define PWMCHANNEL_P0PWM7 0x0007
#define PWMCHANNEL_P0PWM8 0x0008

#define PWMCHANNEL_P1PWM0 0x0100
#define PWMCHANNEL_P1PWM1 0x0101
#define PWMCHANNEL_P1PWM2 0x0102
#define PWMCHANNEL_P1PWM3 0x0103
#define PWMCHANNEL_P1PWM4 0x0104
#define PWMCHANNEL_P1PWM5 0x0105
#define PWMCHANNEL_P1PWM6 0x0106
#define PWMCHANNEL_P1PWM7 0x0107
#define PWMCHANNEL_P1PWM8 0x0108

void pwm_init(int peripheral_channel, float frequency, float initial_dc);
void pwm_set_dc(int peripheral_channel, float pwm_dc);

#ifdef __cplusplus
}
#endif

#endif /* _PWM_TM4C_H */
