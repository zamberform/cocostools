//
//  CocosSnowflake.h
//

#include <stdint.h>

namespace snowflake
{
    //twitter snowflake method
    //64            63------------------22---------------------12------0
    //uint64_t |    41bit timestamp   | 10 bit mechine number| 12 bit sequece which is increasing|
    
    extern uint64_t get_time();
    
    class unique_id_t{
    public:
        unique_id_t();
        ~unique_id_t();
        
        void set_epoch(uint64_t epoch);
        void set_machine(int32_t machine);
        
        int64_t generate();
    private:
        uint64_t epoch_;
        uint64_t time_;
        uint64_t machine_;
        int32_t sequence_;
    };
    
}
