#include <iostream>  
#include "MsgSerial.h"
#include <cstring>
#include <netinet/in.h>
#include <string.h>
#include <sstream>

namespace test
{
//int MsgHeader::Serialize(char* buffer,uint32_t buf_len)
//{
  //int offset = 0;
  //if (buf_len != MSG_HEADER_LENGTH )
  //{
    //return -1; 
  //}
  //if(buffer == NULL)
  //{
    //return -2;
  //}

  //memset(buffer,0x00,buf_len);
  //offset += nettools::Encode_16(buffer+offset, msg_flag_);
  //offset += nettools::Encode_16(buffer+offset, msg_header_len_);
  //offset += nettools::Encode_16(buffer+offset, msg_body_len_);
  //offset += nettools::Encode_16(buffer+offset, msg_code_);

  //return offset;
//}

//int MsgHeader::Deserialize(const char* buffer,uint32_t buf_len)
//{
  //int offset = 0;
  //offset += nettools::Decode_16(buffer+offset, msg_flag_);
  //offset += nettools::Decode_16(buffer+offset, msg_header_len_);
  //offset += nettools::Decode_16(buffer+offset, msg_body_len_);
  //offset += nettools::Decode_16(buffer+offset, msg_code_);

  //return offset;
//}


int MsgBody::GetDataFromSummary(char* buffer,
                                const SummaryInfo& suminfo)
{
  if (buffer == NULL)
  {
    return -1; 
  }
  length_[0] = suminfo.hostname.size();
  length_[1] = suminfo.content.size();
  length_[2] = sizeof(suminfo.val);
  length_[3] = suminfo.time.size();

  uint32_t total_length = length_[0] + length_[1] + length_[2] + length_[3] + 1;

  if (total_length > MSG_DATA_MAX_LENGTH)
  {
    return -2; 
  }
  else
  {
    memcpy(buffer,
           suminfo.hostname.data(),
           suminfo.hostname.size());
    memcpy(buffer + length_[0],
           suminfo.content.data(),
           suminfo.content.size());
    memcpy(buffer + length_[0] + length_[1],
           &(suminfo.val),
           sizeof(suminfo.val));
    memcpy(buffer  + length_[0] + length_[1] + length_[2],
           suminfo.time.data(),
           suminfo.time.size());
    memset(buffer  + length_[0] + length_[1] + length_[2] + length_[3],
           0, //字符串结尾符
           1); //一字节
    //int aligned_length;
    //if(total_length%32 == 0)
    //{
      //aligned_length = total_length/32;
    //}
    //else
    //{
      //aligned_length = total_length/32 + 0x20;  
    //}
    
    //return aligned_length;
    return total_length;
  }
  
  return 0;
}

//int LengthAligned(const uint32_t length,const uint32_t aligned_byte)
//{
  //int aligned_length=0;
  //if(length % aligned_byte == 0)
  //{
    //aligned_length =  length / aligned_byte;
  //}
  //else
  //{

  //}
//}
int MsgBody::GetSummaryFromData(const char* buffer,
                                SummaryInfo& suminfo)
{
  if(buffer == NULL)  
  {
    return -1;
  }

  std::string hostname(buffer + 0 ,
                       buffer + length_[0]);
  std::string content(buffer + length_[0],
                      buffer + length_[0] + length_[1]);
  float val = *(buffer + length_[0] + length_[1]);
  std::string time(buffer + length_[0] + length_[1] + length_[2],
                   buffer + length_[0] + length_[1] + length_[2] + length_[3]);

  suminfo.hostname = hostname;
  suminfo.content = content;
  suminfo.val = val;
  suminfo.time = time;

  return 0;
}

int MsgBody::Serialize(std::string& serialized_str,
                       const SummaryInfo& suminfo)
{
  std::stringstream stream;
  char data[MSG_DATA_MAX_LENGTH + 4*4 +4];
  int offset = 0;
  offset += memcpy((char*)data + offset ,&msg_body_len_,sizeof(msg_body_len_));


  char msg_data[MSG_DATA_MAX_LENGTH];
  msg_body_len_= GetDataFromSummary(msg_data,suminfo);
  msg_data_ =msg_data;
  stream  << msg_body_len_
          << length_[0]
          << length_[1]
          << length_[2]
          << length_[3]
          << msg_data_;
  serialized_str = stream.str();
  return serialized_str.size();
}


int MsgBody::Deserialize(const std::string& deserialized_str,
                         SummaryInfo& suminfo)
{

}
/*namespace nettools*/
//{

//int EncodeBianryArray(char* buffer_out,
                      //uint32_t buffer_out_length,
                      //const char* buffer_in,
                      //const uint32_t buffer_in_length)
//{ 
  //if(buffer_out_length > buffer_in_length)
  //{
    //return -1;
  //}

//}
//int Encode_32 ( char* buffer, uint32_t data )
//{
  //uint32_t temp = htonl ( data );
  //memcpy ( buffer, &temp, sizeof ( temp ) );
  //return sizeof ( temp );
//}

//int Decode_32 ( const char* buffer, uint32_t& data )
//{
  //uint32_t temp;
  //memcpy ( &temp, buffer, sizeof ( temp ) );
  //data = ntohl ( temp );
  //return sizeof ( data );
//}
/*}*/// namespace nettools
}// namespace test
