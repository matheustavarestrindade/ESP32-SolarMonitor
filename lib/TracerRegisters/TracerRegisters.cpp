#include "TracerRegisters.h"

#include <sstream>
inline const std::string BoolToString(bool b) {
    std::string value(b ? "true" : "false");
    return value;
}

TracerRegisters::TracerRegisters(uint8_t MAX485_RE_NEG, uint8_t MAX485_DE, Stream& serial) {
    this->variableValues = new float[SolarTracerVariables::VARIABLES_COUNT + 1]();
    this->max485_re_neg = MAX485_RE_NEG;
    this->max485_de = MAX485_DE;

    pinMode(this->max485_re_neg, OUTPUT);
    pinMode(this->max485_de, OUTPUT);

    digitalWrite(this->max485_re_neg, 0);
    digitalWrite(this->max485_de, 0);

    // set this instance as the callback receiver
    this->node.setTransmissionCallable(this);
    this->node.setResponseTimeout(2000);
    this->node.begin(1, serial);
}

void TracerRegisters::getRegistersValueInJson(char*& loadValues, bool PC_ONLINE_STATUS) {
    std::string jsonString;
    jsonString += "{";
    jsonString += "\"PV_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::PV_VOLTAGE]) + ",";
    jsonString += "\"PV_POWER\":" + to_string(this->variableValues[SolarTracerVariables::PV_POWER]) + ",";
    jsonString += "\"PV_CURRENT\":" + to_string(this->variableValues[SolarTracerVariables::PV_CURRENT]) + ",";
    jsonString += "\"LOAD_CURRENT\":" + to_string(this->variableValues[SolarTracerVariables::LOAD_CURRENT]) + ",";
    jsonString += "\"LOAD_POWER\":" + to_string(this->variableValues[SolarTracerVariables::LOAD_POWER]) + ",";
    jsonString += "\"BATTERY_STATUS\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_STATUS]) + ",";
    jsonString += "\"BATERRY_REAL_RATED_POWER\": \"Futher implementation required\",";  //+ to_string(this->variableValues[SolarTracerVariables::BATERRY_REAL_RATED_POWER]) + ",";
    jsonString += "\"BATTERY_TYPE\": \"Futher implementation required\",";              // + to_string(this->variableValues[SolarTracerVariables::BATTERY_TYPE]) + " ,";
    jsonString += "\"BATTERY_CAPACITY\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_CAPACITY]) + ",";
    jsonString += "\"BATTERY_TEMP\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_TEMP]) + ",";
    jsonString += "\"BATTERY_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_SOC\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_SOC]) + ",";
    jsonString += "\"BATTERY_CHARGE_CURRENT\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_CHARGE_CURRENT]) + ",";
    jsonString += "\"BATTERY_CHARGE_POWER\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_CHARGE_POWER]) + ",";
    jsonString += "\"BATTERY_OVERALL_CURRENT\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_OVERALL_CURRENT]) + ",";
    jsonString += "\"BATTERY_BOOST_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_BOOST_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_EQUALIZATION_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_EQUALIZATION_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_FLOAT_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_FLOAT_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_FLOAT_MIN_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_FLOAT_MIN_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_CHARGING_LIMIT_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_CHARGING_LIMIT_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_DISCHARGING_LIMIT_VOLTAGE\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_DISCHARGING_LIMIT_VOLTAGE]) + ",";
    jsonString += "\"BATTERY_LOW_VOLTAGE_DISCONNECT\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_LOW_VOLTAGE_DISCONNECT]) + ",";
    jsonString += "\"BATTERY_LOW_VOLTAGE_RECONNECT\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_LOW_VOLTAGE_RECONNECT]) + ",";
    jsonString += "\"BATTERY_OVER_VOLTAGE_DISCONNECT\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_OVER_VOLTAGE_DISCONNECT]) + ",";
    jsonString += "\"BATTERY_OVER_VOLTAGE_RECONNECT\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_OVER_VOLTAGE_RECONNECT]) + ",";
    jsonString += "\"BATTERY_UNDER_VOLTAGE_SET\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_UNDER_VOLTAGE_SET]) + ",";
    jsonString += "\"BATTERY_UNDER_VOLTAGE_RESET\":" + to_string(this->variableValues[SolarTracerVariables::BATTERY_UNDER_VOLTAGE_RESET]) + ",";
    jsonString += "\"CONTROLLER_TEMP\":" + to_string(this->variableValues[SolarTracerVariables::CONTROLLER_TEMP]) + ",";
    jsonString += "\"REALTIME_CLOCK\":" + to_string(this->variableValues[SolarTracerVariables::REALTIME_CLOCK]) + ",";
    jsonString += "\"LOAD_FORCE_ONOFF\":" + to_string(this->variableValues[SolarTracerVariables::LOAD_FORCE_ONOFF]) + ",";
    jsonString += "\"LOAD_MANUAL_ONOFF\":" + to_string(this->variableValues[SolarTracerVariables::LOAD_MANUAL_ONOFF]) + ",";
    jsonString += "\"REMOTE_BATTERY_TEMP\":" + to_string(this->variableValues[SolarTracerVariables::REMOTE_BATTERY_TEMP]) + ",";
    jsonString += "\"GENERATED_ENERGY_TODAY\":" + to_string(this->variableValues[SolarTracerVariables::GENERATED_ENERGY_TODAY]) + ",";
    jsonString += "\"GENERATED_ENERGY_MONTH\":" + to_string(this->variableValues[SolarTracerVariables::GENERATED_ENERGY_MONTH]) + ",";
    jsonString += "\"GENERATED_ENERGY_YEAR\":" + to_string(this->variableValues[SolarTracerVariables::GENERATED_ENERGY_YEAR]) + ",";
    jsonString += "\"GENERATED_ENERGY_TOTAL\":" + to_string(this->variableValues[SolarTracerVariables::GENERATED_ENERGY_TOTAL]) + ",";
    jsonString += "\"MAXIMUM_PV_VOLTAGE_TODAY\":" + to_string(this->variableValues[SolarTracerVariables::MAXIMUM_PV_VOLTAGE_TODAY]) + ",";
    jsonString += "\"MINIMUM_PV_VOLTAGE_TODAY\":" + to_string(this->variableValues[SolarTracerVariables::MINIMUM_PV_VOLTAGE_TODAY]) + ",";
    jsonString += "\"MAXIMUM_BATTERY_VOLTAGE_TODAY\":" + to_string(this->variableValues[SolarTracerVariables::MAXIMUM_BATTERY_VOLTAGE_TODAY]) + ",";
    jsonString += "\"MINIMUM_BATTERY_VOLTAGE_TODAY\":" + to_string(this->variableValues[SolarTracerVariables::MINIMUM_BATTERY_VOLTAGE_TODAY]) + ",";
    jsonString += "\"CHARGING_EQUIPMENT_STATUS\":" + to_string(this->variableValues[SolarTracerVariables::CHARGING_EQUIPMENT_STATUS]) + ",";
    jsonString += "\"DISCHARGING_EQUIPMENT_STATUS\":" + to_string(this->variableValues[SolarTracerVariables::DISCHARGING_EQUIPMENT_STATUS]) + ",";
    jsonString += "\"CHARGING_DEVICE_ONOFF\":" + to_string(this->variableValues[SolarTracerVariables::CHARGING_DEVICE_ONOFF]) + ",";
    jsonString += "\"HEATSINK_TEMP\":" + to_string(this->variableValues[SolarTracerVariables::HEATSINK_TEMP]) + ",";
    jsonString += "\"PC_ONLINE_STATUS\":" + BoolToString(PC_ONLINE_STATUS);
    jsonString += "}";
    loadValues = new char[jsonString.length() + 1];
    strcpy(loadValues, jsonString.c_str());
}

