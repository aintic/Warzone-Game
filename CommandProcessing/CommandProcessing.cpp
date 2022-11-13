#include "CommandProcessing.h"
#include "fstream"
#include "iostream"


//*****************************************************************
// Command: Represents the commands given by the client to transition from state to state

/**
 * @brief Constructor: Construct a new Command
 *
 */
Command::Command() {
    this->typed_command = "";
}

Command::Command(Observer* _obs) {
    this->typed_command = "";
    this->Attach(_obs);
    logger = _obs;
}


/**
 * @brief Constructor: Construct a new Command:: Command object
 *
 * @param typed_command
 */
Command::Command(string typed_command, Observer* _obs) {
    this->typed_command = typed_command;
    this->Attach(_obs);
    logger = _obs;

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
    stream << "Command: \n"<< "\tTyped Command: \""<< c.typed_command << "\""<< "\n\tCommand Effect: \""<< c.command_effect << "\""<<endl;
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
    cout<< "\n[[Saving command effect]]\n" << *this<< endl;
    Notify(this);
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

CommandProcessor::CommandProcessor(Observer* _obs) {
    this->Attach(_obs);
    logger = _obs;
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
        stream <<"\t" << *command << endl;
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
    this->Detach();
    logger = nullptr;
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
    cout << "\n[[Starting getCommand()]]\n" << endl;

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

    return command;
}

/**
 * @brief Stores the command internally in a collection of Command objects
 * @return
 */
Command* CommandProcessor::readCommand(){
    cout << "[[Starting readCommand()]]" << endl;
    string string_command;
    cout << "\n\tPlease enter command to move to the next state:  ";
    std::getline(std::cin, string_command);
    return new Command(string_command, logger);
}

/**
 * @brief  Gets commands from the console as a string
 */
void CommandProcessor::saveCommand(Command* c){
    cout << "\n[[Starting saveCommand()]]" << endl;
    this->commands.push_back(c);
    cout << "Saving command in the command processor." << endl;
    Notify(this);
}

/**
 * @brief Checks if the command is valid in the current game state. If the command is not valid,
 * a corresponding error message is saved in the effect of the command.
 * @return
 */
bool CommandProcessor::validate(Command* command, GameEngine* game){

    cout << "\n[[Starting validate()]]" << endl;

    if(command == nullptr){
        cout << "Validating: Command is NOT VALID" << endl;
        return false;
    }

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
                cout << "Validating: Command is NOT VALID" << endl;
                return false;
            }
        }

        // if it is, return valid
        cout << "Validating: Command is VALID" << endl;
        return true;
    }
    else {
        // otherwise save the command error in the effect string of the command
        string error = currentState->getWrongCommandError();
        command->set_command_effect(error);
        cout << "Validating: Command is NOT VALID" << endl;
        return false;
    }
}

string Command::stringToLog()
{

    string command = "Commands:  " + get_typed_command();
    string command_effect = "\nCommand effect: " + get_command_effect();
    return command + command_effect;
}
string CommandProcessor::stringToLog()
{
    string output = "The collection of commands: \n";
    vector<Command*> temp = get_commands();
    for(Command* x : temp){
        output += x->get_typed_command() + "\n";
    }
    return output;
}

//*****************************************************************
// FileLineReader: Represents the reader of the file of commands

/**
 * Default Constructor
 */
FileLineReader::FileLineReader() {
    this->next_line = 0;
}

/**
 * Copy constructor
 * @param f
 */
FileLineReader::FileLineReader(const FileLineReader& f) {
    this->set_file_lines(f.file_lines);
    this->next_line = f.next_line;
}

/**
 * Assignment operator
 * @param fileReader
 * @return
 */
FileLineReader& FileLineReader::operator= (const FileLineReader& fileReader) {
    this->set_file_lines(fileReader.file_lines);
    this->next_line = fileReader.next_line;
    return *this;
}

/**
 *
 * @param fileName
 */
string FileLineReader::readLineFromFile(string file_name) {

    ifstream file;
    int current_line = 0;
    string line;

    file.open(file_name);

    if (file.fail()) {
        cout << "File failed to open. Only valid file names can be used." << endl;
        file.close();
        return "";
    }

    while(!file.eof()) {
        getline(file, line);
        if(current_line == this->next_line) {
            cout << "reading \"" + line +"\"" << endl;
            this->next_line++;
            file.close();
            return line;
        }
        current_line ++;
    }

    cout << "End of file reached, no more commands to read." << endl;
    file.close();
    return "-1";
}



/**
 * Getter of file lines
 * @return
 */
vector<string> FileLineReader::get_file_lines() {
    return file_lines;
}

/**
 * Setter of file lines
 * @return
 */
void FileLineReader::set_file_lines(vector<string> file_lines) {
    this->file_lines =  file_lines;
}

// Destructor
FileLineReader::~FileLineReader() {
}


//*****************************************************************
// FileCommandProcessorAdapter: Represents the file command processor adapter that gets called by the game engine to
// get, read, save and validate commands from a file.
/**
 *  Default constructor
 * @param file_name
 */
// Default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string file_name, Observer* _obs){

    this->fileLineReader = new FileLineReader();
    this->file_name = file_name;
    this->Attach(_obs);
    logger = _obs;
}



/**
 * Copy constructor
 * @param f
 */
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& f) : CommandProcessor(f){

    this->fileLineReader = f.fileLineReader;
    this->file_name = f.file_name;
}

/**
 * Assignment operator
 * @param f
 * @return
 */
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator= (const FileCommandProcessorAdapter& f) {

    CommandProcessor::operator=(f);
    this->fileLineReader = f.fileLineReader;
    this->file_name = f.file_name;
    return *this;
}

/**
 * Destructor
 */
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete this->fileLineReader;
}


/**
 * read command from file
 * @return
 */
Command* FileCommandProcessorAdapter::readCommand() {

    cout << "[[Starting readCommand() of the adapter]]" << endl;

    string line_from_file = this->fileLineReader->readLineFromFile(this->file_name);

    // signal end of file
    if(line_from_file == "-1"){
        return nullptr;
    }

    return new Command(line_from_file, logger);
}

/**
 * @brief Gets the command from the console input, saves it and validates it
 * @return
 */
Command* FileCommandProcessorAdapter::getCommand(GameEngine* game){
    cout << "\n[[Starting getCommand() in Adapter]]\n" << endl;

    // read a command
    Command* command = this->readCommand();

    // validate the command
    bool valid = this->validate(command, game);

    //save the command
    if(command!= nullptr){
        this->saveCommand(command);
    }

    // while not valid, show the error, and ask for another command
    while (!valid){
        if(command == nullptr){
            break;
        }
        cout<< command->get_command_effect() << endl;

        // read a command
        command = this->readCommand();

        // validate the command
        valid = this->validate(command, game);
    }

    return command;
}