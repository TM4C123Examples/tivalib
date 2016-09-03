#ifndef _TIMER_TM4C_H
#define _TIMER_TM4C_H

#define TIMER_BASETIME_US 0
#define TIMER_BASETIME_MS 1

#define TIMER_BASE_MS 0
#define TIMER_BASE_US 1

#ifdef __cplusplus
extern "C" {
#endif

void timer0_init(int period,int basetime,void(*p_callback)(void));
void timer0_start(void);
void timer0_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* _TIMER_TM4C_H */
