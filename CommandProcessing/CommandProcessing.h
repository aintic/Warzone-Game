#ifndef COMP_345_COMMANDPROCESSING_H
#define COMP_345_COMMANDPROCESSING_H
#endif //COMP_345_COMMANDPROCESSING_H

#include "../GameEngine/GameEngine.h"
#include <vector>
#include <string>

using namespace std;

class GameEngine;
class State;

//*****************************************************************
// Command: Represents the commands given by the user to transition from state to state
/**
 * @brief Command class
 *
 */
class Command
{
public:

    /***
     *
     */
    void saveEffect(string command_effect);

    /**
     * @brief Constructor: Construct a new Command object
     *
     * @param typed_command
     */
    Command(string typed_command);

    /**
     * @brief Copy constructor: Construct a new Command object
     * @param c
     */
    Command(const Command &c);

    /**
     * @brief Destructor: Destroy the Command object
     *
     */
    ~Command();

    /**
     * @brief Stream insertion operator
     *
     * @param stream
     * @param c
     * @return ostream&
     */
    friend ostream& operator <<(ostream& stream, const Command& c);

    /**
     * @brief Assignment operator
     *
     * @param x
     * @return Command&
     */
    Command& operator=(const Command& c);

    // Getters and setters for the typed command
    int get_typed_command();
    void set_typed_command(string typed_command);

    // Getters and setters for the command effect
    int get_command_effect();
    void set_command_effect(string command_effect);

private:
    // Private typed command and command effect
    string typed_command;
    string command_effect;
};




//*****************************************************************
// CommandProcessor: Represents the command processor that gets called by the game engine to
// get, read, save and validate commands from the console.
/**
 * @brief CommandProcessor class
 *
 */
class CommandProcessor
{
public:

    /**
     * @brief Constructor: Construct a new CommandProcessor object

     */
    CommandProcessor();

    /**
     * @brief Copy constructor: Construct a new CommandProcessor object
     * @param c
     */
    CommandProcessor(const Command &c);

    /**
     * @brief Destructor: Destroy the CommandProcessor object
     *
     */
    ~CommandProcessor();

    /**
     * @brief Stream insertion operator
     *
     * @param stream
     * @param c
     * @return ostream&
     */
    friend ostream& operator <<(ostream& stream, const CommandProcessor& c);

    /**
     * @brief Assignment operator
     *
     * @param c
     * @return Command&
     */
    CommandProcessor& operator=(const CommandProcessor& c);

    /**
     * @brief Gets the command from the console input, saves it and validates it
     * @return
     */
    Command* getCommand();

    // Getters and setters for the command list
    vector<Command*> get_commands();
    void set_commands(vector <Command> commands);

private:
    // Private methods and command list
    vector<Command*> commands;

    /**
     * @brief Stores the command internally in a collection of Command objects
     * @return
     */
    Command* readCommand();

    /**
     * @brief  Gets commands from the console as a string
     */
    void saveCommand(Command*);

    /**
     * @brief Checks if the command is valid in the current game state. If the command is not valid,
     * a corresponding error message is saved in the effect of the command.
     * @return
     */
    bool validate(Command*, GameEngine*);

};