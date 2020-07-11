#include "mcp_spi.hpp"

#include <stdio.h>
#include <pigpio.h>
#include <sys/time.h>

namespace mcp_comm_lib
{

time_t McpSpi::m_offset;

McpSpi::McpSpi(void)
{
    this->m_hundle = 0;
}

void McpSpi::initializer(void)
{
    struct timeval now_time;
    gettimeofday(&now_time, NULL);

    m_offset = now_time.tv_sec;
}

bool McpSpi::constructor(uint8_t ss_pin, uint32_t speed)
{
    this->m_hundle = spiOpen(ss_pin, speed, this->m_mode);
    if(this->m_hundle != ss_pin)
    {
        printf("spi open failed!\n");
        return false;
    }

    return true;
}

void McpSpi::write(uint8_t* buffer, uint8_t len)
{
    spiWrite(this->m_hundle, (char*)buffer, len);
}

void McpSpi::read_write(uint8_t* send_buffer, uint8_t* read_buffer, uint8_t len)
{
    spiXfer(this->m_hundle, (char*)send_buffer, (char*)read_buffer, len);
}

void McpSpi::wait_ms(uint8_t ms)
{
    struct timespec req = {
        ms / 1000,
        (ms % 1000) * 1000000
    };

    nanosleep(&req, NULL);
}

float McpSpi::now_time(void)
{
    struct timeval now_time;
    gettimeofday(&now_time, NULL);

    return (now_time.tv_sec - m_offset) + ((float)now_time.tv_usec / 1000000);
}

}