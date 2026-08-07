
#include "Parser.hpp"
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;


class PlayerException : public std::runtime_error {
    public:
        PlayerException(const std::string &msg) : std::runtime_error(msg) {}
};

class Player {
    private:
        int points;

    public:
        Player(int totalPoints) : points(totalPoints) {}

        void removePoints(int p) {
            if (p >= 0)
                points = points - p;
            else
                throw PlayerException("Cant Remove Negative Points");
        }

        int getPoints() {
            return points;
        }
};


class GameParser : public Parser<Player> {

    public:
        GameParser(Player * p) : Parser<Player>(p) {
            addCommand(
                "removePoints",
                [this](stringstream &args) {
                    int totalPoints;
                    string token;

                    if (args >> token) {
                        try {
                            totalPoints = stoi(token);
                            this->getTarget()->removePoints(totalPoints);
                        }
                        catch (invalid_argument &e) {
                            throw ParserException("Specified Points not valid as Integer");
                        }
                        catch (PlayerException &e) {
                            throw ParserException(e.what());
                        }

                    }
                    else {
                        this->getTarget()->removePoints(0);
                    }




                }

            );

            addCommand(
                "showPoints",
                [this](stringstream &args) {
                    cout << "\n";
                    cout << "Points: " << this->getTarget()->getPoints();
                    cout << "\n";
                }

            );
        }


        ~GameParser() {};

};


int main() {
    Player p(40);
    GameParser gp(&p);
    string input;
    stringstream input_stream;
    bool quit;

    do {
        cout << "\nInput: \n";

        // Leggi Intero Nome digitato
        getline(cin, input);

        input_stream = stringstream(input);

        quit = gp.parseAndExecute(input_stream);
    } while (!quit);

    return 0;
}
