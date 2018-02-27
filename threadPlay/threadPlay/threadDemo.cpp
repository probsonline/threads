//
//  threadDemo.cpp
//  threadPlay
//
//  Created by Anwar, Kaleem on 2/25/18.
//  Copyright © 2018 Anwar, Kaleem. All rights reserved.
//

#include "demo.h"
#include <thread>

#include <chrono>

void myTaskEntry(string message){
    
    while (true) {
        string str = "I am running in " + message +"\n";            //Note: using multiple << doesn't print cout fully and can yield in-between as best to first prepare the message, which will not yield in-between and then print.
        cout << str;
//        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
}

void myHungryThreadEntry(string message){
    
    while (true) {
        string str = "I am " + message + "\n";
        cout << str;
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }
}

void thread_demo(){
    
    thread t1(myTaskEntry, "Thread 1");
    thread t2(myTaskEntry, "Thread 2");
    thread t3(myHungryThreadEntry, "Hungry Thread");
    
    t1.join();
    t2.join();
    t3.join();
    
    return;
}
