#include "TM4C123.h"                    // Device header
#include "pwm_tm4c.h"

void gpio_set_af(GPIOA_Type *gpio,uint32_t pin,uint32_t af_select);
void gpio_peripheral_enable(GPIOA_Type *gpio);
int gpio_get_peripheral_index(GPIOA_Type *gpio);

void gpio_set_af(GPIOA_Type *gpio,uint32_t pin,uint32_t af_select){
        gpio->DEN |= (0x1<<pin);//digital functions
        gpio->AFSEL |= (0x1<<pin);//alternate functions
        gpio->PCTL &= ~(((uint32_t)0xF)<<(pin*4));
        gpio->PCTL |= (((uint32_t)af_select)<<(pin*4));//Connect Pin6 to alternate function 4 (m0pwm0)
}

void gpio_peripheral_enable(GPIOA_Type *gpio){
    int p_index = gpio_get_peripheral_index(gpio);
    SYSCTL->RCGCGPIO |= (0x1<<p_index);
    while(!(SYSCTL->PRGPIO & (0x1<<p_index)));
}

int gpio_get_peripheral_index(GPIOA_Type *gpio){
    uint32_t address = (uint32_t) gpio;
    return (address-GPIOA_BASE)/(GPIOB_BASE-GPIOA_BASE);
}

typedef struct {
    uint32_t  CTL;                            /*!< PWMX Control                                                          */
    uint32_t  INTEN;                          /*!< PWMX Interrupt and Trigger Enable                                     */
    uint32_t  RIS;                            /*!< PWMX Raw Interrupt Status                                             */
    uint32_t  ISC;                            /*!< PWMX Interrupt Status and Clear                                       */
    uint32_t  LOAD;                           /*!< PWMX Load                                                             */
    uint32_t  COUNT;                          /*!< PWMX Counter                                                          */
    uint32_t  CMPA;                           /*!< PWMX Compare A                                                        */
    uint32_t  CMPB;                           /*!< PWMX Compare B                                                        */
    uint32_t  GENA;                           /*!< PWMX Generator A Control                                              */
    uint32_t  GENB;                           /*!< PWMX Generator B Control                                              */
    uint32_t  DBCTL;                          /*!< PWMX Dead-Band Control                                                */
    uint32_t  DBRISE;                         /*!< PWMX Dead-Band Rising-Edge Delay                                      */
    uint32_t  DBFALL;                         /*!< PWMX Dead-Band Falling-Edge-Delay                                     */
    uint32_t  FLTSRC0;                        /*!< PWMX Fault Source 0                                                   */
    uint32_t  FLTSRC1;                        /*!< PWMX Fault Source 1                                                   */
    uint32_t  MINFLTPER;                      /*!< PWMX Minimum Fault Period                                             */
} PWM_GENERATOR_Type;

typedef struct {                                    /*!< PWM0 Structure                                                        */
  __IO uint32_t  CTL;                               /*!< PWM Master Control                                                    */
  __IO uint32_t  SYNC;                              /*!< PWM Time Base Sync                                                    */
  __IO uint32_t  ENABLE;                            /*!< PWM Output Enable                                                     */
  __IO uint32_t  INVERT;                            /*!< PWM Output Inversion                                                  */
  __IO uint32_t  FAULT;                             /*!< PWM Output Fault                                                      */
  __IO uint32_t  INTEN;                             /*!< PWM Interrupt Enable                                                  */
  __IO uint32_t  RIS;                               /*!< PWM Raw Interrupt Status                                              */
  __IO uint32_t  ISC;                               /*!< PWM Interrupt Status and Clear                                        */
  __IO uint32_t  STATUS;                            /*!< PWM Status                                                            */
  __IO uint32_t  FAULTVAL;                          /*!< PWM Fault Condition Value                                             */
  __IO uint32_t  ENUPD;                             /*!< PWM Enable Update                                                     */
  __I  uint32_t  RESERVED[5];
  __IO PWM_GENERATOR_Type  generator[4];
  __I  uint32_t  RESERVED1[432];
  __IO uint32_t  _0_FLTSEN;                         /*!< PWM0 Fault Pin Logic Sense                                            */
  __I  uint32_t  _0_FLTSTAT0;                       /*!< PWM0 Fault Status 0                                                   */
  __I  uint32_t  _0_FLTSTAT1;                       /*!< PWM0 Fault Status 1                                                   */
  __I  uint32_t  RESERVED2[29];
  __IO uint32_t  _1_FLTSEN;                         /*!< PWM1 Fault Pin Logic Sense                                            */
  __I  uint32_t  _1_FLTSTAT0;                       /*!< PWM1 Fault Status 0                                                   */
  __I  uint32_t  _1_FLTSTAT1;                       /*!< PWM1 Fault Status 1                                                   */
  __I  uint32_t  RESERVED3[30];
  __I  uint32_t  _2_FLTSTAT0;                       /*!< PWM2 Fault Status 0                                                   */
  __I  uint32_t  _2_FLTSTAT1;                       /*!< PWM2 Fault Status 1                                                   */
  __I  uint32_t  RESERVED4[30];
  __I  uint32_t  _3_FLTSTAT0;                       /*!< PWM3 Fault Status 0                                                   */
  __I  uint32_t  _3_FLTSTAT1;                       /*!< PWM3 Fault Status 1                                                   */
  __I  uint32_t  RESERVED5[397];
  __IO uint32_t  PP;                                /*!< PWM Peripheral Properties                                             */
} Custom_PWM0_Type;

