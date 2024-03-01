#include <iostream>
#include "Definitions.h"
#include "Maxon.h"
using namespace std;

unsigned short MaxonDCMotor::Motor::deviceNum = 0;
string MaxonDCMotor::Motor::deviceName = "EPOS4";
string MaxonDCMotor::Motor::protocolStackName = "MAXON SERIAL V2";
string MaxonDCMotor::Motor::interfaceName = "USB";

MaxonDCMotor::MaxonDCMotor(BOOL Default) {
    m_keyHandle = NULL;
    m_NodeId = deviceNum;
    m_portName = (interfaceName == "USB" ? "USB" : "COM") + to_string(deviceNum);
    m_baudrate = 1000000;
    m_operationMode = OMD_HOMING_MODE;
    m_ifDefault = 1;
    deviceNum++;
    stdMsgPrintOut("Default Parameters Set Successfully!", *this);
}

MaxonDCMotor::MaxonDCMotor(char* portName, char* deviceName, char* protocolStackName, char* interfaceName, int operationMode) {
    HANDLE keyHandle = 0;
    m_NodeId = deviceNum + 1;
    keyHandle = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName, &errorCode);
    cout << "Creating a maxon DC motor object..." << endl;
    if (errorCode == 0){
        unsigned int lBaudrate = 0;
        unsigned int lTimeout = 0;

        if (VCS_GetProtocolStackSettings(keyHandle, &lBaudrate, &lTimeout, &errorCode) &&
            VCS_SetProtocolStackSettings(keyHandle, m_baudrate, lTimeout, &errorCode) &&
            VCS_GetProtocolStackSettings(keyHandle, &lBaudrate, &lTimeout, &errorCode)){
            m_keyHandle = keyHandle;
            m_portName = portName;
            m_baudrate = lBaudrate;

            stdMsgPrintOut("Created Successfully", *this);
            if (VCS_SetOperationMode(m_keyHandle, m_NodeId, m_operationMode, &errorCode)) {
                stdMsgPrintOut("Mode Setting", *this);
                cout << "Set Operation Mode : " << m_operationMode << endl;
            }
            deviceNum++;
        }
    }
    else {
        m_keyHandle = 0;
        cout << "Failed to open, Check your device or other parameters" << endl;
        errorCodePrintOut(errorCode, *this);
    }
}

MaxonDCMotor::~MaxonDCMotor() { 
    deviceNum--; 
    VCS_CloseDevice(m_keyHandle, &errorCode);
    stdMsgPrintOut("Closing...", *this);
}


BOOL MaxonDCMotor::ifOpen() {
    stdMsgPrintOut("Haven't Opened This Motor...", *this);
    return false;
}


void MaxonDCMotor::openDevice() {
    char deviceNameArray[40];
    char protocolStackNameArray[40];
    char interfaceNameArray[40];
    char m_portNameArray[40];

    strcpy(deviceNameArray, deviceName.c_str());
    strcpy(protocolStackNameArray, protocolStackName.c_str());
    strcpy(interfaceNameArray, interfaceName.c_str());
    strcpy(m_portNameArray, m_portName.c_str());

    m_keyHandle = VCS_OpenDevice(deviceNameArray, protocolStackNameArray, interfaceNameArray, m_portNameArray, &errorCode);
    if (!m_keyHandle) {
        stdMsgPrintOut("Failed to Open This Motor...", *this);
        errorCodePrintOut(errorCode, *this);
    }
}

BOOL MaxonDCMotor::setOperationMode(char operationMode) {
    if (m_keyHandle == NULL) return ifOpen();
    if (VCS_SetOperationMode(m_keyHandle, m_NodeId, operationMode, &errorCode)) {
        m_operationMode = operationMode;
        stdMsgPrintOut("Operation Set Successfully!", *this);
        return true;
    }
    stdMsgPrintOut("Failed to Set New Operation!", *this);
    errorCodePrintOut(errorCode, *this);
    return false;
}

BOOL MaxonDCMotor::Enable() {
    if (m_keyHandle == NULL) return ifOpen();
    if (VCS_SetEnableState(m_keyHandle, m_NodeId, &errorCode)) {
        stdMsgPrintOut("Enabled...", *this);
        return true;
    }
    stdMsgPrintOut("Failed to Enable!", *this);
    errorCodePrintOut(errorCode, *this);
    return false;
}

BOOL MaxonDCMotor::Disable() {
    if (m_keyHandle == NULL) return ifOpen();
    if (VCS_SetDisableState(m_keyHandle, m_NodeId, &errorCode)) {
        stdMsgPrintOut("Disabled...", *this);
        return true;
    }
    stdMsgPrintOut("Failed to Disabled...", *this);
    errorCodePrintOut(errorCode, *this);
    return false;
}

void Motor::setNodeId(WORD nodeId){
    if (!(m_keyHandle == NULL)) stdMsgPrintOut("already opened or auto-opened!", *this);
    else m_NodeId = nodeId;
}

string Motor::getPortName() { return m_portName; }
WORD Motor::getNodeId() { return m_NodeId; }
