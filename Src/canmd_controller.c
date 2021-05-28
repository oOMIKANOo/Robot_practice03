/* 
 * File:    canmd_controller.c
 * version: ver01.00
 * Author:  hajime
 *
 * Created on 2019/03/31, 0:32
 */

#include "canmd_controller.h"

//*********************************************************
//    �O���[�o���ϐ�
//*********************************************************
static int internal_motor_control_data[CANMD_MD_NUM + 1][2];
static int internal_encoder_count[CANMD_MD_NUM + 1][2];
static int present_md_id;

//*****************************************************************************
//    canmd_controller_init
//*****************************************************************************
//  [�T�v]
//    canmd_controller���W���[���̓����ϐ��̏������D
//  [����]
//    �Ȃ�
//  [�߂�l]
//    �Ȃ�
//  [�g�p�O���[�o���ϐ�]
//    internal_motor_control_data (W)
//    internal_encoder_count (W)
//    present_md_id (W)
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
void canmd_controller_init(void)
{
    int i;

    for(i = 0; i < CANMD_MD_NUM + 1; i++) {
        internal_motor_control_data[i][0] = 0;
        internal_motor_control_data[i][1] = 0;
        internal_encoder_count[i][0] = 0;
        internal_encoder_count[i][1] = 0;
    }
    
    present_md_id = 0;

    return;
}

//*****************************************************************************
//    is_appropriate_md_id
//*****************************************************************************
//  [�T�v]
//    MD_ID���K�؂��ǂ����D
//  [����]
//    �Ȃ�
//  [�߂�l]
//    int�^
//    1 : MD_ID�͓K��
//    0 : MD_ID�͕s�K
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
int is_appropriate_md_id(int md_id)
{
    if(md_id >= 1 && md_id <= CANMD_MD_NUM) return 1;
    else return 0;
}

//*****************************************************************************
//    canmd_controller_set_motor_control_data
//*****************************************************************************
//  [�T�v]
//    ���[�^�[�̐�����͂��Z�b�g�D������͈͂̔͂�-1023�`1023�D
//  [����]
//    md_id         : ����Ώ�MD��ID�ԍ�
//    motor_control_data_0: ���[�^�[0�̐������(-1023�`1023)
//    motor_control_data_1: ���[�^�[1�̐������(-1023�`1023)
//  [�߂�l]
//    int�^
//    0 : ����I��
//    -1: �G���[�@�s�K��md_id
//    -2: �G���[�@motor_control_data_1��-1023�`1023�̊Ԃ̒l�łȂ�
//    -3: �G���[�@motor_control_data_2��-1023�`1023�̊Ԃ̒l�łȂ�
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
int canmd_controller_set_motor_control_data(int md_id, int motor_control_data_0, int motor_control_data_1)
{
    if(!is_appropriate_md_id(md_id)) return -1;
    if(motor_control_data_0 < -1023 || motor_control_data_0 > 1023) return -2;
    if(motor_control_data_0 < -1023 || motor_control_data_0 > 1023) return -3;

    internal_motor_control_data[md_id][0] = motor_control_data_0;
    internal_motor_control_data[md_id][1] = motor_control_data_1;

    return 0;
}

//*****************************************************************************
//    canmd_controller_get_encoder_count
//*****************************************************************************
//  [�T�v]
//    �G���R�[�_�̃J�E���g�l�̎擾�D
//  [����]
//    md_id          : �G���R�[�_�J�E���g�l�擾�Ώ�MD��ID�ԍ�
//    encoder_count_0: �G���R�[�_0�̃J�E���g�l���i�[����ϐ��̃|�C���^
//    encoder_count_1: �G���R�[�_1�̃J�E���g�l���i�[����ϐ��̃|�C���^
//  [�߂�l]
//    int�^
//    0 : ����I��
//    -1: �G���[�@�s�K��md_id
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
int canmd_controller_get_encoder_count(int md_id, int *encoder_count_0, int *encoder_count_1)
{
    if(!is_appropriate_md_id(md_id)) return -1;

    *encoder_count_0 = internal_encoder_count[md_id][0];
    *encoder_count_1 = internal_encoder_count[md_id][1];

    return 0;
}

//*****************************************************************************
//    canmd_controller_clear_encoder_count
//*****************************************************************************
//  [�T�v]
//    �G���R�[�_�̃J�E���g�l���N���A����
//  [����]
//    md_id           : �Ώ�MD��ID�ԍ�
//    encoder_num     : �Ώۂ̃G���R�[�_��I������p�����[�^
//                              0: �G���R�[�_0
//                              1: �G���R�[�_1
//  [�߂�l]
//    int�^
//    0 : ����I��
//    -1: �G���[�@�s�K��md_id
//    -2: �G���[�@�s�K��encoder_num
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
int canmd_controller_clear_encoder_count(int md_id, int encoder_num)
{
    if(!is_appropriate_md_id(md_id)) return -1;
    if(encoder_num != 0 && encoder_num != 1) return -2;

    internal_encoder_count[md_id][encoder_num] = 0;

    return 0;
}

