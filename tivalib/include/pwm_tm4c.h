#ifndef _PWM_TM4C_H
#define _PWM_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

#define PWM_A_ONLY 0
#define PWM_B_ONLY 1
#define PWM_A_AND_B 2

void pwm0_AB_init(float frequency,int mode,float pwm_a_initial_dc,float pwm_b_initial_dc);

void pwm0_A_set_dc(float pwm_dc);

void pwm0_B_set_dc(float pwm_dc);

#ifdef __cplusplus
}
#endif

#endif /* _PWM_TM4C_H */
