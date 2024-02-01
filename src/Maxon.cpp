#include <iostream>
#include "Definitions.h"
#include "Maxon.h"
using namespace std;

MaxonDCMotor::MaxonDCMotor(BOOL Default) {
    m_keyHandle = NULL;
    m_NodeId = deviceNum;
    m_portName = (interfaceName == "USB" ? "USB" : "COM") + to_string(deviceNum);
    m_baudrate = 1000000;
    m_operationMode = OMD_HOMING_MODE;
    m_ifDefault = 1;
    deviceNum++;
    cout << "[Motor Node id : " << this->m_NodeId << "]: Default Parameters Set Successfully!" << endl;
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

            cout << "====================" << endl;
            cout << "Created Successfully" << endl;
            cout << "Port Name : " << m_portName << endl;
            cout << "Node ID   : " << m_NodeId << endl;
            cout << "Baudrate  : " << m_baudrate << endl;
            if (VCS_SetOperationMode(m_keyHandle, m_NodeId, m_operationMode, &errorCode))cout << "Set Operation Mode : " << m_operationMode << endl;
            cout << "====================" << endl;
            deviceNum++;
        }
    }
    else {
        m_keyHandle = 0;
        cout << "Failed to create, Check your device or other parameters" << endl;
    }
}

MaxonDCMotor::~MaxonDCMotor() { 
    deviceNum--; 
    VCS_CloseDevice(m_keyHandle, &errorCode);
    cout << "[Motor Node id : " << this->m_NodeId << "]: Closing... Error Code : " << errorCode << endl;
}


BOOL MaxonDCMotor::ifOpen() {
    cout << "[Motor Node id : " << this->m_NodeId << "]: Haven't Opened This Motor..." << endl;
    return false;
}


void MaxonDCMotor::openMotor() {
    char deviceNameArray[40];
    char protocolStackNameArray[40];
    char interfaceNameArray[40];
    char m_portNameArray[40];

    strcpy(deviceNameArray, deviceName.c_str());
    strcpy(protocolStackNameArray, protocolStackName.c_str());
    strcpy(interfaceNameArray, interfaceName.c_str());
    strcpy(m_portNameArray, m_portName.c_str());

    m_keyHandle = VCS_OpenDevice(deviceNameArray, protocolStackNameArray, interfaceNameArray, m_portNameArray, &errorCode);
    if (!m_keyHandle)  cout << "[Motor Node id : " << this->m_NodeId << "]: Failed to Open This Motor..." << endl;
}

BOOL MaxonDCMotor::setOperationMode(char operationMode) {
    if (m_keyHandle == NULL) return ifOpen();
    if (VCS_SetOperationMode(m_keyHandle, m_NodeId, operationMode, &errorCode)) {
        m_operationMode = operationMode;
        cout << "[Motor Node id : " << this->m_NodeId << "]: Operation Set Successfully!" << endl;
        return true;
    }
    cout << "[Motor Node id : " << this->m_NodeId << "]: Failed to Set New Operation!" << endl;
    return false;
}

BOOL MaxonDCMotor::Enable() {
    if (m_keyHandle == NULL) return ifOpen();
    if (VCS_SetEnableState(m_keyHandle, m_NodeId, &errorCode)) {
        cout << "[Motor Node id : " << this->m_NodeId << "]: Enabled..." << endl;
        return true;
    }
    cout << "[Motor Node id : " << this->m_NodeId << "]: Failed to Enable!" << endl;
    return false;
}

BOOL MaxonDCMotor::Disable() {
    if (m_keyHandle == NULL) return ifOpen();
    if (VCS_SetDisableState(m_keyHandle, m_NodeId, &errorCode)) {
        cout << "Maxon DC Motor Node : " << m_NodeId << " Disabled..." << endl;
        return true;
    }
    cout << "Maxon DC Motor Node : " << m_NodeId << " Failed to Disable!" << endl;
    return false;
}