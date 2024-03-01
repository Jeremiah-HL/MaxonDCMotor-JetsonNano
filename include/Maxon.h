#ifndef __MAXON_H__
#define __MAXON_H__
#define DEFAULT 1
#include <string>
using namespace std;

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int BOOL;
typedef void* HANDLE;
unsigned int errorCode = 0;

void stdMsgPrintOut(string msg, Motor motor){
    cout << "[Motor Node Id : " << motor.getNodeId() << " ]: ";
    cout << msg << endl;
}

void errorCodePrintOut(unsigned int errorCode, Motor motor){
    string msg = "ErrorCode is as followed : " + to_string(errorCode);
    stdMsgPrintOut(msg, motor);
}

class Motor{
protected:
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

    virtual BOOL ifOpen() {};

public:
    virtual void openDevice() {};
    virtual BOOL setOperationMode(char operationMode) {};
    virtual BOOL Enable() {};
    virtual BOOL Disable() {};

    void setNodeId(WORD nodeId);
    string getPortName();
    WORD getNodeId();
    
};

class MaxonDCMotor : public Motor{
public:

    MaxonDCMotor(BOOL Default);
    MaxonDCMotor(char* portName, char* deviceName, char* protocolStackName, char* interfaceName, int operationMode);
    ~MaxonDCMotor();

protected:
    BOOL ifOpen() override;

public:
    void openDevice() override;
    BOOL setOperationMode(char operationMode) override;
    BOOL Enable() override;
    BOOL Disable() override;

};

#endif