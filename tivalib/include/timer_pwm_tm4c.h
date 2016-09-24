#ifndef _TIMER_PWM_TM4C_H
#define _TIMER_PWM_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif
int timer0_pwm_init(int frequency_timer);
void timer0_pwm_set(float duty_cycle);
#ifdef __cplusplus
}
#endif

#endif /* _TIMER_PWM_TM4C_H */
