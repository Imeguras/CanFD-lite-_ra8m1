

#include "canfd.h"
volatile int count;
volatile int a_fd=0;

// CANFD Channel 0 Acceptance Filter List (AFL) rule array
extern const canfd_afl_entry_t p_canfd0_afl [CANFD_CFG_AFL_CH0_RULE_NUM] = {
     {
            // TODO: Edit the settings below to filter for specific messages.

            .id =
            {
                // Specify the ID, ID type and frame type to accept.
                .id         = 0x00000000,
                .frame_type = CAN_FRAME_TYPE_DATA,
                .id_mode    = CAN_ID_MODE_EXTENDED
            },

            .mask =
            {
                // These values mask which ID/mode bits to compare when filtering messages.
                .mask_id         = 0x1FFFFFFF,
                .mask_frame_type = 1,
                .mask_id_mode    = 1
            },

            .destination =
            {
                // If DLC checking is enabled any messages shorter than the below setting will be rejected.
                .minimum_dlc = CANFD_MINIMUM_DLC_0,

                // Optionally specify a Receive Message Buffer (RX MB) to store accepted frames. RX MBs do not have an
                 // interrupt or overwrite protection and must be checked with R_CANFD_InfoGet and R_CANFD_Read.
                .rx_buffer   = CANFD_RX_MB_NONE,

                // Specify which FIFO(s) to send filtered messages to. Multiple FIFOs can be OR'd together.
                .fifo_select_flags = CANFD_RX_FIFO_1
            }
        },
    };



// canfd entry function

void canfd_entry(void){
    UINT status = R_CANFD_Open(&g_canfd0_ctrl, &g_canfd0_cfg);
    (void) status;
    // TODO: add your own cfode here
    while (1){

    }
    UINT status3 = R_CANFD_Close(&g_canfd0_ctrl);
    (void) status3;
}
// Callback function


void canfd0_callback(can_callback_args_t *p_args){



    if(p_args->frame.data_length_code>8){
        a_fd++;
        if(a_fd >=64){
            a_fd=0;
        }
        count = p_args->frame.data[a_fd];
        count++;
        memset(p_args->frame.data,count, 16);
        R_BSP_SoftwareDelay(500, BSP_DELAY_UNITS_MILLISECONDS);

        UINT status_ = R_CANFD_Write(&g_canfd0_ctrl, 0, &p_args->frame);

    }
}

