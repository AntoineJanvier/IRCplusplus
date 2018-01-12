#include "src/ServerSocket.h"
#include "src/SocketException.h"
#include <string>
#include <iostream>

using namespace std;

int main ( int argc, int argv[] ) {
    cout << "running..." << endl;

    try {
        // Create the socket
        ServerSocket server ( 30000 );
        while (true) {
            ServerSocket new_sock;
            server.accept ( new_sock );
            try {
                while (true) {
                    string data;
                    new_sock >> data;
                    new_sock << data;
                }
            } catch ( SocketException& ) {}
        }
    }
    catch (SocketException& e) {
        cout << "Exception was caught: " << e.description() << endl << "Exiting." << endl;
    }
    return 0;
}