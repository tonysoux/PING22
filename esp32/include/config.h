#ifndef CONFIG_H
#define CONFIG_H

// linear actuators settings
#define P1_STEP_PIN -1
#define P1_DIR_PIN -1
#define P1_RX_PIN -1

#define P2_STEP_PIN -1
#define P2_DIR_PIN -1
#define P2_RX_PIN -1

#define P3_STEP_PIN -1
#define P3_DIR_PIN -1
#define P3_RX_PIN -1

#define P4_STEP_PIN -1
#define P4_DIR_PIN -1
#define P4_RX_PIN -1

// solenoid settings
#define P1_SOLENOID_PIN -1
#define P2_SOLENOID_PIN -1
#define P3_SOLENOID_PIN -1
#define P4_SOLENOID_PIN -1

// beam switch settings
#define BEAM_SWITCH_DELAY_us 1000
#define BEAM_SWITCH_TIMEOUT_us 60000
#define P123_BEAM_T_PIN GPIO_NUM_26
#define P1_BEAM_R_PIN GPIO_NUM_25

#define P2_BEAM_R_PIN -1

#define P3_BEAM_R_PIN -1

#define P4_BEAM_R_PIN -1

// communication settings
#define RASP_TX_PIN -1
#define RASP_RX_PIN -1
#define RASP_BAUD_RATE -1

#endif