#include "MCP3425.h"

static float MCP3425_RawToVoltage(mcp3425_HandleTypeDef *m,int16_t raw, float vref)
{
    uint32_t codes;

    switch (m->resolution) {
    case SPS_240: codes = 2048;  break;
    case SPS_60:  codes = 8192;  break;
    case SPS_15:  codes = 32768; break;
    default:      return 0.0f;
    }

    return ((float)raw * vref) / (codes * (1 << m->gain));
}

float MCP3425_Voltage(mcp3425_HandleTypeDef *m, float vref, float R1, float R2){
	int16_t raw = MCP3425_ParseData(m);
    float vadc = MCP3425_RawToVoltage(m,raw,vref);
    return vadc * (R1 + R2) / R2;
}

float MCP3425_ReadCurrent(mcp3425_HandleTypeDef *m,float vref,float shunt_resistance)
{
	int16_t raw = MCP3425_ParseData(m);
    float vshunt = MCP3425_RawToVoltage(m,raw,vref);
    return vshunt / shunt_resistance;
}

