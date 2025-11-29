#include "I2C.h"
#include <stdint.h>


/* Includes ---------------------------------------------------------------------------------------------------------*/

void SW_I2C_Master_Init(void)
{
        SCL_C = 1;
        SDA_C = 1;

        #ifdef  Internal_PU
                SCL_PU = 1;
                SDA_PU = 1;

        #elif   External_PU
                SCL_PU = 0;
                SDA_PU = 0;

        #endif
}


/************************************************************************************************************
     S/W I2C Master Start function.
*****************************************************************************************************/
void SW_I2C_Send_Start(void)
{
        SCL_HIGH();
        GCC_DELAY(t_SU_STO);
        SDA_HIGH();
        GCC_DELAY(t_BUF);

        SDA_LOW();
        GCC_DELAY(t_HD_STA);
        SCL_LOW();
}


/************************************************************************************************************
      S/W I2C Master Stop function.
 ***********************************************************************************************************/
void SW_I2C_Send_Stop(void)
{
        SCL_LOW();

        SDA_C = 1;
        if(!SDA) GCC_CLRWDT();

        SDA_LOW();
        SCL_HIGH();
        GCC_DELAY(t_SU_STO);
        SDA_HIGH();
        GCC_DELAY(t_BUF);
}


/************************************************************************************************************
  * @brief      S/W I2C Master transmit 1-byte data and receive acknowledge flag function.
  * @param      data: the data that will be transmitted.
  * @retval     The acknowledge flag receive from I2C bus.
  *             The acknowledge flag can have one of the values of @ref I2C_ACK_Flag
 ***********************************************************************************************************/
I2C_ACK_Flag SW_I2C_Send_Data(u8 data)
{
        u8 temp = 0b10000000;

        do
        {
                SCL_LOW();

                if (data & temp)
                        SDA_HIGH();
                else
                        SDA_LOW();

                #if (P_RATIO == 0)
                        GCC_DELAY(t_LOW);
                #else
                        GCC_DELAY(t_LOW_OS);
                #endif

                SCL_HIGH();
                GCC_DELAY(t_HIGH);

                #if (P_RATIO == 0)
                        GCC_DELAY(t_HIGH);
                #else
                        GCC_DELAY(t_HIGH_OS);
                #endif

                temp >>= 1; 
        }while(temp != 0);

        GCC_NOP();

        I2C_ACK_Flag ack_status = NACK;

        SCL_LOW();
        GCC_DELAY(t_LOW1);
        SDA_C = 1;
        GCC_DELAY(t_LOW2);

        SCL_HIGH();
        GCC_DELAY(t_HIGH1);

        if(!SDA)
        {
                ack_status = ACK;
        }

        GCC_DELAY(t_HIGH2);

        SCL_LOW();

        return ack_status;
}


/************************************************************************************************************
  * @brief      S/W I2C Master transmit Slave address and receive acknowledge flag function.
  * @param      slave_addr: the Slave address that will be transmitted. 
  *             The slave_addr range is 0x00 ~ 0xFF, but only Bits 7~ 1 is used to define the device slave address.
  * @param      slave_mode: I2C Slave device is transmitter or receiver selection 
  *             slave_mode can have one of the values of @ref I2C_Slave_Mode_TypeDef
  * @retval     The acknowledge flag receive from I2C bus.
  *             The acknowledge flag can have one of the values of @ref I2C_ACK_Flag
 ***********************************************************************************************************/
I2C_ACK_Flag SW_I2C_Send_Addr(u8 slave_addr,u8 slave_mode)
{
        return(SW_I2C_Send_Data((slave_addr & 0xfe)|slave_mode));
}


/************************************************************************************************************
  * @brief      S/W I2C Master receive 1-byte data and response acknowledge function.
  * @param      tx_ack: Response acknowledge flag or non-acknowledge flag
  *             tx_ack can have one of the values of @ref I2C_ACK_Flag
  * @retval     The data receive from I2C bus.
 ***********************************************************************************************************/
u8 SW_I2C_Receive_Data(I2C_ACK_Flag tx_ack)
{
        u8 I2C_data = 0;
        I2C_ACK_Flag ack_flag = tx_ack;
        u8 temp = 0b10000000;

        SCL_LOW();
        SDA_C = 1;

        do
        {
                GCC_DELAY(t_LOW);
                GCC_NOP();

                #if (P_RATIO == 0)
                        GCC_DELAY(t_LOW);
                #else
                        GCC_DELAY(t_LOW_OS);
                #endif

                SCL_HIGH();
                GCC_NOP();
                GCC_NOP();
                GCC_NOP();

                if (1 == SDA)
                        I2C_data |= temp; 

                #if (P_RATIO == 0)
                        GCC_DELAY(t_HIGH);
                #else
                        GCC_DELAY(t_HIGH_OS);
                #endif

                temp >>= 1;

                SCL_LOW();
        }while(temp != 0);

        if(!ack_flag)
        {
                SDA_LOW();

                #if (t_LOW3 > 2)
                        GCC_DELAY((t_LOW3-2));
                #endif
        }
        else
        {
                SDA_HIGH();

                #if (t_LOW3!=0)
                        GCC_DELAY(t_LOW3);
                #endif
        }

        SCL_HIGH();
        GCC_DELAY(t_HIGH1);
        GCC_NOP();
        GCC_NOP();
        GCC_DELAY(t_HIGH2);

        SCL_LOW();

        return I2C_data;
}

void master_write_process (uint8_t SLAVE_ADDRESS_1, uint8_t reg_add, uint8_t reg_data ){
	int Ack_flag;
	SW_I2C_Send_Start();
    Ack_flag = SW_I2C_Send_Addr(SLAVE_ADDRESS_1,0x00);
    if (!Ack_flag)
    {
	Ack_flag=SW_I2C_Send_Data(reg_add);
	 if (!Ack_flag)
	 {
 	 GCC_DELAY(10);
	 Ack_flag=SW_I2C_Send_Data(reg_data);	
	 }	
    }
SW_I2C_Send_Stop();
	
}
uint8_t master_read_process(uint8_t SLAVE_ADDRESS_2,uint8_t reg_add){
	int Ack_flag;
	uint8_t data_i2c;
	SW_I2C_Send_Start();
    Ack_flag = SW_I2C_Send_Addr(SLAVE_ADDRESS_2,0x00);
    if (!Ack_flag)
    {
	 Ack_flag=SW_I2C_Send_Data(reg_add);
	  if (!Ack_flag)
	  {
		SW_I2C_Send_Start();	
		Ack_flag=SW_I2C_Send_Addr(SLAVE_ADDRESS_2,1);
		if (!Ack_flag)
		{
			//GCC_DELAY(10);
			data_i2c=SW_I2C_Receive_Data(NACK);	
		}	
 	  }	
    }
 SW_I2C_Send_Stop();
 return data_i2c;
}
