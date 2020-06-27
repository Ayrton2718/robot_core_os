#ifndef COMM_IO_COMM_TYPE_HPP
#define COMM_IO_COMM_TYPE_HPP

typedef unsigned char byte;

#define CAN_UNKNOWN_ID (0x00)

namespace comm_io
{

struct comm_frame_t
{
    byte                id;
    byte                data_len;
    byte                data[8];
};

}

#endif /*COMM_IO_COMM_TYPE_HPP*/