/* ============================================================================
 * Name            : main.cpp
 * Author          : Jeremiah_HL
 * Version         : 1.0
 * CopyRight       : None
 * Description     : Controling Sinus Endoscope Robot
 * ============================================================================ */

#include <iostream>
#include "Definitions.h"
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/time.h>
#include "JetsonGPIO.h"

using namespace std;
using namespace GPIO;

// define HANDLE and BOOL in case that Linux Lib not contain these two data type.
typedef void* HANDLE;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned long DWORD;

char deviceName[] = "EPOS4";
char protocolStackName[] = "MAXON SERIAL V2";
char interfaceName[] = "USB";
char portName1[] = "USB0";
char portName2[] = "USB1";
char portName3[] = "USB2";
char portName4[] = "USB3";
long Velocity = 1000;

unsigned int errorCode = 0;
WORD motorType = MT_DC_MOTOR;
WORD nodeId1 = 1;
WORD nodeId2 = 2;
WORD nodeId3 = 3;
WORD nodeId4 = 4;
BOOL status[5] = {0, 0, 0, 0, 0};

char g_mode = OMD_PROFILE_POSITION_MODE;
char g_mode_r = OMD_PROFILE_VELOCITY_MODE;
DWORD profileVelocity = 1500;
DWORD profileAccerleration = 1000;
DWORD profileDecerleration = 1000;
long MaxPosition = 5000000;
long initialPosition = 0;
long MinPosition = -1*MaxPosition;

int J1X_R = 5;
int J1X_L = 6;
int J1Y_R = 13;
int J1Y_L = 19;
int J2X_R = 26;
int J2X_L = 16;
int J2Y_R = 20;
int J2Y_L = 21;
int key1  = 23;
int key2  = 24;

void ResetStatus() { status[0] = status[1] = status[2] = status[3] = status[4] = 0; }

