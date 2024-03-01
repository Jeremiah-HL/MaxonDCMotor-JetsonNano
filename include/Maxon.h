#ifndef __MAXON_H__
#define __MAXON_H__
#define DEFAULT 1
#include <string>
using namespace std;

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef int BOOL;
typedef void* HANDLE;
unsigned int errorCode = 0;

class Motor{
private:
    unsigned short m_NodeId;
    void* m_keyHandle;
    string m_portName;
    int m_operationMode;

    int m_baudrate = 1000000;
    BOOL m_ifDefault = 0;
    static unsigned short deviceNum;
    static string deviceName;
    static string protocolStackName;
    static string interfaceName;

protected:
    virtual BOOL ifOpen() = 0;

public:
    virtual void openDevice() = 0;
    virtual BOOL setOperationMode(char operationMode) = 0;
    virtual BOOL Enable() = 0;
    virtual BOOL Disable() = 0;
};

class MaxonDCMotor : public Motor{
public:

    MaxonDCMotor(BOOL Default);
    MaxonDCMotor(char* portName, char* deviceName, char* protocolStackName, char* interfaceName, int operationMode);
    ~MaxonDCMotor();

protected:
    BOOL ifOpen();

public:
    void openMotor();
    BOOL setOperationMode(char operationMode);
    BOOL Enable();
    BOOL Disable();
};

unsigned short MaxonDCMotor::Motor::deviceNum = 0;
string MaxonDCMotor::Motor::deviceName = "EPOS4";
string MaxonDCMotor::Motor::protocolStackName = "MAXON SERIAL V2";
string MaxonDCMotor::Motor::interfaceName = "USB";

#endif