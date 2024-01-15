#include "BLEProtocol.h"

std::map<DataType, SampleConfig> sampleConfigSelector = {
    {T_RH_V3,
     {.dataType = DataType::T_RH_V3,
      .downloadType = 0,
      .sampleType = 4,
      .sampleSizeBytes = 4,
      .sampleCountPerPacket = 4,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}}}}},
    {T_RH_V4,
     {.dataType = DataType::T_RH_V4,
      .downloadType = 5,
      .sampleType = 6,
      .sampleSizeBytes = 4,
      .sampleCountPerPacket = 4,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV2}}}}},
    {T_RH_VOC,
     {.dataType = DataType::T_RH_VOC,
      .downloadType = 1,
      .sampleType = 3,
      .sampleSizeBytes = 6,
      .sampleCountPerPacket = 3,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 4,
                        .converterFunction = &convertSimple}}}}},
    {T_RH_CO2,
     {.dataType = DataType::T_RH_CO2,
      .downloadType = 9,
      .sampleType = 10,
      .sampleSizeBytes = 6,
      .sampleCountPerPacket = 3,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}}}}},
    {T_RH_CO2_ALT,
     {.dataType = DataType::T_RH_CO2_ALT,
      .downloadType = 7,
      .sampleType = 8,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}}}}},
    {T_RH_CO2_PM25,
     {.dataType = DataType::T_RH_CO2_PM25,
      .downloadType = 11,
      .sampleType = 12,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 6,
                        .converterFunction = &convertPM2p5V1}}}}},
    {T_RH_VOC_PM25,
     {.dataType = DataType::T_RH_VOC_PM25,
      .downloadType = 15,
      .sampleType = 16,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 6,
                        .converterFunction = &convertPM2p5V1}}}}},
    {T_RH_VOC_NOX,
     {.dataType = DataType::T_RH_VOC_NOX,
      .downloadType = 21,
      .sampleType = 22,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::NOX_INDEX,
                       {.signalType = SignalType::NOX_INDEX,
                        .offset = 6,
                        .converterFunction = &convertSimple}}}}},
    {T_RH_VOC_NOX_PM25,
     {.dataType = DataType::T_RH_VOC_NOX_PM25,
      .downloadType = 23,
      .sampleType = 24,
      .sampleSizeBytes = 20,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::NOX_INDEX,
                       {.signalType = SignalType::NOX_INDEX,
                        .offset = 6,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 8,
                        .converterFunction = &convertPMV2}}}}},
    {T_RH_HCHO,
     {.dataType = DataType::T_RH_HCHO,
      .downloadType = 13,
      .sampleType = 14,
      .sampleSizeBytes = 6,
      .sampleCountPerPacket = 3,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::HCHO_PARTS_PER_BILLION,
                       {.signalType = SignalType::HCHO_PARTS_PER_BILLION,
                        .offset = 4,
                        .converterFunction = &convertHCHOV1}}}}},
    {T_RH_CO2_VOC_PM25_HCHO,
     {.dataType = DataType::T_RH_CO2_VOC_PM25_HCHO,
      .downloadType = 19,
      .sampleType = 20,
      .sampleSizeBytes = 12,
      .sampleCountPerPacket = 1,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 6,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 8,
                        .converterFunction = &convertPM2p5V1}},
                      {SignalType::HCHO_PARTS_PER_BILLION,
                       {.signalType = SignalType::HCHO_PARTS_PER_BILLION,
                        .offset = 10,
                        .converterFunction = &convertHCHOV1}}}}},
    {T_RH_CO2_VOC_NOX_PM25,
     {.dataType = DataType::T_RH_CO2_VOC_NOX_PM25,
      .downloadType = 25,
      .sampleType = 26,
      .sampleSizeBytes = 12,
      .sampleCountPerPacket = 1,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 6,
                        .converterFunction = &convertSimple}},
                      {SignalType::NOX_INDEX,
                       {.signalType = SignalType::NOX_INDEX,
                        .offset = 8,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 10,
                        .converterFunction = &convertPMV2}}}}},
    {T_RH_CO2_PM25_V2,
     {.dataType = DataType::T_RH_CO2_PM25_V2,
      .downloadType = 27,
      .sampleType = 28,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 6,
                        .converterFunction = &convertPMV2}}}}},
    {T_RH_VOC_PM25_V2,
     {.dataType = DataType::T_RH_VOC_PM25_V2,
      .downloadType = 29,
      .sampleType = 30,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 2,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 6,
                        .converterFunction = &convertPMV2}}}}},
    {T_RH_CO2_VOC_PM25_HCHO_V2,
     {.dataType = DataType::T_RH_CO2_VOC_PM25_HCHO_V2,
      .downloadType = 30,
      .sampleType = 31,
      .sampleSizeBytes = 12,
      .sampleCountPerPacket = 1,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 0,
                        .converterFunction = &convertTemperatureV1}},
                      {SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                       {.signalType = SignalType::RELATIVE_HUMIDITY_PERCENTAGE,
                        .offset = 2,
                        .converterFunction = &convertHumidityV1}},
                      {SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 4,
                        .converterFunction = &convertSimple}},
                      {SignalType::VOC_INDEX,
                       {.signalType = SignalType::VOC_INDEX,
                        .offset = 6,
                        .converterFunction = &convertSimple}},
                      {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                       {.signalType =
                            SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
                        .offset = 8,
                        .converterFunction = &convertPMV2}},
                      {SignalType::HCHO_PARTS_PER_BILLION,
                       {.signalType = SignalType::HCHO_PARTS_PER_BILLION,
                        .offset = 10,
                        .converterFunction = &convertHCHOV1}}}}},
    {PM10_PM25_PM40_PM100,
     {.dataType = DataType::PM10_PM25_PM40_PM100,
      .downloadType = 33,
      .sampleType = 34,
      .sampleSizeBytes = 8,
      .sampleCountPerPacket = 1,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots =
          {{SignalType::PM1P0_MICRO_GRAMM_PER_CUBIC_METER,
            {.signalType = SignalType::PM1P0_MICRO_GRAMM_PER_CUBIC_METER,
             .offset = 0,
             .converterFunction = &convertPMV2}},
           {SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
            {.signalType = SignalType::PM2P5_MICRO_GRAMM_PER_CUBIC_METER,
             .offset = 2,
             .converterFunction = &convertPMV2}},
           {SignalType::PM4P0_MICRO_GRAMM_PER_CUBIC_METER,
            {.signalType = SignalType::PM4P0_MICRO_GRAMM_PER_CUBIC_METER,
             .offset = 4,
             .converterFunction = &convertPMV2}},
           {SignalType::PM10P0_MICRO_GRAMM_PER_CUBIC_METER,
            {.signalType = SignalType::PM10P0_MICRO_GRAMM_PER_CUBIC_METER,
             .offset = 6,
             .converterFunction = &convertPMV2}}}}},
    {CO2_DataType,
     {.dataType = DataType::CO2_DataType,
      .downloadType = 35,
      .sampleType = 36,
      .sampleSizeBytes = 2,
      .sampleCountPerPacket = 1,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::CO2_PARTS_PER_MILLION,
                       {.signalType = SignalType::CO2_PARTS_PER_MILLION,
                        .offset = 0,
                        .converterFunction = &convertSimple}}}}},
    {AV_T,
     {.dataType = DataType::AV_T,
      .downloadType = 37,
      .sampleType = 38,
      .sampleSizeBytes = 4,
      .sampleCountPerPacket = 4,
      .sensirionAdvertisementSampleType = 0,
      .sampleSlots = {{SignalType::VELOCITY_METERS_PER_SECOND,
                       {.signalType = SignalType::VELOCITY_METERS_PER_SECOND,
                        .offset = 0,
                        .converterFunction = &convertVelocityV1}},
                      {SignalType::TEMPERATURE_DEGREES_CELSIUS,
                       {.signalType = SignalType::TEMPERATURE_DEGREES_CELSIUS,
                        .offset = 2,
                        .converterFunction = &convertTemperatureV1}}}}}
    /* Add new SampleConfigs here */
};

// Converter functions
uint16_t convertSimple(float value) {
    return static_cast<uint16_t>(value + 0.5f);
}

uint16_t convertTemperatureV1(float value) {
    return static_cast<uint16_t>((((value + 45) / 175) * 65535) + 0.5f);
}

uint16_t convertHumidityV1(float value) {
    return static_cast<uint16_t>(((value / 100) * 65535) + 0.5f);
}

uint16_t convertHumidityV2(float value) {
    return static_cast<uint16_t>((((value + 6.0) * 65535) / 125.0) + 0.5f);
}

uint16_t convertPM2p5V1(float value) {
    return static_cast<uint16_t>(((value / 1000) * 65535) + 0.5f);
}

uint16_t convertPMV2(float value) {
    return static_cast<uint16_t>((value * 10) + 0.5f);
}

uint16_t convertHCHOV1(float value) {
    return static_cast<uint16_t>((value * 5) + 0.5f);
}

uint16_t convertVelocityV1(float value) {
    return static_cast<uint16_t>((value / 1024) * 65535 + 0.5f);
}
/* Define new converter function here */