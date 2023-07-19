#include "reassembler.hh"
#include <assert.h>
#include <iostream>

using namespace std;

Reassembler::Reassembler() : inner_storage(), status(), index(0), stored(0), capacity(1000000), is_last(false)  {
  inner_storage.resize(capacity);
  inner_storage.reserve(capacity);
  fill(inner_storage.begin(), inner_storage.end(), 0);
  status.resize(capacity);
  status.reserve(capacity);
  fill(status.begin(), status.end(), 0);
}

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring, Writer& output )
{
  // Fill in the data segment into the reassembler
  uint64_t stream_capacity = output.available_capacity();
  for(uint64_t i = max(first_index, index); i - first_index < data.size() && i < index + stream_capacity; i++){
    inner_storage[i % capacity] = data[i - first_index];
    if(status[i % capacity] == 0){
      status[i % capacity] = 1;
      ++stored;
    }
  }

  // pop the data out from the reassembler
  if(first_index <= index && first_index + data.size() > index){
    string segment = "";
    while(true){
      if(status[index % capacity] == 0){
        break;
      }
      segment.push_back(inner_storage[index % capacity]);
      status[index++ % capacity] = 0;
      --stored;
    }
    output.push(segment);
  }

  if(is_last_substring) is_last = true;
  if(is_last && !stored) {
    output.close();
  } 
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return stored;
}
