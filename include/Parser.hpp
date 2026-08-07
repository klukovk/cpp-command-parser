
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>


using CommandName = std::string;
using CommandMethod = std::function<void(std::stringstream& args)>;

class ParserException : public std::runtime_error {
    public:
        ParserException(const std::string &arg) : std::runtime_error(arg) {}
};


template <class T>
class Parser {

    public:
        Parser(T * target)  : target(target) {
            loadBasicCommands();
        }

        ~Parser() {}


        bool parseAndExecute(std::stringstream &input_stream) {

            std::string command;

            input_stream >> command;

            std::cout << "\n";
            if (!(command == "quit"))
            {
                auto func = commandMap.find(command);

                if (func != commandMap.end())
                {
                    try {
                        func->second(input_stream);
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


        void addCommand(const CommandName &name, const CommandMethod &func)  {
            commandMap.insert({name, func});
        }

        T * getTarget() {
            return target;
        }

    private:
        void loadBasicCommands() {

            commandMap["help"] = [this](std::stringstream &args) {

                std::cout << "List of Commands:\n\n";
                std::cout << "* quit" << "\n";

                for (const auto& [key, value] : this->commandMap) {
                    std::cout << "* " << key << "\n";
                }
            };

        }

    private:
        std::unordered_map<CommandName, CommandMethod> commandMap;
        T * target;

};