std::string TracerRegisters::to_string(float f) {
    std::stringstream ss;
    ss << f;
    std::string finalString = ss.str();
    return finalString;
}

void TracerRegisters::updateModbusInformation() {
    if (this->connectionStablished == false) {
        this->connectionStablished = testConn(0x0006);
        return;
    }

    switch (this->current_update) {
        case 0:
            AddressRegistry_3100();
            break;
        case 1:
            AddressRegistry_311A();
            break;
        case 2:
            AddressRegistry_331B();
            break;
        case 3:
            AddressRegistry_9003();
            break;
        case 4:
            updateStats();
            break;
        case 6:
            this->current_update = 0;
            return;
    }
    this->current_update += 1;
}

void TracerRegisters::AddressRegistry_3100() {
    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_PV_VOLTAGE, 16);
    if (this->result != this->node.ku8MBSuccess) {
        Serial.println("Failed to get registry 3100");
        Serial.println(this->result);
        Serial.println(this->node.ku8MBSuccess);
        return;
    }

    this->variableValues[SolarTracerVariables::PV_VOLTAGE] = this->node.getResponseBuffer(0x00) / 100.0f;
    this->variableValues[SolarTracerVariables::PV_CURRENT] = this->node.getResponseBuffer(0x01) / 100.0f;
    this->variableValues[SolarTracerVariables::PV_POWER] = (this->node.getResponseBuffer(0x02) | this->node.getResponseBuffer(0x03) << 16) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_VOLTAGE] = this->node.getResponseBuffer(0x04) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_CHARGE_CURRENT] = this->node.getResponseBuffer(0x05) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_CHARGE_POWER] = (this->node.getResponseBuffer(0x06) | this->node.getResponseBuffer(0x07) << 16) / 100.0f;
    this->variableValues[SolarTracerVariables::LOAD_CURRENT] = this->node.getResponseBuffer(0x0D) / 100.0f;
    this->variableValues[SolarTracerVariables::LOAD_POWER] = (this->node.getResponseBuffer(0x0E) | this->node.getResponseBuffer(0x02) << 16) / 100.0f;
}

