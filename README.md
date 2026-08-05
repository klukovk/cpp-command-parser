# cpp-command-parser

## Usage
Import `Parser.hpp` in the project and use it by binding a class.
```cpp
GenericClass gc;
Parser<GenericClass> parser(&gc);
```

In alternative, it is possible to create a custom Parser using inheritance.
This allows to add custom methods, for example in the constructor.
```cpp

class GameParser : public Parser<GenericClass> {

    public:
        GameParser(GenericClass * obj) : Parser<GenericClass>(obj) {

            // Use other commands aside from the basic ones
            addCommand(
                "customCommand",
                [this](stringstream &args) {
                    this->getTarget()->execCustomMethod()


                }

            );

```

After creating the Parser, it's possible to execute the commands by using
`parseAndExecute(stringstream &arg)` method, which takes in the whole input and executes it.
Parser already contains `quit` and `help` commands.
