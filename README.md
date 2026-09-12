# cpp-command-parser
1. [In General](#in-general)
2. [How it works](#how-it-works)
3. [Usage](#usage)
4. [Final Notes](#final-notes)
5. [Attribution](#attribution)




## In General
`Parser` helps the user to use class methods through CLI

## How it works
`Parser` is a class that contains a pointer to an object called `target` and a command map of <`CommandName`,`CommandInfo`>.

`ParserException` has been created in order to help the user to throw a specific error when parsing the CLI command. The discussion on how to manage errors will be given below.

The methods are executed by `parseAndExceute` method, which requires in input the full string typed by the user as a `stringstream`. Keep in mind that the first string in the stream has to be the command, and all thw followin strings pattern can be decided by the users (the parsing will be organized in the lambda functions associated to the commands, and he will decide how to manage flags and other things).

> `parseAndExceute` returns true if it is necessary to quit the program

### The Command Map

Each `CommandInfo` contains: 
- A description
  - The description that the users wants to show when requiring info about that command when using `help` in CLI
- A map of <flag, description> which contains each flag that the command supports
- A lambda function
  - The lambda function will be called when typing the command in terminal. It requires the `stringstream` as input, which helps the user to parse the flags and the arguments typed in CLI

### The Target
The parser keeps track of an object called `target` as reference. In this way, when the users will add new commands to the list, when implementing the lambda function associated it will be possible to call a method belonging to target.
Storing the `target` avoids to implement methods directly inside the lambda functions.

### The Lambda Function
Lambda functions are functions that are executed when calling the command they are associated to. A few considerations:
1. They require a `stringstream` as input. 
    - This will contain all the string typed by the user aside from the `CommandName`. If the command requires arguments, it will be possible to access to them by parsing the `stringstream`.
2. It is possible to call all the `target` methods.
    - As already discussed above, the parser contains a pointer to a `target`. This means that the parser can access to target and call his methods through the lambda functions.
3. Parsing errors
    - If the users wants to manage errors during parsing in lambda function, he can write `throw ParserException`. The parser already has a guarded zone in `parseAndExecute` and so he will print the error that has been found during parsing of that command.

### Adding New Methods

To create a new command to be called in cli, it is necessary to add it through the `addCommand()` method, passing as input:
- a name for that command (`ComandName`)
- all the infos required above to associate to a `CommandInfo`.

Further Examples discussed in [Usage](#usage)



`Parser` already contains these commands: `help` and `quit`:
- `help` prints on cli a list of commands that has been added until that moment and their description. `help` itself is a command, so it has a lambda function to be called
- `quit` is used to quit the program. Keep in mind that this **DOESN'T** have a lambda function. The parser will just check that if the command is `quit` then the `parseAndExecute()` will return `false` and so the user will know that it's necessary to quit the program.


## Usage
Import `Parser.hpp` in the project and use it by binding a target as discussed above.

```cpp

// Target of The Parser
GenericClass gc;

// Parser targetting GenericClass
Parser<GenericClass> parser(&gc);

```

In alternative, it is possible to create a custom Parser using inheritance.
This allows the user to add custom methods in the list at constructor time, avoiding using `addCommand` outside the Parser context

```cpp
class GameParser : public Parser<GenericClass> {

    public:
        GameParser(GenericClass * obj) : Parser<GenericClass>(obj) {

            addCommand(
                // Name of the command
                "customCommand",
                CommandInfo{
                    // Put a Description
                    .description = "Custom Command Description",

                    // Put all flags accepted + densription
                    .flagsMap = {
                        "-f",
                        "Flag Description"
                    },

                    // Put the method associated to customCommand. 
                    // In alternative, call a method on target
                    .func = [this](stringstream &args) {

                        cout << "Executing Custom Command!";
                        
                        this->getTarget()->execCustomMethod();
                    }
                }
            );

int main() {
    GenericClass c;
    GameParser parser = GameParser(&c);

    stringstream s = string("customCommand")

    parser.parseAndExecute(s);
}
```

Keep in mind that `parseAndExecute == true` <=> the command was `quit`


## Final Notes
This project was created to provide a simple yet useful CLI parser, avoiding complex and hard-to-read boilerplate code. 
I tried to keep the architecture as straightforward as possible. 
I would highly appreciate any issue tickets or reports regarding code bugs, missing features, or documentation improvements!

## Attribution
If you use this library in your own project, a link back to this repository or a mention in your project's credits is greatly appreciated!