void TracerRegisters::AddressRegistry_311A() {
    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_BATT_SOC, 2);
    if (this->result != this->node.ku8MBSuccess) {
        Serial.println("ERROR GETTING REGISTRY 311A");
        Serial.println(this->result);
        return;
    }

    this->variableValues[SolarTracerVariables::BATTERY_SOC] = this->node.getResponseBuffer(0x00) / 1.0f;
    this->variableValues[SolarTracerVariables::REMOTE_BATTERY_TEMP] = this->node.getResponseBuffer(0x01) / 100.0f;

    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_BATT_REAL_RATED_POWER, 1);
    if (this->result != this->node.ku8MBSuccess) {
        Serial.println("ERROR GETTING REGISTRY 311A RATTED");
        Serial.println(this->result);
        return;
    }

    this->variableValues[SolarTracerVariables::BATERRY_REAL_RATED_POWER] = this->node.getResponseBuffer(0x00) / 100.0f;
}

void TracerRegisters::AddressRegistry_3200() {
    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_CHARGING_EQUIPMENT_STATUS, 16);
    if (this->result != this->node.ku8MBSuccess) {
        return;
    }

    this->variableValues[SolarTracerVariables::BATTERY_STATUS] = this->node.getResponseBuffer(0x00);
    this->variableValues[SolarTracerVariables::CHARGING_EQUIPMENT_STATUS] = this->node.getResponseBuffer(0x01);
    this->variableValues[SolarTracerVariables::DISCHARGING_EQUIPMENT_STATUS] = this->node.getResponseBuffer(0x02);
}

void TracerRegisters::AddressRegistry_331B() {
    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_BATTERY_OVERALL_CURRENT, 16);
    if (this->result != this->node.ku8MBSuccess) {
        return;
    }
    this->variableValues[SolarTracerVariables::BATTERY_OVERALL_CURRENT] = (this->node.getResponseBuffer(0x00) | this->node.getResponseBuffer(0x01) << 16) / 100.0f;
}

