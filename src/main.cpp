#include <TracerRegisters.h>  // empty library for potential future use
#include <WebServer.h>
#include <WiFi.h>

const char* ssid = "Rede trindade";
const char* password = "cpmn2018";

#define SERIAL_COM Serial2  // RX, TX
#define MAX485_DE 13
#define MAX485_RE_NEG 13
#define NETWORK_PORT 7858
#define RELAY_GPIO 12

#define TRACER_INSTANCE TracerRegisters(MAX485_RE_NEG, MAX485_DE, SERIAL_COM);

TracerRegisters* tracerRegisters;
WebServer server(NETWORK_PORT);
std::string convertToString(char* a, int size) {
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void handleRequest() {
    char* data;
    tracerRegisters->getRegistersValueInJson(data);
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.sendHeader("Content-Length", (String)(sizeof(data) * sizeof(char)));
    server.send(200, "text/json", data);
}

bool isPoweringPC = false;

void handlePowerOn() {
    // Switch relay on for 2 sec
    digitalWrite(RELAY_GPIO, 1);
    delay(2000);
    digitalWrite(RELAY_GPIO, 0);
    server.send(200, "text/json", "{\"success\": true}");
}

void handleDeveceInformation() {
    server.send(200, "text/json", "{\"success\": true}");
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(115200);
    // Serial.print("STARTING :\n ");

    pinMode(RELAY_GPIO, OUTPUT);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();

    tracerRegisters = new TRACER_INSTANCE;

    server.on("/", handleRequest);
    server.on("/power_on", handlePowerOn);

    server.begin();
}

uint64_t lastUpdateTime = millis();

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        ESP.restart();
        return;
    }

    if (lastUpdateTime < millis()) {
        tracerRegisters->updateModbusInformation();
        lastUpdateTime = millis() + 2000;
    }
    server.handleClient();
}
