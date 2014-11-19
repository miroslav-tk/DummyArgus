#include <iostream>  
#include "MsgSerial.h"
#include <cstring>
#include <netinet/in.h>
#include <string.h>
#include <sstream>

namespace argusnet
{

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
    return total_length;
  }
  
  return 0;
}


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
  float val = *((float*)(buffer + length_[0] + length_[1]));
  std::string time(buffer + length_[0] + length_[1] + length_[2],
                   buffer + length_[0] + length_[1] + length_[2] + length_[3]);

  suminfo.hostname = hostname;
  suminfo.content = content;
  suminfo.val = val;
  suminfo.time = time;

  return 0;
}

int MsgBody::Serialize(const SummaryInfo& suminfo)
{
  memset(data_,0,DATA_TOTAL_LENGTH);

  msg_body_len_= GetDataFromSummary(msg_data_,suminfo);
  int offset = 0;
  memcpy(data_ + offset,
         &msg_body_len_,
         sizeof(msg_body_len_));
  offset += sizeof(msg_body_len_);

  memcpy(data_ + offset ,
         length_,
         sizeof(length_));
  offset += sizeof(length_);

  return msg_body_len_ + offset;
}


int MsgBody::Deserialize(SummaryInfo& suminfo)
{

  int offset = 0;
  memcpy(&msg_body_len_,
         data_ + offset,
         sizeof(msg_body_len_));
  offset += sizeof(msg_body_len_);

  memcpy(length_,
         data_ + offset,
         sizeof(length_));
  offset += sizeof(length_);

  GetSummaryFromData(msg_data_,suminfo);
  return msg_body_len_ + offset;
}
}// namespace argusnet
