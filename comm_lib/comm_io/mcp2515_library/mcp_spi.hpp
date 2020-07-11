#ifndef MCP_SPI_HPP
#define MCP_SPI_HPP

#include <stdint.h>
#include <time.h>

namespace mcp_comm_lib
{

class McpSpi
{
private:
    int m_hundle;

    static const uint8_t m_mode = 0;

    static time_t m_offset;

public:
    McpSpi(void);

    static void initializer(void);

    bool constructor(uint8_t ss_pin, uint32_t speed);

    void write(uint8_t* buffer, uint8_t len);

    void read_write(uint8_t* send_buffer, uint8_t* read_buffer, uint8_t len);

    static void wait_ms(uint8_t ms);

    static float now_time(void);
};

}

#endif /*MCP_SPI_HPP*/