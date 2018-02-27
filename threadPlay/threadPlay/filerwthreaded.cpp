//
//  filerwthreaded.cpp
//  threadPlay
//
//  Created by Anwar, Kaleem on 2/26/18.
//  Copyright © 2018 Anwar, Kaleem. All rights reserved.
//

#include "demo.h"

#include <fstream>
#include <thread>
//This exmplaes demonstrates multiple ways of implementing threads entry points (handlers), alongwith continuing the basic classes practices

class myFileHandler{
public:
    myFileHandler(){}
    myFileHandler(string inF, string outF);
    ~myFileHandler(){}
    void write_to_file(string &str);
    void read_from_file(string &str);
    void write_for_reader(string &str);
    string get_inputfile_name(){
        return infilepath;
    }
    
    string get_outpufile_name(){
        return outfilepath;
    }
    
private:
    ifstream inputfile;
    ofstream outputfile;
    string infilepath;
    string outfilepath;
    
};

myFileHandler::myFileHandler(string inF, string outF){
    infilepath = inF;
    outfilepath = outF;
    
    inputfile.open(inF);
    if (inputfile.is_open()) {
        cout << "successfully opened " << inF << " for reading" << endl;
    }
    else{
        cout << "Failed to open " << inF << endl;
    }
    
    outputfile.open(outF);
    if (outputfile.is_open()) {
        cout << "successfully opened " << outF << " for writing" << endl;
    }
    else{
        cout << "Failed to open " << outF << endl;
    }

}

void myFileHandler::write_to_file(string &str){
    outputfile << str << endl;
    cout << str << endl;
}

void myFileHandler::read_from_file(string &str){
    inputfile >> str;
//    cout << str << endl;
}

void myFileHandler::write_for_reader(string &str){
    ofstream ofile(infilepath);
    ofile << str << endl;
    ofile.close();
}

void sleep(int milliseconds){
    std::this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void WriterThread(myFileHandler &fileH, int limit){
    int counter=0;
    while(counter++ < limit){
        string logmessage = to_string(counter) + ". writing to file " + fileH.get_outpufile_name() + "\n";
        fileH.write_to_file(logmessage);
        sleep(2000);
    }
}

void readerThreadOuter(myFileHandler &fileH, int &r_thread_num, int limit){
    int counter=0;
    while(counter++ < limit){
        string str;
        fileH.read_from_file(str);
        string logmessage = to_string(counter) + ". reading message " + str + " in reader thread number " + std::to_string(++r_thread_num) + "\n";
        cout << logmessage ;
        sleep(800);
    }
}

//NOte: "Attempt to use a deleted function". This weird error is thrown if the parameters to the thread constructors are not correct i.e. the name of the entry point and entry point paramters are not listed properly

void filerw_threaded_demo(){
    int limit=3;
    string inputFile="input.txt";
    string outputFile="output.txt";
    myFileHandler mfile(inputFile, outputFile);
    
    //Create a thread in a simple way, specifying a clearly separately, defined thread handler. If an object needs to be given as input, it must be wrapped in ref()
    std::thread writer(WriterThread, ref(mfile), limit);
    writer.join();

    int readerThreadCounter=0;
    
    //Create a thread using lambda. Here the entry point is defined as lambda. The full entrypoint definition is the first paramter and then the paramter to the thread handler are passed as the next parameters to thread constructor.
    thread reader1 ([](myFileHandler &fileH, int r_thread_num, int limit){
        int counter=0;
        while(counter++ < limit){
            string str;
            fileH.read_from_file(str);
            string logmessage = to_string(counter) + ". reading message " + str + " in reader thread number " + std::to_string(r_thread_num) + "\n";
            cout << logmessage ;
            sleep(500);
        }
    }
    , ref(mfile), ++readerThreadCounter, limit); //Don't foget to specify the thread handler paramters even when using lambda simply
    
    thread reader2(readerThreadOuter, ref(mfile),ref(readerThreadCounter), limit);  //Note: readerThreadCounter is passed by refernce. IN thread simple & can't be used we have to use ref. Due to ref the value will be modified inside the thread handler
    
    //Demoing that the contructor for thread can be called using {} braces as well instead of (). Also demoing that & in lambda signifies that all the local parameters in the function are accessible by refernce to thread handler without any extra work required to pass the paramters
    thread reader3{[&](){
        int counter=0;
        while(counter++ < limit){
            string str;
            mfile.read_from_file(str);
            string logmessage = to_string(counter) + ". reading message " + str + " in reader thread number " + std::to_string(++readerThreadCounter) + "\n";
            cout << logmessage ;
            std::this_thread::sleep_for(chrono::seconds(1));
        }
    }};

    //Demoing that = in lambda signifies that all the local parameters in the function are accessible by value to thread handler without any extra work required to pass the paramters
    thread reader4([=](myFileHandler &fileH, int &r_thread_num){
        int counter=0;
        while(counter++ < limit){
            string str;
            fileH.read_from_file(str);
            string logmessage = to_string(counter) + ". reading message " + str + " in reader thread number " + std::to_string(++r_thread_num) + "\n";
            cout << logmessage ;
            sleep(1000);
        }
    }, ref(mfile), ref(readerThreadCounter));

    thread writerreader([&](){
        srand(time(NULL));
        string str =to_string(readerThreadCounter*rand()%99);
        mfile.write_for_reader(str);
    });
    
    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();

    return;
}
