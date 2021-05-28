/* 
 * File:    canmd_controller.c
 * version: ver01.00
 * Author:  hajime
 *
 * Created on 2019/03/31, 0:32
 */

#include "canmd_controller.h"

//*********************************************************
//    グローバル変数
//*********************************************************
static int internal_motor_control_data[CANMD_MD_NUM + 1][2];
static int internal_encoder_count[CANMD_MD_NUM + 1][2];
static int present_md_id;

//*****************************************************************************
//    canmd_controller_init
//*****************************************************************************
//  [概要]
//    canmd_controllerモジュールの内部変数の初期化．
//  [引数]
//    なし
//  [戻り値]
//    なし
//  [使用グローバル変数]
//    internal_motor_control_data (W)
//    internal_encoder_count (W)
//    present_md_id (W)
//  [備考]
//    特になし
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
//  [概要]
//    MD_IDが適切かどうか．
//  [引数]
//    なし
//  [戻り値]
//    int型
//    1 : MD_IDは適切
//    0 : MD_IDは不適
//  [備考]
//    特になし
//-----------------------------------------------------------------------------
int is_appropriate_md_id(int md_id)
{
    if(md_id >= 1 && md_id <= CANMD_MD_NUM) return 1;
    else return 0;
}

//*****************************************************************************
//    canmd_controller_set_motor_control_data
//*****************************************************************************
//  [概要]
//    モーターの制御入力をセット．制御入力の範囲は-1023～1023．
//  [引数]
//    md_id         : 制御対象MDのID番号
//    motor_control_data_0: モーター0の制御入力(-1023～1023)
//    motor_control_data_1: モーター1の制御入力(-1023～1023)
//  [戻り値]
//    int型
//    0 : 正常終了
//    -1: エラー　不適なmd_id
//    -2: エラー　motor_control_data_1が-1023～1023の間の値でない
//    -3: エラー　motor_control_data_2が-1023～1023の間の値でない
//  [備考]
//    特になし
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
//  [概要]
//    エンコーダのカウント値の取得．
//  [引数]
//    md_id          : エンコーダカウント値取得対象MDのID番号
//    encoder_count_0: エンコーダ0のカウント値を格納する変数のポインタ
//    encoder_count_1: エンコーダ1のカウント値を格納する変数のポインタ
//  [戻り値]
//    int型
//    0 : 正常終了
//    -1: エラー　不適なmd_id
//  [備考]
//    特になし
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
//  [概要]
//    エンコーダのカウント値をクリアする
//  [引数]
//    md_id           : 対象MDのID番号
//    encoder_num     : 対象のエンコーダを選択するパラメータ
//                              0: エンコーダ0
//                              1: エンコーダ1
//  [戻り値]
//    int型
//    0 : 正常終了
//    -1: エラー　不適なmd_id
//    -2: エラー　不適なencoder_num
//  [備考]
//    特になし
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
//  [概要]
//    全てのエンコーダのカウント値をクリアする
//  [引数]
//    なし
//  [戻り値]
//    なし
//  [備考]
//    特になし
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
//  [概要]
//    CAN通信で受信したデータをセット．
//  [引数]
//    id      : ID(11ビット)が格納されている変数
//    dlc     : DLC(4ビット)が格納されている変数
//    data    : データフィールドが格納されている配列
//  [戻り値]
//    int型
//    0～3: 受信データの種類
//    -1  : エラー　不適なid
//    -2  : エラー　不適なdlc
//  [使用グローバル変数]
//    internal_encoder_count (W)
//    present_md_id (R)
//  [備考]
//    特になし
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
//  [概要]
//    CAN通信で送信するデータを取得．
//  [引数]
//    id      : ID(11ビット)を格納する変数のポインタ
//    dlc     : DLC(4ビット)を格納する変数のポインタ
//    data    : データフィールドを格納する配列
//  [戻り値]
//    なし
//  [使用グローバル変数]
//    internal_motor_control_data (R)
//    present_md_id (W)
//  [備考]
//    特になし
//-----------------------------------------------------------------------------
void canmd_controller_get_can_transmit_data(int *id, int *dlc, unsigned char data[])
{
    static enum {
        INIT_ROUTINE,
        CONTROL_ROUTINE,
    } state = INIT_ROUTINE;

    state = CONTROL_ROUTINE;

    // present_md_id の更新
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
