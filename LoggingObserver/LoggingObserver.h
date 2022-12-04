//
// Created by Hongsuk on 10/30/2022.
//
#pragma once
#include <string>
#include <vector>
#include <list>



using namespace std;

class ILoggable{
public:
    //Default constructor
    ILoggable();
    //Copy constructor
    ILoggable(const ILoggable& s);
    //Assignment operator
    ILoggable& operator=(const ILoggable& s);
    //pure virtual stringToLog function
    virtual string stringToLog() = 0;
    //Stream insertion operator
    friend ostream& operator<<(ostream& os, ILoggable& s);
};

class Observer{
public:
    //Default constructor
    Observer();
    //Copy constructor
    Observer(const Observer& s);
    //Assignment operator
    Observer& operator=(const Observer& s);
    //pure virtual Update method
    virtual void Update(ILoggable* _loggable_object) = 0;
    //Stream insertion operator
    friend ostream& operator<<(ostream& os, Observer& s);


};

class Subject{
public:
    //Attach observer method
    virtual void Attach(Observer* o);
    //Detach observer method
    virtual void Detach();
    //Notify method
    virtual void Notify(ILoggable* _loggable_object);
    //Defautl constructor
    Subject();
    //Destructor
    ~Subject();
    //Copy constructor
    Subject(const Subject& s);
    //Assignment operator
    Subject& operator=(const Subject& s);
    //Stream insertion operator
    friend ostream& operator<<(ostream& os, Subject& s);


private:
    Observer * _observers = nullptr;

};

class LogObserver : public Observer{
public:
    //Default constructor
    LogObserver();
    //copy constructor
    LogObserver(const LogObserver& s);
    //Assignment operator
    LogObserver& operator=(const LogObserver& s);
    //stream insertion operator
    friend ostream& operator<<(ostream& os, LogObserver& s);
    //Update method
    void Update(ILoggable* _loggable_object);

};

static vector<string> getValidCommand(); //method to get valid

