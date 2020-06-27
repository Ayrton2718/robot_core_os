# thread-util
For communication library between threads.  
This library have 5 features. You can use theare without mutex locker.  
But you cannot set a pointer. If set a pointer, you have to use mutex locker.

You can set a key when call constructors of thread-util.  
Thread_util sync with others that have the same key as mine.  
So, you have to set same key that you want to connect at constructors.  

# contents
* [Share](#Share)
* [Signal](#Signal)
* [Queue](#Queue)
* [Callback](#Callback)


# Share
You can share variables between threads when use this.
## examples
```c++
#include "threadutil.h"

void write_thread(void)
{
    thread_util::Share<int> write("mot_power");
    write.write(100); 
}

void read_thread(void)
{
    thread_util::Share<int> read("mot_power");
    print("%d\n", read.read())
    //100
}

int main(void)
{
    run(write_thread);  // start send thread.
    run(read_thread);  // read send thread.
}
```


# Signal
You can send signal with variables to other threads.
## examples
```c++
#include "threadutil.h"

enum deployment_status{
    max=0,
    middle=1,
    min=2
};

void send_thread(void)
{
    thread_util::SignalSender<deployment_status> send("start_deployment");
    send.broadcast(deployment_status::max); 
}

void receiver_thread(void)
{
    thread_util::SignalSender<deployment_status> receiver("start_deployment");
    deployment_status deploy_status = read.wait();
    printf("%d\n", deploy_status);
    //0
}

int main(void)
{
    run(send_thread);  // start send_thread thread.
    run(receiver_thread);  // read receiver_thread thread.
}
```


# Queue
This queue sync between threads.
## examples
```c++
#include "threadutil.h"

struct pos_t
{
    int x;
    int y;
};

void push_thread(void)
{
    thread_util::QueueSetter<struct pos_t> pusher("target_pos");
    
    struct pos_t target_pos;
    target_pos.x = 100;
    target_pos.y = 20;
    pusher.add(target_pos);

    target_pos.x = 200;
    target_pos.y = 100;
    pusher.add(target_pos);
}

void pop_thread(void)
{
    thread_util::QueueReader<struct pos_t> reader("target_pos");

    while (reader.size() > 0)
    {
        thread_util::locker::yield();
    }
    struct pos_t next_pos = reader.poll(); // x = 100, y = 20

    while (reader.size() > 0)
    {
        thread_util::locker::yield();
    }
    struct pos_t next_pos = reader.poll(); // x = 200, y = 100

    struct pos_t next_pos = reader.poll(); // x = 0, y = 0
}

int main(void)
{
    run(push_thread);  // start push_thread thread.
    run(pop_thread);  // read pop_thread thread.
}
```

# CallBack
You can call function of other thread.
## examples
```c++
#include "threadutil.h"

struct pos_t
{
    int x;
    int y;
};

void call_thread(void)
{
    thread_util::CallbackCall<struct pos_t, void>  call("move");
    
    struct pos_t pos;
    pos.x = 100;
    pos.y = 20;
    call.call(pos);
}

void func(struct pos_t pos)
{
    print("%d, %d\n", pos.x, pos.y);    // 100, 20
}

void called_thread(void)
{
    thread_util::CallbackReply<struct pos_t, int> reply("move", func);

    reply.wait();  // wait until it got a call order. 
}

int main(void)
{
    run(call_thread);  // start push_thread thread.
    run(called_thread);  // read pop_thread thread.
}
```