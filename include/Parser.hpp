
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>






class ParserException : public std::runtime_error {
    public:
        ParserException(const std::string &arg) : std::runtime_error(arg) {}
};


template <class T>
class Parser {

    protected:

        // Command is just a string
        using CommandName = std::string;

        // Custom commands are methods
        using CommandMethod = std::function<void(std::stringstream& args)>;

        // Flags
        using FlagName = std::string;
        using FlagDescription = std::string;

        // Contains method + his description + flags
        struct CommandInfo{
            std::string description;
            std::unordered_map<FlagName, FlagDescription> flagsMap;
            CommandMethod func;
        };

    public:


        Parser(T * target)  : target(target) {
            loadBasicCommands();
        }

        ~Parser() {}

        /**
         * Parse a stringstream.
         * The fist word must be the command name, followed by [flag argument]
         * Returns true if wanting to quit the program
         */
        bool parseAndExecute(std::stringstream &input_stream) {

            CommandName command;

            input_stream >> command;

            std::cout << "\n";
            if (!(command == "quit"))
            {
                auto dict_it = commandMap.find(command);

                if (dict_it != commandMap.end())
                {
                    try {
                        dict_it->second.func(input_stream);
                    }
                    catch (ParserException &e) {
                        std::cerr << "Error" << e.what() << "\n\n";
                    }

                }
                else
                    std::cerr << "Command Not Found\n\n";


                return false;
            }
            else
                return true;

        }


        void addCommand(const CommandName &name, const CommandInfo &func)  {
            commandMap.insert({name, func});
        }

        T * getTarget() {
            return target;
        }

    private:

        /**
         * Loads help command
         */
        void loadBasicCommands() {

            commandMap["help"] = CommandInfo{
                .description = "Shows other available commands.",
                .flagsMap = {},
                .func = [this](std::stringstream &args) {

                    std::string token;

                    if (!(args >> token)) {
                        std::cout << "List of Commands:\n\n";
                        std::cout << "* quit" << "\n\t\t" << "DESC: Quit Program" << "\n";

                        for (const auto& [key, value] : this->commandMap) {
                            std::cout << "* " << key << "\n\t\t" << "DESC: " << value.description << "\n";
                        }
                    }
                    else
                        throw ParserException("Extra arguments not allowed for help");


                }
            };

        };

    private:
        std::unordered_map<CommandName, CommandInfo> commandMap;
        T * target;

};