void pwm_configure_channel(Custom_PWM0_Type* myPWM, int channel, float frequency, float initial_dc){
    SystemCoreClockUpdate();
    int load_value = (int)((SystemCoreClock/(64.0f*frequency)))-1;
    int gen_block = (channel>>1)&0xf;
    int is_channel_b = channel&0x1;
    
    myPWM->generator[gen_block].CTL = 0;
    myPWM->generator[gen_block].GENA = (0x3<<6)|(0x2<<0);
    myPWM->generator[gen_block].GENB = (0x3<<10)|(0x2<<0);
    myPWM->generator[gen_block].LOAD = load_value;

    
    if(is_channel_b){
        myPWM->generator[gen_block].CMPB = (int)((load_value+1) * initial_dc/100);
    }else{
        myPWM->generator[gen_block].CMPA = (int)((load_value+1) * initial_dc/100);
    }
    
    myPWM->generator[gen_block].CTL = (0x1<<2)|(0x1<<0);
    myPWM->ENABLE |= 0x1<<channel;
}

void pwm0_AB_init(float frequency,int mode,float pwm_a_initial_dc,float pwm_b_initial_dc){
    //Configure PB6 as alternate function for M0PWM0
    if((mode == PWM_A_ONLY)||(mode == PWM_A_AND_B)){
        gpio_peripheral_enable(GPIOB);
        gpio_set_af(GPIOB,6,4);//Connect Pin6 to alternate function 4 (m0pwm0)
    }
    //Configure PB7 as alternate function for M0PWM1
    if((mode == PWM_B_ONLY)||(mode == PWM_A_AND_B)){
        gpio_peripheral_enable(GPIOB);
        gpio_set_af(GPIOB,7,4);//Connect Pin7 to alternate function 4 (m0pwm1)
    }

    SYSCTL->RCC |= (0x1<<20);// Use pwm div
    SYSCTL->RCC |= (0x7<<17);// divide system clock by 64

    SYSCTL->RCGCPWM |= (0x1<<0);//Turn on PWM0
    while(!(SYSCTL->PRPWM & (0x1<<0)));

    SystemCoreClockUpdate();
    int load_value = (int)((SystemCoreClock/(64.0f*frequency)))-1;

    Custom_PWM0_Type* myPWM = (Custom_PWM0_Type*)PWM0;

    if((mode == PWM_A_ONLY)||(mode == PWM_A_AND_B)){
        pwm_configure_channel(myPWM,0,frequency,pwm_a_initial_dc);
    }
    if((mode == PWM_B_ONLY)||(mode == PWM_A_AND_B)){
        pwm_configure_channel(myPWM,1,frequency,pwm_b_initial_dc);
    }
}

void pwm0_A_set_dc(float pwm_dc){
    Custom_PWM0_Type* myPWM = (Custom_PWM0_Type*)PWM0;
    myPWM->generator[0].CMPA = (int)((myPWM->generator[0].LOAD + 1)* pwm_dc/100);
}

void pwm0_B_set_dc(float pwm_dc){
    Custom_PWM0_Type* myPWM = (Custom_PWM0_Type*)PWM0;
    myPWM->generator[0].CMPB = (int)((myPWM->generator[0].LOAD + 1)* pwm_dc/100);
}

