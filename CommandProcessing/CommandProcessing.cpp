#include "CommandProcessing.h"


//*****************************************************************
// Command: Represents the commands given by the client to transition from state to state

/**
 * @brief Constructor: Construct a new Command
 *
 */
Command::Command() {
    this->typed_command = "";
}

/**
 * @brief Constructor: Construct a new Command:: Command object
 *
 * @param typed_command
 */
Command::Command(string typed_command) {
    this->typed_command = typed_command;
}

/**
 * @brief Copy constructor: Construct a new Command:: Command object
 *
 * @param c
 */
Command::Command(const Command &c){
    typed_command = c.typed_command;
    command_effect = c.command_effect;
}

/**
 * @brief Stream insertion operator
 *
 * @param stream
 * @param c
 * @return ostream&
 */
ostream& operator <<(ostream& stream, const Command& c){
    stream << "Command: \n"<< "Typed Command: "<< c.typed_command << "\nCommand Effect: "<< c.command_effect << endl;
    return stream;
}

/**
 * @brief Assignment operator
 *
 * @param t
 * @return Command&
 */
Command& Command::operator=(const Command& c){
    typed_command = c.typed_command;
    command_effect = c.command_effect;
    return *this;
}

/**
 * @brief Destructor: Destroy the Command:: Command object
 *
 */
Command::~Command() {
}

// Getters and Setters
string Command::get_command_effect()
{
    return this->command_effect;
}
void Command::set_command_effect(std::string command_effect)
{
    this->command_effect = command_effect;
}

string Command::get_typed_command()
{
    return this->typed_command;
}
void Command::set_typed_command(std::string typed_command)
{
    this->typed_command = typed_command;
}

/**
 * Save the command effect
 * @param command_effect
 */
void Command::saveEffect(std::string command_effect) {
    this->set_command_effect(command_effect);
}

//*****************************************************************
// CommandProcessor: Represents the command processor that gets called by the game engine to
// get, read, save and validate commands from the console.
/**
 * @brief Constructor: Construct a new CommandProcessor:: CommandProcessor object
 *
 * @param typed_command
 */
CommandProcessor::CommandProcessor() {
}

/**
 * @brief Copy constructor: CommandProcessor a new CommandProcessor:: CommandProcessor object
 *
 * @param c
 */
CommandProcessor::CommandProcessor(const CommandProcessor &c){
    commands = c.commands;
}

/**
 * @brief Stream insertion operator
 *
 * @param stream
 * @param c
 * @return ostream&
 */
ostream& operator <<(ostream& stream, const CommandProcessor& c){
    for(Command *command: c.commands){
        stream << command << endl;
    }
    return stream;
}

/**
 * @brief Assignment operator
 *
 * @param t
 * @return Command&
 */
CommandProcessor& CommandProcessor::operator=(const CommandProcessor& c){
    commands = c.commands;
    return *this;
}

/**
 * @brief Destructor: Destroy the CommandProcessor:: CommandProcessor object
 *
 */
CommandProcessor::~CommandProcessor() {
    for(Command *command: commands){
        delete command;
        command = nullptr;
    }
}

// Getters and Setters
vector<Command*> CommandProcessor::get_commands()
{
    return this->commands;
}

void CommandProcessor::set_commands(vector<Command*> commands)
{
    this->commands = commands;
}


/**
 * @brief Gets the command from the console input, saves it and validates it
 * @return
 */
Command* CommandProcessor::getCommand(GameEngine* game){
    cout << "\033[1;34m[Starting getCommand()]\033[0m\n" << endl;

    // read a command
    Command* command = this->readCommand();

    // validate the command
    bool valid = this->validate(command, game);

    //save the command
    this->saveCommand(command);

    // while not valid, show the error, and ask for another command
    while (!valid){
        cout<< command->get_command_effect() << endl;

        // read a command
        command = this->readCommand();

        // validate the command
        valid = this->validate(command, game);
    }

    cout << "\033[1;34m[Exiting getCommand()]\033[0m\n" << endl;
    return command;
}

/**
 * @brief Stores the command internally in a collection of Command objects
 * @return
 */
Command* CommandProcessor::readCommand(){
    cout << "\033[1;31m\t[Starting readCommand()]\033[0m" << endl;
    string string_command;
    cout << "\n\t\tPlease enter command to move to the next state:  ";
    std::getline(std::cin, string_command);
    cout << "\033[1;31m\t[Exiting readCommand()]\033[0m\n" << endl;
    return new Command(string_command);
}

/**
 * @brief  Gets commands from the console as a string
 */
void CommandProcessor::saveCommand(Command* c){
    cout << "\033[1;32m\t[Starting saveCommand()]\033[0m\n" << endl;
    this->commands.push_back(c);
    cout << "\033[1;32m\t\t[Command saved]\033[0m\n" << endl;
    cout << "\033[1;32m\t[Exiting saveCommand()]\033[0m\n" << endl;
}

/**
 * @brief Checks if the command is valid in the current game state. If the command is not valid,
 * a corresponding error message is saved in the effect of the command.
 * @return
 */
bool CommandProcessor::validate(Command* command, GameEngine* game){

    cout << "\033[1;33m\t[Starting validate()]\033[0m\n" << endl;

    string typed_command = command->get_typed_command();

    // for commands like loadmap and add player, the valid command is only the first token of the command
    // for example loadmap examplemap --> valid token is loadmap
    string delimiter = " ";
    string token_command = typed_command.substr(0, typed_command.find(delimiter));

    State* currentState = game->getCurrentState();

    string state_name = currentState->getStateName();

    vector<string> valid_commands = currentState->getSpecificValidCommands();

    // check is typed command is in vector of allowed commands
    if (std::find(valid_commands.begin(), valid_commands.end(), token_command) != valid_commands.end())
    {
        // if loadmap or addplayer, we need a name for the map and the player
        if(token_command == "loadmap" || token_command == "addplayer"){
            if(typed_command.length() <= (token_command.length() + 1)){

                // command is incomplete. ex: loadmap instead of loadmap <mapname>
                string error = currentState->getWrongCommandError();
                command->set_command_effect(error);
                cout << "\033[1;33m\t\t[Command is not valid]\033[0m\n" << endl;
                cout << "\033[1;33m\t[Exiting validate()]\033[0m\n" << endl;
                return false;
            }
        }

        // if it is, return valid
        cout << "\033[1;33m\t\t[Command is valid]\033[0m\n" << endl;
        cout << "\033[1;33m\t[Exiting validate()]\033[0m\n" << endl;
        return true;
    }
    else {
        // otherwise save the command error in the effect string of the command
        string error = currentState->getWrongCommandError();
        command->set_command_effect(error);
        cout << "\033[1;33m\t\t[Command is not valid]\033[0m\n" << endl;
        cout << "\033[1;33m\t[Exiting validate()]\033[0m\n" << endl;
        return false;
    }
}



//*****************************************************************