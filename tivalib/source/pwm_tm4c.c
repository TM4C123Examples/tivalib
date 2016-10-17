#include "TM4C123.h"                    // Device header
#include "pwm_tm4c.h"
#include "gpio_config_tm4c.h"

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

typedef struct {
    GPIOA_Type *gpio;
    uint32_t pin;
    uint32_t af;
} pin_description_t;

const pin_description_t pwm_pin_af[2][8] = {
    {{GPIOB,6,4},{GPIOB,7,4},{GPIOB,4,4},{GPIOB,5,4},{GPIOE,4,4},{GPIOE,5,4},{GPIOC,4,4},{GPIOC,5,4}},
    {{GPIOD,0,5},{GPIOD,1,5},{GPIOA,6,5},{GPIOA,7,5},{GPIOF,0,5},{GPIOF,1,5},{GPIOF,2,5},{GPIOF,3,5}}
};

static void pwm_peripheral_enable(int peripheral_index);
static void pwm_configure_channel(Custom_PWM0_Type* myPWM, int channel, float frequency, float initial_dc);

static void pwm_peripheral_enable(int peripheral_index){
    SYSCTL->RCGCPWM |= (0x1<<peripheral_index);
    while(!(SYSCTL->PRPWM & (0x1<<peripheral_index)));
}

static void pwm_configure_channel(Custom_PWM0_Type* myPWM, int channel, float frequency, float initial_dc){
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

void pwm_init(int peripheral_channel, float frequency, float initial_dc){
    uint32_t peripheral_index = (peripheral_channel>>8) & 0x1;
    uint32_t channel = peripheral_channel & 0xF;

    const pin_description_t *pin_configuration = &(pwm_pin_af[peripheral_index][channel]);

    gpio_peripheral_enable(pin_configuration->gpio);
    gpio_set_af(pin_configuration->gpio,pin_configuration->pin,pin_configuration->af);


    SYSCTL->RCC |= (0x1<<20);// Use pwm div
    SYSCTL->RCC |= (0x7<<17);// divide system clock by 64

    pwm_peripheral_enable(peripheral_index);
    Custom_PWM0_Type* myPWM = (void*)((peripheral_index)?PWM1:PWM0);
    pwm_configure_channel(myPWM,channel,frequency,initial_dc);
}

void pwm_set_dc(int peripheral_channel, float pwm_dc){
    uint32_t peripheral_index = (peripheral_channel>>8) & 0x1;
    uint32_t channel = peripheral_channel & 0xF;

    int load_value;
    int gen_block = (channel>>1)&0xf;
    int is_channel_b = channel&0x1;

    Custom_PWM0_Type* myPWM = (void*)((peripheral_index)?PWM1:PWM0);

    load_value = myPWM->generator[gen_block].LOAD;

    if(is_channel_b){
        myPWM->generator[gen_block].CMPB = (int)((load_value+1) * pwm_dc/100);
    }else{
        myPWM->generator[gen_block].CMPA = (int)((load_value+1) * pwm_dc/100);
    }
}

