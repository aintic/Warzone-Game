#include <fstream>
#include <iostream>
#include "LoggingObserver.h"
#include <typeinfo>


using namespace std;

ILoggable::ILoggable(){}

Observer::Observer(){}


LogObserver::LogObserver() {}


Subject::Subject() {
}
Subject::~Subject(){
    this->_observers = nullptr;
}
void Subject::Attach(Observer* o){
    _observers = o;
}

void Subject::Detach(Observer* o){
    if(_observers != nullptr){
        _observers = nullptr;
    }
}
void Subject::Notify(ILoggable* _loggable_object){
    if(_observers != nullptr){
        _observers->Update(_loggable_object);
    }
}



void LogObserver::Update(ILoggable* _loggable_object)
{

    cout << _loggable_object->stringToLog() << endl;
    // opening output file stream
    ofstream logfile;
    logfile.open("../gamelog.txt", ofstream::app); // append setting. If gamelog.txt is not found, it will create it.
    logfile << _loggable_object->stringToLog() << endl; // output the stringToLog to the output file
    logfile.close(); // close the output file stream
}

