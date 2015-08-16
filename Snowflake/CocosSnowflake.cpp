//
//  CocosSnowflake.cpp
//

#include "CocosSnowflake.h"
//there is a big difference on windows and gnuc
#ifdef __GNUC__
#include<sys/time.h>
#include<stdio.h>
#define EPOCHFILETIME 11644473600000000ULL
#else
#include<windows.h>
#include<time.h>
#define EPOCHFILETIME 11644473600000000Ui64
#endif

namespace snowflake
{
    uint64_t get_time(){
#ifdef __GNUC__
        struct timeval tv;
        gettimeofday(&tv,NULL);
        uint64_t time = tv.tv_usec;
        time /= 1000;
        time += (tv.tv_sec * 1000);
        return time;
#else
        FILETIME filetime;
        uint64_t time = 0;
        GetSystemTimeAsFileTime(&filetime);
        
        time |= filetime.dwHighDateTime;
        time <<= 32;
        time |= filetime.dwLowDateTime;
        
        time /= 10;
        time -= EPOCHFILETIME;
        return time / 1000;
#endif
    }
    
    
    unique_id_t :: unique_id_t()
    {
        epoch_ = 0;
        time_ = 0;
        machine_ = 0;
        sequence_ = 0;
    }
    
    unique_id_t :: ~unique_id_t(){
        
    }
    
    
    void unique_id_t::set_epoch(uint64_t epoch){
        epoch_ = epoch;
    }
    
    
    void unique_id_t:: set_machine(int32_t machine){
        machine_ = machine;
    }
    
    //create snowflake id, something like uuid
    int64_t unique_id_t :: generate(){
        int64_t value = 0;
        uint64_t time = get_time() - epoch_;
        
        //left 22
        value = time << 22;
        
        //10 bit in the middle is mechine num
        
        value |= (machine_ & 0x3FF) << 12;
        
        //last 12 bit is squenceID
        value |= sequence_++ & 0xFFF;
        
        if (sequence_ == 0x1000){
            sequence_ = 0;
        }
        return value;
    }
}