
#include "Parser.hpp"
#include <sstream>
#include <string>

using namespace std;

class Player {
    private:
        int points;

    public:
        Player(int totalPoints) : points(totalPoints) {}

        void removePoints(int p) {
            points = points - p;
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
                        this->getTarget()->removePoints(stoi(token));
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

};


int main() {
    Player p(40);
    GameParser gp(&p);
    string input;
    stringstream input_stream;
    bool quit;

    do {
        cout << "Input: \n";

        // Leggi Intero Nome digitato
        getline(cin, input);

        input_stream = stringstream(input);

        quit = gp.parseAndExecute(input_stream);
    } while (!quit);

    return 0;
}
