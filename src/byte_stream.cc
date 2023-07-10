#include <stdexcept>
// #include <iostream>

#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity )
  , current_capacity( 0 )
  , is_eof( false )
  , is_err( false )
  , total_in( 0 )
  , total_out( 0 )
  , db()
{}

void Writer::push( string data )
{
  // Your code here.
  uint64_t length = data.size();
  if ( data[length - 1] == '\0' ) {
    is_eof = true;
  }
  uint64_t read_in = min( length, capacity_ - current_capacity );
  current_capacity += read_in;
  total_in += read_in;
  for ( uint64_t i = 0; i < read_in; i++ ) {
    db.emplace( data[i] );
  }
}

void Writer::close()
{
  // Your code here.
  is_eof = true;
}

void Writer::set_error()
{
  // Your code here.
  is_err = true;
}

bool Writer::is_closed() const
{
  // Your code here.
  return is_eof;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - current_capacity;
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return total_in;
}

string_view Reader::peek() const
{
  // Your code here.
  return string_view( &db.front(), 1 );
}

bool Reader::is_finished() const
{
  // Your code here.
  return is_eof && !( current_capacity );
}

bool Reader::has_error() const
{
  // Your code here.
  return is_err;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  // cout << "pop" << endl;
  for ( uint64_t i = 0; i < len; i++ ) {
    if ( current_capacity ) {
      db.pop();
      ++total_out;
      --current_capacity;
    } else
      break;
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return current_capacity;
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  // cout << "bytes_popped" << endl;
  return total_out;
}