//*****************************************************************************
//    canmd_controller_clear_all_encoder_count
//*****************************************************************************
//  [�T�v]
//    �S�ẴG���R�[�_�̃J�E���g�l���N���A����
//  [����]
//    �Ȃ�
//  [�߂�l]
//    �Ȃ�
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
void canmd_controller_clear_all_encoder_count(void)
{
    int i;

    for(i = 0; i < CANMD_MD_NUM + 1; i++) {
    	canmd_controller_clear_encoder_count(i, 0);
    	canmd_controller_clear_encoder_count(i, 1);
    }
   
    return;
}

//*****************************************************************************
//    canmd_controller_set_can_receive_data
//*****************************************************************************
//  [�T�v]
//    CAN�ʐM�Ŏ�M�����f�[�^���Z�b�g�D
//  [����]
//    id      : ID(11�r�b�g)���i�[����Ă���ϐ�
//    dlc     : DLC(4�r�b�g)���i�[����Ă���ϐ�
//    data    : �f�[�^�t�B�[���h���i�[����Ă���z��
//  [�߂�l]
//    int�^
//    0�`3: ��M�f�[�^�̎��
//    -1  : �G���[�@�s�K��id
//    -2  : �G���[�@�s�K��dlc
//  [�g�p�O���[�o���ϐ�]
//    internal_encoder_count (W)
//    present_md_id (R)
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
MdDataType canmd_controller_set_can_receive_data(int id, int dlc, const unsigned char data[])
{
    MdDataType md_data_type;

    if(dlc < 0b0000 || dlc > 0b1111) return -2;

    md_data_type = (data[0] >> 6) & 0b11;

    switch(md_data_type) {
        case MD_DATA_TYPE_PID_GAIN_0:
        case MD_DATA_TYPE_PID_GAIN_1:
        case MD_DATA_TYPE_TIME_PARAM:
            if(dlc != 4) {
                return -2;
            }
            else {

            }
            break;

        case MD_DATA_TYPE_CONTROL_DATA:
            if(dlc != 3) {
                return -2;
            }
            else {
                if((data[0] >> 5 & 1) == 0) {
                    internal_encoder_count[present_md_id][0] += ((data[0] & 0b111000) << 5) | data[1];
                }
                else {
                    internal_encoder_count[present_md_id][0] += (-1 << 11) | (((data[0] & 0b111000) << 5) | data[1]);
                }
                
                if((data[0] >> 2 & 1) == 0) {
                    internal_encoder_count[present_md_id][1] += ((data[0] & 0b111) << 8) | data[2];
                }
                else {
                    internal_encoder_count[present_md_id][1] += (-1 << 11) | (((data[0] & 0b111) << 8) | data[2]);
                }
            }
            break;
    }

    return md_data_type;
}

//*****************************************************************************
//    canmd_controller_get_can_transmit_data
//*****************************************************************************
//  [�T�v]
//    CAN�ʐM�ő��M����f�[�^���擾�D
//  [����]
//    id      : ID(11�r�b�g)���i�[����ϐ��̃|�C���^
//    dlc     : DLC(4�r�b�g)���i�[����ϐ��̃|�C���^
//    data    : �f�[�^�t�B�[���h���i�[����z��
//  [�߂�l]
//    �Ȃ�
//  [�g�p�O���[�o���ϐ�]
//    internal_motor_control_data (R)
//    present_md_id (W)
//  [���l]
//    ���ɂȂ�
//-----------------------------------------------------------------------------
void canmd_controller_get_can_transmit_data(int *id, int *dlc, unsigned char data[])
{
    static enum {
        INIT_ROUTINE,
        CONTROL_ROUTINE,
    } state = INIT_ROUTINE;

    state = CONTROL_ROUTINE;

    // present_md_id �̍X�V
    present_md_id++;
    if(present_md_id > CANMD_MD_NUM) {
        present_md_id = 1;
    }

    switch(state){
        case INIT_ROUTINE:
            break;
        case CONTROL_ROUTINE:

            *id = present_md_id;
            *dlc = 3;
            data[0] = (MD_DATA_TYPE_CONTROL_DATA << 6)
                        | (internal_motor_control_data[present_md_id][0] >> 5 & 0b111000)
                        | (internal_motor_control_data[present_md_id][1] >> 8 & 0b111);
            data[1] = internal_motor_control_data[present_md_id][0] & 0XFF;
            data[2] = internal_motor_control_data[present_md_id][1] & 0XFF;
            
            break;
    }

    return;
}
