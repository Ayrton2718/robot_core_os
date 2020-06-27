#include "comm_thread.hpp"

#include "../thread-util/threadutil.hpp"
#include "comm_type.hpp"
#include "comm_can.hpp"
#include "comm_interface.hpp"

namespace comm_io
{

void comm_thread(void)
{
    CommCan comm_io;
    thread_util::QueueReader<struct comm_frame_t> comm_order("comm_send");
    thread_util::QueueSetter<struct comm_frame_t> comm_readraw("comm_readraw");

    while(true)
    {
        if(0 < comm_order.size())
        {
            struct comm_frame_t send_frame = comm_order.poll();
            if(send_frame.id != CAN_UNKNOWN_ID)
            {
                comm_io.send(&send_frame);
            }
        }

        struct comm_frame_t rec_frame;
        if(true == comm_io.read_rxbuf1(&rec_frame))
        {
            comm_readraw.add(rec_frame);
        }

        if(true == comm_io.read_rxbuf2(&rec_frame))
        {
            comm_readraw.add(rec_frame);
        }

        thread_util::locker::yield();
    }
}

void sensor_thread(void)
{
    thread_util::QueueReader<struct comm_frame_t> comm_readraw("comm_readraw");

    CommReader data_lib;

    while(true)
    {
        if(0 < comm_readraw.size())
        {
            struct comm_frame_t read_data;
            read_data = comm_readraw.poll();

            data_lib.set_data(read_data.id, read_data.data, read_data.data_len);
        }else{
            thread_util::locker::yield();
        }
    }
}

void comm_io_start(void)
{
    thread_util::Launcher comm_launch(comm_thread);

    thread_util::Launcher sensor_launch(sensor_thread);
}

}
