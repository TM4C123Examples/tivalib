#ifndef _TIMER_PWM_TM4C_H
#define _TIMER_PWM_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif
int timer_pwm_init(void);
void set_timer_pwm(float duty_cycle);
#ifdef __cplusplus
}
#endif

#endif /* _TIMER_PWM_TM4C_H */
