#ifndef ModbusMasterCallable_h
#define ModbusMasterCallable_h

/*
Interface to implement for callbleObjs to use  with ModbusMaster::setTransmissionCallable()
*/
class ModbusMasterCallable{
  public:
    // preTransmission callback function; gets called before writing a Modbus message
    virtual void onModbusPreTransmission() = 0;
    // postTransmission callback function; gets called after a Modbus message has been sent
    virtual void onModbusPostTransmission() = 0;
    // idle callback function; gets called during idle time between TX and RX
    virtual void onModbusIdle() = 0;
};

#endif
