#include "spi_tm4c.h"
/* examples for
	SPI conection to MCP4921 12bit dac
	PIN 	NAME			CONNECT TO
	1			VDD				3.3v
	2			/CS				spi cs
	3			SCK				spi sck
	4			SDI				spi sdo
	5			/LDAC			10k resistor to gnd
	6			VREFA			vref (2.5v)
	7			AVSS			gnd
	8			VOUTA			output

	spi singnalign
	idle state: /CS=1 SCK=0 SDI=x
							/CS=0 SCK=0 SDI=x/data
							/CS=0 SCK=0 SDI=data_i //repeat this i times
							/CS=0 SCK=1 SDI=data_i //
							/CS=0 SCK=0 SDI=x
							 CS=1 SCK=0 SDI=x
*/



float volt=1.5;

int main(){
	int dac_volt;
	spi_init();
	while(1){
		dac_volt=(int) (volt*(4095.0/2.5));
		spi_write16(dac_volt);
	}
}

