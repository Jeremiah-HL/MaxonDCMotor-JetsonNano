#include<iostream>
using namespace std;

class Father
{
public:
static int m_A;
};

class Son: public Father{
public:
    int m_B;

};

void test01(){
    Son son;
    Father::m_A = 2;
    cout << son.m_A << endl;
}

int Father::m_A = 1;

int main(){

    test01();
}