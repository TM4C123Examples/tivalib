#ifndef _ADC_TM4C_H
#define _ADC_TM4C_H

#ifdef __cplusplus
extern "C" {
#endif

void adc_init(void);
int adc_read(int select_channel);

#ifdef __cplusplus
}
#endif

#endif /* _ADC_TM4C_H */
