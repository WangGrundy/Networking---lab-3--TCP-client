#include <iostream>
#include <sstream>
#include <string>

#include "socklib.h"

std::string do_client(std::istream& in_stream);
int run_test();

int main(int argc, char* argv[]) {
    SockLibInit(); //for windows



    /* TODO: ADD SETUP CODE HERE */

    return run_test();
}

std::string do_client(std::istream& in_stream) {
    /* TODO: ADD FUNCTION IMPLEMENTATION HERE */

      //Create a socket, and connect to the server at IP ADDRESS 68.183.63.165 and PORT 7778.
    Socket socket(Socket::Family::INET, Socket::Type::STREAM);
    std::string str_address("68.183.63.165");
    Address address(str_address);
    socket.Connect(address, 7778);

    //Create a string to send to the server using the build_string() function(described below).
    std::string msgSent;

    //Send a properly - formatted sort string to the server.
    std::string msg((char*)&in_stream); //or "LIST 5 4 3 2 1"
    size_t nbytes_sent = socket.Send(msg.data(), msg.size());

    //Receive the server's response.
    char buffer[4096];
    size_t nbytes_recved = socket.Recv(buffer, sizeof(buffer));

    //Create a std::string from the server's response and return it.
    std::string msgRecieed(buffer, nbytes_recved);

    std::cout << "HELLO\n;";

    return msgRecieed;
}

std::string build_string(std::istream& in_stream) {
    /* TODO (optional): implement this function */

      //Get a line from the given istream.
      //std::string line = in_stream.getline(in_stream);

      //Take a line of input from the given istream and parse it into an integer(if it is an integer) or a float(if it is a float).
    int lineInt;
    float lineFloat;

    //Add the parsed number to a string, which will ultimately be sent to the server.
    std::string msg;

    //When the user enters the string done, the string is complete and should be returned.
    std::string ans = "";
    while (ans != "done") {
        std::cin >> ans;
    }

    return msg;
}

int run_test() {
    std::stringstream input("30\n500\n-12\n3.6\n"
        "not a number\n200also not a number\n"
        "88.1\ndone");

    std::cout << "Testing on input '" << input.str() << "'.\n";

    std::string msg = do_client(input);
    std::string expected("SORTED -12 3.6 30 500 88.1");
    std::cout << "do_client() returned '" << msg << "'.\n";

    if (msg != expected) {
        std::cout << "TEST FAILED. Expected '" << expected << "' but was '" << msg
            << "'.\n";
        return 1;
    }

    std::cout << "Recieved expected message '" << msg << "'. Test passed 😄\n";
    return 0;
}
