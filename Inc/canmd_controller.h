/* 
 * File:    canmd_controller.h
 * version: ver01.00
 * Author:  hajime
 *
 * Created on 2019/03/31, 0:29
 */
#ifndef CANMD_MANAGER_H
#define CANMD_MANAGER_H

#define CANMD_MD_NUM 4

typedef enum tag_MdDataType {
    MD_DATA_TYPE_PID_GAIN_0 = 0b00,
    MD_DATA_TYPE_PID_GAIN_1 = 0b01,
    MD_DATA_TYPE_TIME_PARAM = 0b10,
    MD_DATA_TYPE_CONTROL_DATA = 0b11,
} MdDataType;

void canmd_controller_init(void);
int is_appropriate_md_id(int md_id);
int canmd_controller_set_motor_control_data(int md_id, int motor_control_data_0, int motor_control_data_1);
int canmd_controller_get_encoder_count(int md_id, int *encoder_count_0, int *encoder_count_1);
int canmd_controller_clear_encoder_count(int md_id, int encoder_num);
void canmd_controller_clear_all_encoder_count(void);
MdDataType canmd_controller_set_can_receive_data(int id, int dlc, const unsigned char data[]);
void canmd_controller_get_can_transmit_data(int *id, int *dlc, unsigned char data[]);

#endif /* CANMD_MANAGER_H */
