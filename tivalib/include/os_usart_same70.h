#ifndef _OS_USART_SAME70_H
#define _OS_USART_SAME70_H

void os_usart1_init(int baudrate);
void os_usart1_puts(const char* pData);
int os_usart1_gets(char *pBuffer);

#endif// _OS_USART_SAME70_H
