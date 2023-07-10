#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  cerr << "Warning: get_URL() has not been implemented yet.\n";
  Address my_url( host, "http" );
  TCPSocket my_socket;
  my_socket.connect( my_url );
  my_socket.write( "GET " );
  my_socket.write( path );
  my_socket.write( " HTTP/1.1\r\nHost: " );
  my_socket.write( host );
  my_socket.write( "\r\nConnection: close\r\n\r\n" );
  string result;
  while ( true ) {
    my_socket.read( result );
    cout << result;
    if ( my_socket.eof() )
      break;
  }
  my_socket.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
