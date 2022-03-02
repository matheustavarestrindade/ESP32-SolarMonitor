#include <TracerRegisters.h>  // empty library for potential future use

#define SERIAL_COM Serial2  // RX, TX

#define MAX485_DE 13
#define MAX485_RE_NEG 13

#define TRACER_INSTANCE TracerRegisters(MAX485_RE_NEG, MAX485_DE, SERIAL_COM);

TracerRegisters *tracerRegisters;
void setup() {
    Serial.begin(115200);
    Serial.print("STARTING :\n ");

    tracerRegisters = new TRACER_INSTANCE;
}

void loop() {
    // uint8_t is short hand for a byte or an integer of length 8 bits
    tracerRegisters->updateModbusInformation();

    Serial.print("Getting values:\n ");
    Serial.print(tracerRegisters->getRegistersValueInJson());

    delay(1000);
}
