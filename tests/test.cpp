

#include "Parser.hpp"
#include <sstream>

using namespace std;

class GenericClass {

};

void test_method_non_exist() {
    GenericClass gc;
    Parser<GenericClass> parser(&gc);

    CommandName command = "Non-Existing Command";

    stringstream nonExistingCommand = stringstream(command);

    cout << "Executing : " << command;
    parser.parseAndExecute(nonExistingCommand);
}

int main() {

    cout << "Starting Tests...\n";

    test_method_non_exist();



    return 0;
}
