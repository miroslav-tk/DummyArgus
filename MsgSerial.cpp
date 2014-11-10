#include <iostream>  
#include "MsgSerial.h"
#include <cstring>
#include <netinet/in.h>

namespace test
{
  int MsgHeader::Serialize(char* buffer,uint32_t buf_len)
  {
    int offset = 0;
    if (buf_len < MSG_HEADER_LENGTH )
    {
      return -1; 
    }
    if(buffer == NULL)
    {
      return -2;
    }

    memset(buffer,0x00,buf_len);
    offset += nettools::Encode_16(buffer+offset, msg_flag_);
    offset += nettools::Encode_16(buffer+offset, msg_header_len_);
    offset += nettools::Encode_16(buffer+offset, msg_body_len_);
    offset += nettools::Encode_16(buffer+offset, msg_code_);

    return offset;
  }

int MsgHeader::Deserialize(const char* buffer,uint32_t buf_len)
{
  int offset = 0;
  offset += nettools::Decode_16(buffer+offset, msg_flag_);
  offset += nettools::Decode_16(buffer+offset, msg_header_len_);
  offset += nettools::Decode_16(buffer+offset, msg_body_len_);
  offset += nettools::Decode_16(buffer+offset, msg_code_);
  
  return offset;
}

namespace nettools
{
int Encode_16 ( char* buffer, uint16_t data )
{
    uint16_t temp = htons ( data );
    memcpy ( buffer, &temp, sizeof ( temp ) );
    return sizeof ( temp );
}

int Decode_16 ( const char* buffer, uint16_t& data )
{
    uint16_t temp;
    memcpy ( &temp, buffer, sizeof ( temp ) );
    data = ntohs ( temp );
    return sizeof ( data );
}

int Encode_32 ( char* buffer, uint32_t data )
{
    uint32_t temp = htonl ( data );
    memcpy ( buffer, &temp, sizeof ( temp ) );
    return sizeof ( temp );
}

int Decode_32 ( const char* buffer, uint32_t& data )
{
    uint32_t temp;
    memcpy ( &temp, buffer, sizeof ( temp ) );
    data = ntohl ( temp );
    return sizeof ( data );
}
}// namespace nettools
}// namespace test
