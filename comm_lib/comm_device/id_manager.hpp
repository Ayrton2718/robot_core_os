#ifndef COMM_DEVICE_ID_MANAGER_HPP
#define COMM_DEVICE_ID_MANAGER_HPP

#include "comm_io.hpp"
#include "../thread-util/threadutil.hpp"

#include <string>

namespace comm_device
{

class IdManager
{
private:
    static thread_util::locker                          m_locker;
    static std::unordered_map<uint8_t, std::string>     m_id_map;

    static void nolock_set_id(const std::string name, uint8_t id);
    static std::string nolock_get_devname(uint8_t id);
    static bool nolock_isset_id(uint8_t id);

public:
    IdManager(void);

    static void set_id(const std::string name, uint8_t id);

    static uint8_t get_devid(const std::string name);
    static uint8_t isset_devname(const std::string name);

    static std::string get_devname(uint8_t id);
    static bool isset_id(uint8_t id);
};

}

#endif /*COMM_DEVICE_ID_MANAGER_HPP*/