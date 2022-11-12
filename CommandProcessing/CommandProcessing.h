#pragma once
#include "../GameEngine/GameEngine.h"
#include <vector>
#include <string>

using namespace std;

class GameEngine;
class State;

//*****************************************************************
// Command: Represents the commands given by the client to transition from state to state
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
    Command();

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
    string get_typed_command();
    void set_typed_command(string typed_command);

    // Getters and setters for the command effect
    string get_command_effect();
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
    CommandProcessor(const CommandProcessor &c);

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
    virtual Command* getCommand(GameEngine* game);

    // Getters and setters for the command list
    vector<Command*> get_commands();
    void set_commands(vector <Command*> commands);

    /**
     * @brief Checks if the command is valid in the current game state. If the command is not valid,
     * a corresponding error message is saved in the effect of the command.
     * @return
     */
    bool validate(Command* command, GameEngine* game);

protected:
    /**
     * @brief Stores the command internally in a collection of Command objects
     * @return
     */

    Command* readCommand();
    /**
     * @brief  Gets commands from the console as a string
     */
    void saveCommand(Command*);

private:
    // Private methods and command list
    vector<Command*> commands;

};

//*****************************************************************
// FineLineReader: Represents the file reader that reads a file of commands
/**
 * @brief FileLineReader class
 *
 */
class FileLineReader {
public:

    /**
     * @brief Constructor: Construct a new FileLineReader object

     */
    FileLineReader();

    /**
     * @brief Copy constructor: Construct a new FileLineReader object
     * @param c
     */
    FileLineReader(const FileLineReader &f);

    /**
     * @brief Destructor: Destroy the FileLineReader object
     *
     */
    ~FileLineReader();

    /**
     * @brief Stream insertion operator
     *
     * @param stream
     * @param f
     * @return ostream&
     */
    friend ostream& operator <<(ostream& stream, const FileLineReader& f);

    /**
     * @brief Assignment operator
     *
     * @param f
     * @return Command&
     */
    FileLineReader& operator=(const FileLineReader& f);


    /**
     * @brief ReadLineFromFile
     *
     */
    string readLineFromFile(string);

    /**
     * Getter for the file lines
     * @return
     */
    vector<string> get_file_lines();

    /**
     * Setter for the file lines
     * @return
     */
    void set_file_lines(vector<string>);


private:
    vector<string> file_lines;
    int next_line;
};


//*****************************************************************
// FileCommandProcessorAdapter: Represents the file command processor adapter that gets called by the game engine to
// get, read, save and validate commands from a file.

/**
 * FileCommandProcessorAdapter adapts the file reader to act as a command processor
 */
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    /**
     * Default constructor
     * @param file_name
     */
    FileCommandProcessorAdapter(string file_name);

    /**
     * Copy constructor
     */
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);

    /**
     * Assignment operator
     * @return
     */
    FileCommandProcessorAdapter& operator= (const FileCommandProcessorAdapter&);

    /**
     * Destructor
     */
    ~FileCommandProcessorAdapter();

    /**
     * Read command from file
     * @return
     */
    Command* readCommand();

    /**
     * stream insertion operator
     * @return
     */
    friend ostream& operator<< (ostream&, const vector<string>);

    /**
     * Get Command
     * @param game
     * @return
     */
    Command* getCommand(GameEngine* game) override;

private:

    /**
     * File line reader pointer
     */
    FileLineReader* fileLineReader;

    /**
     * File name
     */
    string file_name;
};