void TracerRegisters::AddressRegistry_9003() {
    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_HIGH_VOLTAGE_DISCONNECT, 12);
    if (this->result != this->node.ku8MBSuccess) {
        Serial.println("Error getting battery voltage");
        Serial.println(this->result);
        return;
    }

    this->variableValues[SolarTracerVariables::BATTERY_OVER_VOLTAGE_DISCONNECT] = this->node.getResponseBuffer(0x00) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_CHARGING_LIMIT_VOLTAGE] = this->node.getResponseBuffer(0x01) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_OVER_VOLTAGE_RECONNECT] = this->node.getResponseBuffer(0x02) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_EQUALIZATION_VOLTAGE] = this->node.getResponseBuffer(0x03) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_BOOST_VOLTAGE] = this->node.getResponseBuffer(0x04) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_FLOAT_VOLTAGE] = this->node.getResponseBuffer(0x05) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_FLOAT_MIN_VOLTAGE] = this->node.getResponseBuffer(0x06) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_LOW_VOLTAGE_RECONNECT] = this->node.getResponseBuffer(0x07) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_UNDER_VOLTAGE_RESET] = this->node.getResponseBuffer(0x08) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_UNDER_VOLTAGE_SET] = this->node.getResponseBuffer(0x09) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_LOW_VOLTAGE_DISCONNECT] = this->node.getResponseBuffer(0x0A) / 100.0f;
    this->variableValues[SolarTracerVariables::BATTERY_DISCHARGING_LIMIT_VOLTAGE] = this->node.getResponseBuffer(0x0B) / 100.0f;

    // this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_BATTERY_TYPE, 2);
    // if (this->result != this->node.ku8MBSuccess) {
    //     Serial.println("Error getting battery type");
    //     Serial.println(this->result);
    //     return;
    // }

    // this->variableValues[SolarTracerVariables::BATTERY_TYPE] = this->node.getResponseBuffer(0x00);
    // this->variableValues[SolarTracerVariables::BATTERY_CAPACITY] = this->node.getResponseBuffer(0x01);
}

void TracerRegisters::updateStats() {
    this->result = this->node.readInputRegisters(TracerRegisterType::MODBUS_ADDRESS_STAT_MAX_PV_VOLTAGE_TODAY, 12);
    if (this->result != this->node.ku8MBSuccess) {
        return;
    }

    this->variableValues[SolarTracerVariables::MAXIMUM_PV_VOLTAGE_TODAY] = this->node.getResponseBuffer(0x00) / 100.0f;
    this->variableValues[SolarTracerVariables::MINIMUM_PV_VOLTAGE_TODAY] = this->node.getResponseBuffer(0x01) / 100.0f;
    this->variableValues[SolarTracerVariables::MAXIMUM_BATTERY_VOLTAGE_TODAY] = this->node.getResponseBuffer(0x02) / 100.0f;
    this->variableValues[SolarTracerVariables::MINIMUM_BATTERY_VOLTAGE_TODAY] = this->node.getResponseBuffer(0x03) / 100.0f;

    this->variableValues[SolarTracerVariables::GENERATED_ENERGY_TODAY] = (this->node.getResponseBuffer(12) | this->node.getResponseBuffer(13) << 16) / 100.0f;
    this->variableValues[SolarTracerVariables::GENERATED_ENERGY_MONTH] = (this->node.getResponseBuffer(14) | this->node.getResponseBuffer(15) << 16) / 100.0f;
    this->variableValues[SolarTracerVariables::GENERATED_ENERGY_YEAR] = (this->node.getResponseBuffer(16) | this->node.getResponseBuffer(17) << 16) / 100.0f;
    this->variableValues[SolarTracerVariables::GENERATED_ENERGY_TOTAL] = (this->node.getResponseBuffer(18) | this->node.getResponseBuffer(19) << 16) / 100.0f;
}

void TracerRegisters::onModbusPreTransmission() {
    digitalWrite(this->max485_re_neg, 1);
    digitalWrite(this->max485_de, 1);
}

void TracerRegisters::onModbusIdle() {
    // nothing to do here!
}

void TracerRegisters::onModbusPostTransmission() {
    digitalWrite(this->max485_re_neg, 0);
    digitalWrite(this->max485_de, 0);
}

bool TracerRegisters::testConn(uint16_t address) {
    this->result = this->node.readCoils(address, 1);

    bool success = this->result == this->node.ku8MBSuccess;
    if (success) {
        return true;
    }
    return false;
}