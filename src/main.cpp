#include <TracerRegisters.h>  // empty library for potential future use

#include "HomeAutomation.h"

#define SERIAL_COM Serial2  // RX, TX

#define MAX485_DE 13
#define MAX485_RE_NEG 13

#define RELAY_GPIO 12
#define CPU_ONLINE_CHECK_PIN 14

#define TRACER_INSTANCE TracerRegisters(MAX485_RE_NEG, MAX485_DE, SERIAL_COM);

char* device_name = "Epever Solar Monitor";
char* device_type = "solar_monitor_v1";

TracerRegisters* tracerRegisters;
HomeAutomation automation(device_name, device_type);
bool isPCPowerOn = false;

void handleRequest() {
    char* data;
    tracerRegisters->getRegistersValueInJson(data, isPCPowerOn);

    automation.setContentLength(CONTENT_LENGTH_UNKNOWN);
    automation.sendHeader("Content-Length", (String)(sizeof(data) * sizeof(char)));
    automation.send(200, "text/json", data);
}

void handlePowerOn() {
    // Switch relay on for 2 sec
    digitalWrite(RELAY_GPIO, 1);
    delay(2000);
    digitalWrite(RELAY_GPIO, 0);
    automation.send(200, "text/json", "{\"success\": true}");
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200);
    // Serial.print("STARTING :\n ");

    pinMode(RELAY_GPIO, OUTPUT);
    pinMode(CPU_ONLINE_CHECK_PIN, INPUT);

    tracerRegisters = new TRACER_INSTANCE;

    automation.on("/data", handleRequest);
    automation.on("/power_on", handlePowerOn);
    automation.setup();
}

uint64_t lastUpdateTime = millis();

void loop() {
    automation.networkLoop();
    if (lastUpdateTime < millis()) {
        isPCPowerOn = digitalRead(CPU_ONLINE_CHECK_PIN) > 0;
        Serial.println("PC Power");
        Serial.println(isPCPowerOn);
        tracerRegisters->updateModbusInformation();
        lastUpdateTime = millis() + 2000;
    }
}
