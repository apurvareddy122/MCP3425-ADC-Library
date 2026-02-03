#ifndef INC_MCP3425_H_
#define INC_MCP3425_H_

#if defined(STM32F412Vx) || defined(STM32F446xx)
    #include "stm32f4xx_hal.h"
#elif defined(STM32G030xx) || defined(STM32G0B0xx) || defined(STM32G070xx)
    #include "stm32g0xx_hal.h"
#elif defined(STM32G431xx)
    #include "stm32g4xx_hal.h"
#else
	#error "MCU not supported. Contact for support"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	ADDR_0 = 0x00, // Select this when using a single device and you have not specified a custom device address at factory
	ADDR_1 = 0x01,
    ADDR_2 = 0x02,
    ADDR_3 = 0x03,
    ADDR_4 = 0x04,
    ADDR_5 = 0x05,
    ADDR_6 = 0x06,
    ADDR_7 = 0x07,
}mcp3425_i2c_address_select_t;

typedef enum{
	ONE_SHOT = 0,
	CONTINUOUS = 1,
} mcp3425_conversion_t;

typedef enum{
	SPS_240 = 0x00, // Resolution 12 bits
	SPS_60 = 0x01, // Resolution 14 bits
	SPS_15 = 0x02, // Resolution 16 bits
}mcp3425_sample_rate_selection_t;

typedef enum{
	PGA_1 = 0x00,
	PGA_2 = 0x01,
	PGA_4 = 0x02,
	PGA_8 = 0x03,
}mcp3425_gain_selector_t;

typedef struct{
  I2C_HandleTypeDef *hi2c;
  uint8_t addr;

  mcp3425_conversion_t conversion;
  mcp3425_sample_rate_selection_t resolution;
  mcp3425_gain_selector_t gain;

  uint8_t buf[3];
}mcp3425_HandleTypeDef;

void MCP3425_I2C_ADDR(mcp3425_HandleTypeDef *m, mcp3425_i2c_address_select_t addr);

HAL_StatusTypeDef MCP3425_Config(mcp3425_HandleTypeDef *m);

HAL_StatusTypeDef MCP3425_ReadData(mcp3425_HandleTypeDef *m);

int16_t MCP3425_ParseData(mcp3425_HandleTypeDef *m);

#endif /* INC_MCP3425_H_ */
