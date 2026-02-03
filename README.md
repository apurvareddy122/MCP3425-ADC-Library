# MCP3425-ADC-Library
MCP3425 ADC Library for STM32

Usage example:

```
#include "MCP3425.h"
#include "MCP3425_utils.h"

mcp3425_HandleTypeDef adc;

adc.hi2c = &hi2c1;
adc.conversion = ONE_SHOT;
adc.resolution = SPS_240;
adc.gain = PGA_1;

int main(void){
  MCP3425_I2C_ADDR(&adc, ADDR_0);
  MCP3425_Config(&adc);
  
  while (1)
  {
  	  if (MCP3425_ReadData(&adc) == HAL_OK)
  	  {
  		  float voltage = MCP3425_Voltage(&adc, 2.048f, 10000.0f, 10000.0f);
  		  float current = MCP3425_ReadCurrent(&adc, 2.048f, 0.1f);
  	  }

  	  HAL_Delay(500);
  }
}
```
Please feel free to contact if you encounter any bugs or if you have any suggestions.
