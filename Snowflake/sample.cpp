snowflake::unique_id_t * u_id_ptr = new snowflake::unique_id_t();
u_id_ptr->set_epoch(uint64_t(1367505795100));
u_id_ptr->set_machine(int32_t(100));

CCLOG("%" PRId64 "\n", u_id_ptr->generate());