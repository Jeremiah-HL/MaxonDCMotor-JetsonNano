#include <iostream>
#include "Definitions.h"
#include "Maxon.h"
#define INITIALVALUE 0

double pi = 3.14;
// typedef unsigned int DWORD;
// typedef unsigned short WORD;
// typedef bool BOOL;
// typedef void* HANDLE;

int main()
{
    char deviceName[] = "EPOS4";
    char protocolStackName[] = "MAXON SERIAL V2";
    char portName[]= "USB0";
    char interfaceName[] = "USB";
    DWORD errorCode = 0;
    HANDLE keyHandle = 0;
    BOOL status = INITIALVALUE;
    int FLAG = 0;
    bool s = true;
    std::string book = "What the Fuck are you doing?";
    // 打开设备
    keyHandle = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName, &errorCode);
    if (!keyHandle) std::cout << "No USB Devices Detected\n";
    else { std::cout << "Connected Successfully\n"; FLAG++; }

    // 配置电机、传感器以及编码器的设备参数
    WORD motorType = MT_DC_MOTOR;
    WORD nodeID = 1;
    status = VCS_SetMotorType(keyHandle, nodeID, motorType, &errorCode);
    if (!status) std::cout << "Motor Set Failed\n";
    else { std::cout << "SET Successfully"; FLAG++; }
    // encoder
    status = VCS_SetSensorType(keyHandle, nodeID, ST_INC_ENCODER2_3CHANNEL, &errorCode);
    BOOL encoderStatus = INITIALVALUE;
    DWORD encoderRevolution = 256;
    encoderStatus = VCS_SetIncEncoderParameter(keyHandle, nodeID, encoderRevolution, 0, &errorCode);
    // sensor 
    BOOL sensorStatus = INITIALVALUE;
    WORD sensorType;
    sensorStatus = VCS_GetSensorType(keyHandle, nodeID, &sensorType, &errorCode);
    // sensorStatus = VCS_SetHallSensorParameter();
    // 配置模式及其参数（configuration with PPM）
    BOOL modeStatus = INITIALVALUE;
    modeStatus = VCS_SetOperationMode(keyHandle, nodeID, OMD_PROFILE_POSITION_MODE, &errorCode);
    

    // 配置状态机器控制电机（operation）


    // 关闭设备
    VCS_CloseDevice(keyHandle, &errorCode);

    
}
