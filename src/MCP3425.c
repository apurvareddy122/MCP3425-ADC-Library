#include "MCP3425.h"


void MCP3425_I2C_ADDR(mcp3425_HandleTypeDef *m,mcp3425_i2c_address_select_t addr){
	uint8_t i2c_addr;
	i2c_addr = (0x68 | (addr & 0x07));
	m -> addr = i2c_addr;
}


HAL_StatusTypeDef MCP3425_Config(mcp3425_HandleTypeDef *m){
	uint8_t cfg = 0;
	HAL_StatusTypeDef ret;

	cfg |= (m->conversion & 0x01) << 4;
	cfg |= (m->resolution & 0x03) << 2;
	cfg |= (m->gain & 0x03);

	ret = HAL_I2C_Master_Transmit(m->hi2c, m->addr, &cfg, 1, 10);
	if(ret != HAL_OK) return ret;

	return HAL_OK;
}

HAL_StatusTypeDef MCP3425_ReadData(mcp3425_HandleTypeDef *m){

	HAL_StatusTypeDef ret;

	ret = HAL_I2C_Master_Receive(m->hi2c, m->addr, m->buf, 3, 1000);
	if(ret != HAL_OK) return ret;
	HAL_Delay(10);

	if (m->buf[2] & 0x80) {
	    return HAL_BUSY;
	}

	return HAL_OK;
}

int16_t MCP3425_ParseData(mcp3425_HandleTypeDef *m){
	int16_t data = ((uint16_t)m->buf[0] << 8) | m->buf[1];;

	switch (m->resolution){
	case SPS_240:
		data >>= 4;
		break;
	case SPS_60:
		data >>= 2;
		break;
	case SPS_15:
		break;
	default:
		data = 0;
		break;
	}

	return data;
}

