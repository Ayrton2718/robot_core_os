#ifndef COMM_IO_HPP
#define COMM_IO_HPP

#include <stdio.h>

typedef unsigned char byte;

namespace driver_comm
{

struct comm_frame_t
{
    byte                id;
    byte                data_len;
    byte                data[8];
};

class CommIo
{
public:
    CommIo(void);

    bool send(const struct comm_frame_t* frame);

    bool read_rxbuf1(struct comm_frame_t* frame);
    bool read_rxbuf2(struct comm_frame_t* frame);
};

}

#endif /*COMM_IO_HPP*/