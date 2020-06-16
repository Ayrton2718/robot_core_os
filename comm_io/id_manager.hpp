#ifndef ID_MANAGER_HPP
#define ID_MANAGER_HPP

#include "comm_io.hpp"
#include "../thread-util/threadutil.hpp"

#include <string>

namespace driver_comm
{

class IdManager
{
private:
    static thread_util::locker                      m_locker;
    static std::unordered_map<byte, std::string>    m_id_map;

    void nolock_set_id(byte id, std::string name);
    std::string nolock_get_devname(byte id);
    bool nolock_isset_id(byte id);

public:
    IdManager(void);

    void IdManager_cons(void);

    void set_id(byte id, std::string name);

    std::string get_devname(byte id);

    bool isset_id(byte id);
};

}

#endif /*ID_MANAGER_HPP*/