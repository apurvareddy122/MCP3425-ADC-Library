#ifndef INC_MCP3425_UTILS_H_
#define INC_MCP3425_UTILS_H_

float MCP3425_Voltage(mcp3425_HandleTypeDef *m, float vref, float R1, float R2);
float MCP3425_ReadCurrent(mcp3425_HandleTypeDef *m, float vref, float shunt_resistance);

#endif /* INC_MCP3425_UTILS_H_ */
