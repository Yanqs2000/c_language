#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <mutex>
#include <thread>

class A{
public:
    // 插入消息
    void insertMsg(){
        for(int i = 0; i < 100; i++){
            std::cout << "insertMsg: " << i << std::endl;
            my_mutex1.lock();
            my_mutex2.lock();
            Msg.push_back(i*100);
            my_mutex2.unlock();
            my_mutex1.unlock();
        }
    }

    void readMsg(){
        int MsgCom;
        for (int i = 0; i < 100; i++){
            MsgCom = MsgLULProc(i);
            if (MsgLULProc(MsgCom)){
                std::cout << "readMsg: " << MsgCom << std::endl;
            }
            else{
                std::cout << "readMsg: No Msg" << std::endl;
            }
        }
    }
    // 加解锁函数
    bool MsgLULProc(int& command){
        int curMsg;
        my_mutex2.lock();
        my_mutex1.lock();
        if(!Msg.empty()){
            command = Msg.front();
            Msg.pop_front();

            my_mutex1.unlock();
            my_mutex2.unlock();
            return true;
        }
        else{
            my_mutex1.unlock();
            my_mutex2.unlock();
            return false;
        }
    }
private:
    // 消息列表
    std::list<int> Msg;
    std::mutex my_mutex1;
    std::mutex my_mutex2; 
};

int main()
{
    A a;
    // 创建线程
    std::thread insertTd(&A::insertMsg, &a);
    std::thread readTd(&A::readMsg, &a);
    // 等待线程结束
    insertTd.join();
    readTd.join();
    return 0;
}