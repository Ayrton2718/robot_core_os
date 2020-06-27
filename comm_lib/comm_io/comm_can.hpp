#ifndef COMM_IO_COMM_CAN_HPP
#define COMM_IO_COMM_CAN_HPP

#include <stdio.h>


namespace comm_io
{

class CommCan
{
public:
    CommCan(void);

    bool send(const struct comm_frame_t* frame);

    bool read_rxbuf1(struct comm_frame_t* frame);
    bool read_rxbuf2(struct comm_frame_t* frame);
};

}

#endif /*COMM_IO_COMM_CAN_HPP*/