#ifndef _I2C_H
#define _I2C_H


#include <stdint.h>



/*-------------------------------------------------------------------------------------*/


/* Exported constants---------------------------------------------------------------------------------------*/


#define SLAVE_ADDRESS   0XD0            //SLAVE_ADDRESS range is 0x00 ~ 0xFF

#define SCL             _pa5
#define SCL_C           _pac5
#define SCL_PU          _papu5

#define SDA             _pa4
#define SDA_C           _pac4
#define SDA_PU          _papu4

#define FSYS            12000000
#define FSCL            100000

#define t_LOW           1
#define t_HIGH          1

        #define Internal_PU             (1)
//      #define External_PU             (1)


#if     (FSYS==8000000)

        #define t_HD_STA                10
        #define t_SU_STA                10
        #define t_SU_STO                10
        #define t_BUF                   4

        #if     (FSCL==90000)
                #define P_RATIO         0
                #define OFFSET1         0
                #define OFFSET2         0
                #define t_HIGH1         4
                #define t_HIGH2         4
                #define t_LOW1          4
                #define t_LOW2          4
                #define t_LOW3          0

        #elif   (FSCL==50000)
                #define P_RATIO         1
                #define OFFSET1         -1
                #define OFFSET2         -1
                #define t_HIGH1         7
                #define t_HIGH2         9
                #define t_LOW1          9
                #define t_LOW2          9
                #define t_LOW3          8

        #elif   (FSCL==25000)
                #define P_RATIO         3
                #define OFFSET1         -3
                #define OFFSET2         -3
                #define t_HIGH1         ((2+t_HIGH)*P_RATIO+OFFSET1+1)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((2+t_LOW)*P_RATIO+OFFSET2+1)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          27

        #elif   (FSCL==10000)
                #define P_RATIO         8
                #define OFFSET1         2
                #define OFFSET2         2
                #define t_HIGH1         ((2+t_HIGH)*P_RATIO+OFFSET1-19)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((2+t_LOW)*P_RATIO+OFFSET2-19)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          87

        #endif

#elif   (FSYS==12000000)

        #define t_HD_STA                15
        #define t_SU_STA                15
        #define t_SU_STO                15
        #define t_BUF                   14

        #if     (FSCL==100000)
                #define P_RATIO         1
                #define OFFSET1         -6
                #define OFFSET2         -6
                #define t_HIGH1         ((12+t_HIGH)*P_RATIO+OFFSET1)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((12+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          2

        #elif   (FSCL==50000)
                #define P_RATIO         2
                #define OFFSET1         -2
                #define OFFSET2         -2
                #define t_HIGH1         ((3+t_HIGH)*P_RATIO+OFFSET1)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((4+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          18

        #elif   (FSCL==25000)
                #define P_RATIO         5
                #define OFFSET1         -5
                #define OFFSET2         -5
                #define t_HIGH1         ((t_HIGH)*P_RATIO+OFFSET1+7)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((t_LOW)*P_RATIO+OFFSET2+7) 
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          47

        #elif   (FSCL==10000)
                #define P_RATIO         13
                #define OFFSET1         -3
                #define OFFSET2         -3
                #define t_HIGH1         ((t_HIGH)*P_RATIO+OFFSET1-3)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((t_LOW)*P_RATIO+OFFSET2-3)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          137

        #endif

#elif   (FSYS==16000000)

        #define t_HD_STA                20
        #define t_SU_STA                20
        #define t_SU_STO                20
        #define t_BUF                   25

        #if     (FSCL==100000)
                #define P_RATIO         1
                #define OFFSET1         -1
                #define OFFSET2         -1
                #define t_HIGH1         ((7+t_HIGH)*P_RATIO+OFFSET1)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((7+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          7

        #elif   (FSCL==50000)
                #define P_RATIO         3
                #define OFFSET1         -3
                #define OFFSET2         -3
                #define t_HIGH1         ((3+t_HIGH)*P_RATIO+OFFSET1)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((2+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          25

        #elif   (FSCL==25000)
                #define P_RATIO         6
                #define OFFSET1         4
                #define OFFSET2         4
                #define t_HIGH1         ((2+t_HIGH)*P_RATIO+OFFSET1-15)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((2+t_LOW)*P_RATIO+OFFSET2-15)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          64

        #elif   (FSCL==10000)
                #define P_RATIO         17
                #define OFFSET1         3
                #define OFFSET2         3
                #define t_HIGH1         ((2+t_HIGH)*P_RATIO+OFFSET1-47)
                #define t_HIGH2         ((10+t_HIGH)*P_RATIO+OFFSET1)
                #define t_LOW1          ((2+t_LOW)*P_RATIO+OFFSET2-47)
                #define t_LOW2          ((10+t_LOW)*P_RATIO+OFFSET2)
                #define t_LOW3          187

#endif

#elif   ((FSYS!=8000000) && (FSYS!=12000000) && (FSYS!=16000000))
        #if     (DIV_COEFF == 100)
                #define t_HD_STA        20
                #define t_SU_STA        20
                #define t_SU_STO        20
                #define t_BUF           25
                #define P_RATIO         1
                #define OFFSET1         -8
                #define OFFSET2         -9
                #define t_HIGH1         4
                #define t_HIGH2         5
                #define t_LOW1          5
                #define t_LOW2          5
                #define t_LOW3          0

        #elif   (DIV_COEFF == 200)
                #define t_HD_STA        20
                #define t_SU_STA        20
                #define t_SU_STO        20
                #define t_BUF           25
                #define P_RATIO         1
                #define OFFSET1         4
                #define OFFSET2         4
                #define t_HIGH1         11
                #define t_HIGH2         11
                #define t_LOW1          11
                #define t_LOW2          11
                #define t_LOW3          12

        #endif

#endif

#define t_LOW_OS        ((10+t_LOW)*P_RATIO+OFFSET1)
#define t_HIGH_OS       ((10+t_HIGH)*P_RATIO+OFFSET2)

#define SCL_HIGH()      SCL_C=1
#define SCL_LOW()       SCL_C=0,SCL=0

#define SDA_HIGH()      SDA_C=1
#define SDA_LOW()       SDA_C=0,SDA=0

typedef enum 
{
        RX_Mode = 0x00,
        TX_Mode = 0x01
}I2C_Slave_Mode_TypeDef;


/* Exported functions---------------------------------------------------------------------------------------*/
void SW_I2C_Master_Init(void);
void SW_I2C_Send_Start(void);
void SW_I2C_Send_Stop(void);
I2C_ACK_Flag SW_I2C_Send_Data(uint8_t data);
I2C_ACK_Flag SW_I2C_Send_Addr(uint8_t slave_addr,uint8_t slave_mode);
uint8_t SW_I2C_Receive_Data(I2C_ACK_Flag tx_ack);
void master_write_process (uint8_t SLAVE_ADDRESS_1, uint8_t reg_add, uint8_t reg_data );
uint8_t master_read_process(uint8_t SLAVE_ADDRESS_2,uint8_t reg_add);
#endif