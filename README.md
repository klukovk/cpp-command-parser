# cpp-command-parser

## Usage
Import `Parser.hpp` in the project and use it by binding a class.
```cpp
GenericClass gc;
Parser<GenericClass> parser(&gc);
```

In alternative, it is possible to create a custom Parser using inheritance.
This allows to add custom methods at instantiation time
```cpp

class GameParser : public Parser<GenericClass> {

    public:
        GameParser(GenericClass * obj) : Parser<GenericClass>(obj) {

            // Use other commands aside from the basic ones
            addCommand(
                "customCommand",
                [this](stringstream &args) {

                    // Given that GenericClass contains execCustomMethod()
                    this->getTarget()->execCustomMethod()


                }

            );

int main() {
    GenericClass c;
    GameParser parser = GameParser(&c);

    stringstream s = string("customCommand")

    parser.parseAndExecute(s);
}

```

After creating the Parser, it's possible to execute the commands by using
`parseAndExecute(stringstream &arg)` method, which takes in the whole input and executes it.
Parser already contains `quit` and `help` commands.
