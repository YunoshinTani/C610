#ifndef C610_H
#define C610_H

#include <mbed.h>

class C610
{
public:

C610(PinName can_rd, PinName can_td, uint16_t can_id = 0x200);

int set_torque(uint8_t motor_num, uint16_t torque);

int read_position(uint8_t motor_num);

int read_torque(uint8_t motor_num);

int read_velocity(uint8_t motor_num);

int read_temperature(uint8_t motor_num);

int position;

int torque;

int velocity;

int temperature;

private:

uint16_t _can_id;
CAN _can;

bool send_data(uint16_t torque1, uint16_t torque2, uint16_t torque3, uint16_t torque4);

bool read_data(const unsigned char *data);

};

#endif // C610_H