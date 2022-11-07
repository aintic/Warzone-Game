//
// Created by Hongsuk on 10/30/2022.
//
#pragma once
#include <string>
#include <vector>
#include <list>

#ifndef COMP_345NEW_LOGGINGOBSERVER_H
#define COMP_345NEW_LOGGINGOBSERVER_H

#endif //COMP_345NEW_LOGGINGOBSERVER_H



using namespace std;

class ILoggable{
public:
    ILoggable();
    virtual string stringToLog() = 0; //pure virtual function

};

class Observer{
public:

    Observer();
    virtual void Update(ILoggable* _loggable_object) = 0;


};

class Subject{
public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify(ILoggable* _loggable_object);

    Subject();
    ~Subject();
private:
    Observer * _observers = nullptr;

};

class LogObserver : public Observer{
public:
    LogObserver();
    void Update(ILoggable* _loggable_object);

};

static vector<string> getValidCommand(); //method to get valid

