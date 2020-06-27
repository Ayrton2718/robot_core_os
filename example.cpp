#include "comm_lib/comm_device/comm_device.hpp"

int main(void)
{
    comm_device::IdManager::set_id("flont_motor", 0x51);
    comm_device::IdManager::set_id("right_switch", 0x24);

    // ID 0x51のモータドライバとの通信開始。
    comm_device::DCMotor front("flont_motor");

    // ID 0x24のスイッチドライバとの通信開始。スイッチの番号は0。
    comm_device::Switch right_sw("right_switch", 0);

    if(right_sw.get_status())
    {
        //押されたとき
        front.set_power(50);    //前に50%で回転
    }else{
        front.set_power(-50);   //後ろにに50%で回転
    }
}