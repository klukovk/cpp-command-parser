
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

        using CommandName = std::string;

        using CommandMethod = std::function<void(std::stringstream& args)>;
        using FlagName = std::string;
        using FlagDescription = std::string;

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
                        dict_it->second(input_stream);
                    }
                    catch (ParserException &e) {
                        std::cout << e.what();
                    }

                }
                else
                    std::cout << "Command Not Found\n\n";


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
        void loadBasicCommands() {

            commandMap["help"] = CommandInfo{
                .description = "Shows Other Aviable Commands.",
                .flagsMap = {},
                .funct = [this](std::stringstream &args) {

                    std::cout << "List of Commands:\n\n";
                    std::cout << "* quit" << "\n";

                    for (const auto& [key, value] : this->commandMap) {
                        std::cout << "* " << key << "\t" << value.description << "\n";
                    }

                }
            };

        };

    private:
        std::unordered_map<CommandName, CommandInfo> commandMap;
        T * target;

};