int main(){

    // initializing four pins
    GPIO::setmode(GPIO::BCM);
    GPIO::setwarnings(false);

    // set pin mode
    GPIO::setup({J1X_R, J1X_L, J2X_R, J2X_L,
                 J1Y_R, J1Y_L, J2Y_R, J2Y_L,
                 key1 , key2}, GPIO::IN);

    // initializing maxon DC motors and drivers
    
    void* keyHandle1;
    void* keyHandle2;
    void* keyHandle3;
    void* keyHandle4;

    keyHandle1 = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName1, &errorCode);
    keyHandle2 = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName2, &errorCode);
    keyHandle3 = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName3, &errorCode);
    keyHandle4 = VCS_OpenDevice(deviceName, protocolStackName, interfaceName, portName4, &errorCode);
    std::cout << (keyHandle1 && keyHandle2 && keyHandle3 && keyHandle4 ? "1 Succeeded" : "1 Failed") << std::endl;
    std::cout << status[1] << " | " << status[0] << " | " << status[2] << " | " << status[3] << " | " << errorCode << endl;
    ResetStatus();

    status[0] = VCS_SetMotorType(keyHandle1, nodeId1, MT_DC_MOTOR, &errorCode);
    status[1] = VCS_SetMotorType(keyHandle2, nodeId2, MT_DC_MOTOR, &errorCode);
    status[3] = VCS_SetMotorType(keyHandle3, nodeId3, MT_DC_MOTOR, &errorCode);
    status[4] = VCS_SetMotorType(keyHandle4, nodeId4, MT_DC_MOTOR, &errorCode);
    std::cout << ((status[0] && status[1] && status[3] && status[4]) ? "2 Succeeded" : "2 Failed") << endl;
    std::cout << status[1] << " | " << status[0] << " | " << status[3] << " | " << status[3] << " | " << errorCode << endl;
    ResetStatus();

    status[0] = VCS_SetOperationMode(keyHandle1, nodeId1, g_mode, &errorCode);
    status[1] = VCS_SetOperationMode(keyHandle2, nodeId2, g_mode, &errorCode);
    status[3] = VCS_SetOperationMode(keyHandle3, nodeId3, g_mode, &errorCode);
    status[4] = VCS_SetOperationMode(keyHandle4, nodeId4, g_mode, &errorCode);
    std::cout << ((status[0] && status[1] && status[3] && status[4]) ? "3 Succeeded" : "3 Failed") << endl;
    std::cout << status[1] << " | " << status[0] << " | " << status[3] << " | " << status[3] << " | " << errorCode << endl;
    ResetStatus();

    status[0] = VCS_SetPositionProfile(keyHandle1, nodeId1, profileVelocity, profileAccerleration, profileDecerleration, &errorCode);
    status[1] = VCS_SetPositionProfile(keyHandle2, nodeId2, profileVelocity, profileAccerleration, profileDecerleration, &errorCode);
    status[3] = VCS_SetPositionProfile(keyHandle3, nodeId3, profileVelocity, profileAccerleration, profileDecerleration, &errorCode);
    status[4] = VCS_SetPositionProfile(keyHandle4, nodeId4, profileVelocity, profileAccerleration, profileDecerleration, &errorCode);
    std::cout << ((status[0] && status[1] && status[3] && status[4]) ? "4 Succeeded" : "4 Failed") << endl;
    std::cout << status[1] << " | " << status[0] << " | " << status[3] << " | " << status[3] << " | " << errorCode << endl;
    ResetStatus();

    status[0] = VCS_ActivateProfilePositionMode(keyHandle1, nodeId1, &errorCode);
    status[1] = VCS_ActivateProfilePositionMode(keyHandle2, nodeId2, &errorCode);
    status[3] = VCS_ActivateProfilePositionMode(keyHandle3, nodeId3, &errorCode);
    status[4] = VCS_ActivateProfilePositionMode(keyHandle4, nodeId4, &errorCode);
    std::cout << ((status[0] && status[1] && status[3] && status[4]) ? "5 Succeeded" : "5 Failed") << endl;
    std::cout << status[1] << " | " << status[0] << " | " << status[3] << " | " << status[3] << " | " << errorCode << endl;
    ResetStatus();

    status[0] = VCS_SetEnableState(keyHandle2, nodeId2, &errorCode);
    status[0] = VCS_SetEnableState(keyHandle1, nodeId1, &errorCode);
    status[0] = VCS_SetEnableState(keyHandle3, nodeId3, &errorCode);
    status[0] = VCS_SetEnableState(keyHandle4, nodeId4, &errorCode);

    status[1] = VCS_MoveToPosition(keyHandle2, nodeId2, initialPosition, 1, true, &errorCode);
    status[1] = VCS_MoveToPosition(keyHandle1, nodeId1, initialPosition, 1, true, &errorCode);
    status[1] = VCS_MoveToPosition(keyHandle3, nodeId3, initialPosition, 1, true, &errorCode);
    status[1] = VCS_MoveToPosition(keyHandle4, nodeId4, initialPosition, 1, true, &errorCode);
    sleep(5);
    status[2] = VCS_SetDisableState(keyHandle2, nodeId2, &errorCode);
    status[2] = VCS_SetDisableState(keyHandle1, nodeId1, &errorCode);
    status[2] = VCS_SetDisableState(keyHandle3, nodeId3, &errorCode);
    status[2] = VCS_SetDisableState(keyHandle4, nodeId4, &errorCode);
    std::cout << ((status[0] && status[1] && status[2] ) ? "Test Successfully" : "Failed") << endl;
    
    status[0] = VCS_SetOperationMode(keyHandle1, nodeId1, OMD_PROFILE_VELOCITY_MODE, &errorCode);
    status[1] = VCS_SetOperationMode(keyHandle2, nodeId2, OMD_PROFILE_VELOCITY_MODE, &errorCode);
    status[3] = VCS_SetOperationMode(keyHandle3, nodeId3, OMD_PROFILE_VELOCITY_MODE, &errorCode);
    status[4] = VCS_SetOperationMode(keyHandle4, nodeId4, OMD_PROFILE_VELOCITY_MODE, &errorCode);

    status[0] = VCS_SetVelocityProfile(keyHandle1, nodeId1, profileAccerleration, profileDecerleration, &errorCode);
    status[1] = VCS_SetVelocityProfile(keyHandle2, nodeId2, profileAccerleration, profileDecerleration, &errorCode);
    status[3] = VCS_SetVelocityProfile(keyHandle3, nodeId3, profileAccerleration, profileDecerleration, &errorCode);
    status[4] = VCS_SetVelocityProfile(keyHandle4, nodeId4, profileAccerleration, profileDecerleration, &errorCode);

    status[0] = VCS_ActivateProfileVelocityMode(keyHandle1, nodeId1, &errorCode);
    status[1] = VCS_ActivateProfileVelocityMode(keyHandle2, nodeId2, &errorCode);
    status[3] = VCS_ActivateProfileVelocityMode(keyHandle3, nodeId3, &errorCode);
    status[4] = VCS_ActivateProfileVelocityMode(keyHandle4, nodeId4, &errorCode);
    std::cout << ((status[0] && status[1] && status[3] && status[4]) ? "Set Mode Succeeded" : "Set Mode Failed") << endl;
    std::cout << status[1] << " | " << status[0] << " | " << status[3] << " | " << status[3] << " | " << errorCode << endl;
    ResetStatus();
    
    bool XRFlag1 = 1;
    bool XLFlag1 = 1;
    bool YRFlag1 = 1;
    bool YLFlag1 = 1;
    bool XRFlag2 = 1;
    bool XLFlag2 = 1;
    bool YRFlag2 = 1;
    bool YLFlag2 = 1;

    while ( (input(key1) || input(key2)) ) {
        // std::cout << "XFlag = " << XFlag << " | " << "YFlag = " << YFlag << endl;
        // std::cout << "J2X_R = " << input(J2X_R) << " | " << "J2X_L = " << input(J2X_L) << endl;  
        // std::cout << "J2Y_R = " << input(J2Y_R) << " | " << "J2Y_L = " << input(J2Y_L) << endl;  
        
        // axis 1
        if ( input(J1X_R) && XRFlag1 ) {
            status[0] = VCS_SetEnableState(keyHandle3, nodeId3, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle3, nodeId3, Velocity, &errorCode);
            std::cout << "No.3 motor is running +" << endl;
            XRFlag1 = false;
        } 
        if (!input(J1X_R) && !XRFlag1) { VCS_SetDisableState(keyHandle3, nodeId3, &errorCode); XRFlag1 = true; }

        if ( input(J1X_L) && XLFlag1 ) {
            status[0] = VCS_SetEnableState(keyHandle3, nodeId3, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle3, nodeId3, -1*Velocity, &errorCode);
            std::cout << "No.3 motor is running +" << endl;
            XLFlag1 = false;
        } 
        if (!input(J1X_L) && !XLFlag1) { VCS_SetDisableState(keyHandle3, nodeId3, &errorCode); XLFlag1 = true; }
        
        if ( input(J1Y_R) && YRFlag1 ) {
            status[0] = VCS_SetEnableState(keyHandle4, nodeId4, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle4, nodeId4, Velocity, &errorCode);
            std::cout << "No.4 motor is running +" << endl;
            YRFlag1 = false;
        } 
        if (!input(J1Y_R) && !YRFlag1) { VCS_SetDisableState(keyHandle4, nodeId4, &errorCode); YRFlag1 = true; }

        if ( input(J1Y_L) && YLFlag1 ) {
            status[0] = VCS_SetEnableState(keyHandle4, nodeId4, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle4, nodeId4, -1*Velocity, &errorCode);
            std::cout << "No.4 motor is running +" << endl;
            YLFlag1 = false;
        } 
        if (!input(J1Y_L) && !YLFlag1) { VCS_SetDisableState(keyHandle4, nodeId4, &errorCode); YLFlag1 = true; }
        usleep(100);
        // axis 2
        if ( input(J2X_R) && XRFlag2 ) {
            status[0] = VCS_SetEnableState(keyHandle1, nodeId1, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle1, nodeId1, Velocity, &errorCode);
            std::cout << "No.1 motor is running +" << endl;
            XRFlag2 = false;
        } 
        if (!input(J2X_R) && !XRFlag2) { VCS_SetDisableState(keyHandle1, nodeId1, &errorCode); XRFlag2 = true; }
        
        if ( input(J2X_L) && XLFlag2 ) {
            status[0] = VCS_SetEnableState(keyHandle1, nodeId1, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle1, nodeId1, -1*Velocity, &errorCode);
            std::cout << "No.1 motor is running -" << endl;
            XLFlag2 = false;
        } 
        if (!input(J2X_L) && !XLFlag2) { VCS_SetDisableState(keyHandle1, nodeId1, &errorCode); XLFlag2 = true; }

        if ( input(J2Y_R) && YRFlag2 ) {
            status[0] = VCS_SetEnableState(keyHandle2, nodeId2, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle2, nodeId2, Velocity, &errorCode);
            std::cout << "No.2 motor is running +" << endl;
            YRFlag2 = false;
        } 
        if (!input(J2Y_R) && !YRFlag2) { VCS_SetDisableState(keyHandle2, nodeId2, &errorCode); YRFlag2 = true; }
        
        if ( input(J2Y_L) && YLFlag2 ) {
            status[0] = VCS_SetEnableState(keyHandle2, nodeId2, &errorCode);
            status[1] = VCS_MoveWithVelocity(keyHandle2, nodeId2, -1*Velocity, &errorCode);
            std::cout << "No.2 motor is running -" << endl;
            YLFlag2 = false;
        } 
        if (!input(J2Y_L) && !YLFlag2) { VCS_SetDisableState(keyHandle2, nodeId2, &errorCode); YLFlag2 = true; }
        
        if (!input(key1)) {XRFlag1 = XLFlag1 = YRFlag1 = YLFlag1 = 0;}
        if (!input(key2)) {XRFlag2 = XLFlag2 = YRFlag2 = YLFlag2 = 0;}

        usleep(100000);
    }

    std::cout << "Exiting..." << endl;
    status[0] = VCS_SetOperationMode(keyHandle1, nodeId1, g_mode, &errorCode);
    status[1] = VCS_SetOperationMode(keyHandle2, nodeId2, g_mode, &errorCode);
    status[3] = VCS_SetOperationMode(keyHandle3, nodeId3, g_mode, &errorCode);
    status[4] = VCS_SetOperationMode(keyHandle4, nodeId4, g_mode, &errorCode);

    status[0] = VCS_SetEnableState(keyHandle2, nodeId2, &errorCode);
    status[0] = VCS_SetEnableState(keyHandle1, nodeId1, &errorCode);
    status[0] = VCS_SetEnableState(keyHandle3, nodeId3, &errorCode);
    status[0] = VCS_SetEnableState(keyHandle4, nodeId4, &errorCode);

    status[1] = VCS_MoveToPosition(keyHandle2, nodeId2, initialPosition, 1, true, &errorCode);
    status[1] = VCS_MoveToPosition(keyHandle1, nodeId1, initialPosition, 1, true, &errorCode);
    status[1] = VCS_MoveToPosition(keyHandle3, nodeId3, initialPosition, 1, true, &errorCode);
    status[1] = VCS_MoveToPosition(keyHandle4, nodeId4, initialPosition, 1, true, &errorCode);
    sleep(5);
    status[2] = VCS_SetDisableState(keyHandle2, nodeId2, &errorCode);
    status[2] = VCS_SetDisableState(keyHandle1, nodeId1, &errorCode);
    status[2] = VCS_SetDisableState(keyHandle3, nodeId3, &errorCode);
    status[2] = VCS_SetDisableState(keyHandle4, nodeId4, &errorCode);

    // exiting all devices
    status[2] = VCS_CloseAllDevices(&errorCode);
    GPIO::cleanup();
    return 0;
}
