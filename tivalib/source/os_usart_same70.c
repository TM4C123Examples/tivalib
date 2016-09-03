#include "os_usart_same70.h"
#include "usart_same70.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

#define USART_SIGNAL 1

osMutexDef(usart1_tx_mutex);
osMutexId usart1_tx_mutex_id;
osThreadId usart1_tx_owner;

osMutexDef(usart1_rx_mutex);
osMutexId usart1_rx_mutex_id;
osThreadId usart1_rx_owner;
int usart1_rx_nBytesRead;

void _os_usart1_tx_callback(void);
void _os_usart1_rx_callback(int);

void os_usart1_init(int baudrate){
    usart1_init(baudrate);
    usart1_tx_mutex_id = osMutexCreate(osMutex(usart1_tx_mutex));
    usart1_rx_mutex_id = osMutexCreate(osMutex(usart1_rx_mutex));
}

void os_usart1_puts(const char* pData){
    osMutexWait(usart1_tx_mutex_id, osWaitForever);
    usart1_tx_owner = osThreadGetId();
    osSignalClear(usart1_tx_owner, USART_SIGNAL);

    usart1_async_puts(pData, _os_usart1_tx_callback);

    osSignalWait(USART_SIGNAL, osWaitForever);
    osMutexRelease(usart1_tx_mutex_id);
}

int os_usart1_gets(char *pBuffer){
    osMutexWait(usart1_rx_mutex_id, osWaitForever);
    usart1_rx_owner = osThreadGetId();
    osSignalClear(usart1_rx_owner, USART_SIGNAL);

    usart1_async_gets(pBuffer, _os_usart1_rx_callback);

    osSignalWait(USART_SIGNAL, osWaitForever);
    osMutexRelease(usart1_rx_mutex_id);
    return usart1_rx_nBytesRead;
}

void _os_usart1_tx_callback(void){
    osSignalSet(usart1_tx_owner, USART_SIGNAL);
}

void _os_usart1_rx_callback(int nBytesRead){
    usart1_rx_nBytesRead  =  nBytesRead;
    osSignalSet(usart1_rx_owner, USART_SIGNAL);
}
