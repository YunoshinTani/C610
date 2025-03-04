#include "C610.h"

C610::C610(PinName can_rd, PinName can_td, uint16_t can_id) : _can(can_rd, can_td, 1e6) {
    _can_id = can_id;
}

bool C610::send_data(uint16_t torque1, uint16_t torque2, uint16_t torque3, uint16_t torque4) {
    char txBuf[8];
    txBuf[0] = (torque1 >> 8) & 0xFF;
    txBuf[1] = (torque1) & 0xFF;
    txBuf[2] = (torque2 >> 8) & 0xFF;
    txBuf[3] = (torque2) & 0xFF;
    txBuf[4] = (torque3 >> 8) & 0xFF;
    txBuf[5] = (torque3) & 0xFF;
    txBuf[6] = (torque4 >> 8) & 0xFF;
    txBuf[7] = (torque4) & 0xFF;
    CANMessage write_msg(_can_id, txBuf, 8);
    if (_can.write(write_msg)) {
        return true;
    } else {
        return false;
    }
}

bool C610::read_data(const unsigned char *data) {
    CANMessage read_msg;
    unsigned char rxBuf[8];
    if (_can.read(read_msg)) {
        for (uint8_t i=0; i<8; i++) {
            rxBuf[i] = read_msg.data[i];
        }
        position = (int)(rxBuf[0] << 8 | rxBuf[1]);
        torque = (int)(rxBuf[2] << 8 | rxBuf[3]);
        velocity = (int)(rxBuf[4] << 8 | rxBuf[5]);
        temperature = (int)(rxBuf[6]);
        return true;
    } else {
        return false;
    }
}