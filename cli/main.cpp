#include <iostream>
#include <unistd.h>
#include "../lib/Board.h"
#include "../lib/Connector.h"
#include <map>
#include <locale>

const int PLAYER_COLOR = 1;

std::map<std::string, int> ports {{"white", 5800},{"black",5801}};

int main(int argc, char **argv) {
    std::string player_color;
    if (argc < 2) {
        std::cout << "Missing Player Color {Black|White}" << std::endl;
        std::cout << "Starting as white" << std::endl;
        player_color= "white";
    } else {
        player_color = std::string(argv[PLAYER_COLOR]);
    }

    std::cout << "Hello, World!" << std::endl;
    Board b;
    b.load_board("{\"board\":[[\"EMPTY\",\"EMPTY\",\"EMPTY\",\"BLACK\",\"BLACK\",\"BLACK\",\"EMPTY\",\"EMPTY\",\"EMPTY\"],[\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"BLACK\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\"],[\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"WHITE\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\"],[\"BLACK\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"WHITE\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"BLACK\"],[\"BLACK\",\"BLACK\",\"WHITE\",\"WHITE\",\"KING\",\"WHITE\",\"WHITE\",\"BLACK\",\"BLACK\"],[\"BLACK\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"WHITE\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"BLACK\"],[\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"WHITE\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\"],[\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"BLACK\",\"EMPTY\",\"EMPTY\",\"EMPTY\",\"EMPTY\"],[\"EMPTY\",\"EMPTY\",\"EMPTY\",\"BLACK\",\"BLACK\",\"BLACK\",\"EMPTY\",\"EMPTY\",\"EMPTY\"]],\"turn\":\"WHITE\"}");
    std::cout << b;

    Connector connector{ports[player_color]};
    connector.send_name("Pippo");

    b.load_board(connector.receive_string());
    std::cout << b << std::endl;

    while (true) {
        std::string from;
        std::string to;

        std::cout << "From To" << std::endl;
        std::cin >> from >> to;

        std::string move {"{\"from\":\""+from+"\",\"to\":\""+to+"\",\"turn\":\"WHITE\"}"};
        std::cout << move << std::endl;
        connector.send_string(move);

        b.load_board(connector.receive_string());
        std::cout << b << std::endl;

        b.load_board(connector.receive_string());
        std::cout << b << std::endl;
    }

}