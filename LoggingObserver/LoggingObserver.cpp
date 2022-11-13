#include <fstream>
#include <iostream>
#include "LoggingObserver.h"
#include <typeinfo>


using namespace std;
/**
 * Default Constructor for ILoggable
 */
ILoggable::ILoggable(){}
/**
 * copy constructor for ILoggable
 * @param s
 */
ILoggable::ILoggable(const ILoggable& s) {

}
/**
 * Assignment operator for ILoggable
 * @param s
 * @return ILoggable object
 */
ILoggable& ILoggable::operator=(const ILoggable& s) {
    return *this;
}


/**
 * Default constructor for LogObserver
 */
LogObserver::LogObserver() {

}
/**
 * Copy constructor for LogObserver
 * @param s
 */
LogObserver::LogObserver(const LogObserver& s) {

}
/**
 * Assignment operator for LogObserver
 * @param s
 * @return
 */
LogObserver& LogObserver::operator=(const LogObserver& s) {
    return *this;
}

/**
 * Default constructor for Subject
 */
Subject::Subject() {
}
/**
 * Destructor for Subject
 */
Subject::~Subject(){
    this->_observers = nullptr;
}
/**
 * Copy constructor for Subject
 * @param s
 */
Subject::Subject(const Subject& s) : _observers(s._observers) {

}
/**
 * Assignment operator for Subject
 * @param s
 * @return
 */
Subject& Subject::operator=(const Subject& s)
{
    this->_observers = s._observers;
    return *this;
}
/**
 * Attach Observer
 * @param o
 */
void Subject::Attach(Observer* o){
    _observers = o;
}
/**
 * Detach Observer
 * @param o
 */
void Subject::Detach(){
    if(_observers != nullptr){
        _observers = nullptr;
    }
}
/**
 * Notify method
 * @param _loggable_object
 */
void Subject::Notify(ILoggable* _loggable_object){
    if(_observers != nullptr){
        _observers->Update(_loggable_object);
    }
}
/**
 * Default constructor for Observer
 */
Observer::Observer(){}
/**
 * Copy constructor for Observer
 * @param s
 */
Observer::Observer(const Observer& s) {

}
/**
 * Assignment operator for Observer
 * @param s
 * @return
 */
Observer& Observer::operator=(const Observer& s) {
    return *this; }
/**
 * Update method that logs gamelog
 * @param _loggable_object
 */
void LogObserver::Update(ILoggable* _loggable_object)
{

    // opening output file stream
    ofstream logfile;
    logfile.open("../gamelog.txt", ofstream::app); // append setting. If gamelog.txt is not found, it will create it.
    logfile << _loggable_object->stringToLog() << endl; // output the stringToLog to the output file
    logfile.close(); // close the output file stream
}
/**
 * Stream insertion operators
 */
ostream& operator<<(ostream& os, ILoggable& p){
    return os;
}ostream& operator<<(ostream& os, Observer&& p){
    return os;
}ostream& operator<<(ostream& os, LogObserver& p){
    return os;
}ostream& operator<<(ostream& os, Subject& p){
    return os;
}


