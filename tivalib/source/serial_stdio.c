#include "serial_stdio.h"

#define OUT_BUFFER_SIZE 80

void serial_puts(Serial_t serial ,const char * pString){
	char newChar; 
	int i ;
	for(i = 0 ; i < 81; i++){
		newChar = pString[i];
		if( newChar != '\0' ){
			serial.sendChar(newChar);
		}else{
			break;
		}
	}
}

int serial_gets(Serial_t  serial,char * pBuffer, int bufferSize){
	char newChar; 
	int i ;
	for(i = 0 ; i < (bufferSize - 1); i++){
		newChar = serial.getChar();
		if( (newChar != '\r') ){
			pBuffer[i]=newChar;
		}else{
			pBuffer[i]='\0';
			return i;
		}
	}
	pBuffer[bufferSize-1]='\0';
	return bufferSize-1;
}

void serial_printf(Serial_t  serial, const char * format ,...){
	char * tempBuffer;
	va_list args;
	va_start(args, format);
	#if defined ( __GNUC__ )
	vasprintf(&tempBuffer,format, args);
	#else	
	tempBuffer=malloc(OUT_BUFFER_SIZE);//alocate memory manualy
	vsnprintf(tempBuffer,OUT_BUFFER_SIZE,format,args);
	#endif
	va_end(args);
	serial_puts(serial,tempBuffer);
	free(tempBuffer);
}
