
/* CH376芯片 硬件标准异步串口连接的硬件抽象层 V1.0 */
/* 提供I/O接口子程序 */



//#include "Ch376inc.h"
//#include "hal.h"
/* 本例中的硬件连接方式如下(实际应用电路可以参照修改下述定义及子程序) */
/* 单片机的引脚    CH376芯片的引脚
      TXD                  RXD
      RXD                  TXD       */
 #include "file_ah9837.h"
 #include	"HAL.H"	


//#define CH376_INT_WIRE			0x00  //INT0	/* 假定CH376的INT#引脚,如果未连接那么也可以通过查询串口中断状态码实现 */

#define	UART_INIT_BAUDRATE  9600	/* 默认通讯波特率9600bps,建议通过硬件引脚设定直接选择更高的CH376的默认通讯波特率 */
#define	UART_WORK_BAUDRATE	76800 //9600//19200   /* 正式通讯波特率57600bps */

//enum {EUdisk_initNO ,EUdisk_initYES};



void	CH376_PORT_INIT(uint8 k   )  /* 由于使用异步串口读写时序,所以进行初始化 */
{
//  uint8 SFRPAGE_save=SFRPAGE;
//  SFRPAGE=CONFIG_PAGE;
 
 
  mDelaymS( 200 );
  if((k&0x01)!=0x00)
    {
      Uart1Init(UART_INIT_BAUDRATE);
	}
  else
  	{
  	  Uart1Init(UART_WORK_BAUDRATE);
  	}
  UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT);
  IntDisable(INT_UART1);
  mDelaymS( 200 );
//  SFRPAGE=SFRPAGE_save;
}

#ifdef	UART_WORK_BAUDRATE
void	SET_WORK_BAUDRATE( void )  /* 将单片机切换到正式通讯波特率 */
{

  Uart1Init(UART_WORK_BAUDRATE);
   UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT);
  IntDisable(INT_UART1);
  mDelaymS( 200 );
}

#endif

//#define	xEndCH376Cmd( )  /* 结束CH376命令,仅用于SPI接口方式 */

void	xWriteCH376Cmd( UINT8 mCmd )  /* 向CH376写命令 */
{

     UARTCharPut(UART1_BASE , SER_SYNC_CODE1); /* 启动操作的第1个串口同步码 */
	 UARTCharPut(UART1_BASE , SER_SYNC_CODE2); /* 启动操作的第2个串口同步码 */
	 UARTCharPut(UART1_BASE ,  mCmd);/* 串口输出 */



}

void	xWriteCH376Data( UINT8 mData )  /* 向CH376写数据 */
{
 
  UARTCharPut(UART1_BASE ,  mData);/* 串口输出 */

}

UINT8	xReadCH376Data( void )  /* 从CH376读数据 */
{
	UINT32	i;
    uint8 sbuf_temp=0;
for ( i = 0; i < 0x50000; i ++ )
	{  /* 计数防止超时 */
	  if( 0== (HWREG(UART1_BASE + UART_O_FR) & UART_FR_RXFE))
         {
           sbuf_temp=(uint8)(UART1_BASE + UART_O_DR);
		   break;
        }

  	}
	
	return( sbuf_temp);  /* 不应该发生的情况 */
}

/* 查询CH376中断(INT#低电平) */
UINT8	Query376Interrupt( void )
{
#ifdef	CH376_INT_WIRE
	return( CH376_INT_WIRE ? FALSE : TRUE );  /* 如果连接了CH376的中断引脚则直接查询中断引脚 */
#else
  {
   	 if( 0== (HWREG(UART1_BASE + UART_O_FR) & UART_FR_RXFE))
	 	{  /* 如果未连接CH376的中断引脚则查询串口中断状态码 */
		// HWREG(UART1_BASE + UART_O_DR);
		 return( TRUE );
	    }
	 
	 else
	 	{
	  	return( FALSE );
	 	} 
   }	
#endif
}



UINT8	mInitCH376Host(  )  /* 初始化CH376 */
{
	UINT8	res;

	   uint8 k;
    for(k=0x00;k<6;k++)
    	{
	     CH376_PORT_INIT(k);  /* 接口硬件初始化 */
	     xWriteCH376Cmd( CMD11_CHECK_EXIST );  /* 测试单片机与CH376之间的通讯接口 */
         xWriteCH376Data( 0x65 );
         res = xReadCH376Data( );
//	xEndCH376Cmd( );  // 异步串口方式不需要
	     if ( res == 0x9A ) 
	     	{
		 	 break;
		 	}
    	 }
    if(k>=6)
    	{
    	 return( ERR_USB_UNKNOWN );
    	} /* 通讯接口不正常,可能原因有:接口连接异常,其它设备影响(片选不唯一),串口波特率,一直在复位,晶振不工作 */
#ifdef	UART_WORK_BAUDRATE
	xWriteCH376Cmd( CMD21_SET_BAUDRATE );  /* 设置串口通讯波特率 */
#if		UART_WORK_BAUDRATE >= 6000000/256
	xWriteCH376Data( 0x03 );
	xWriteCH376Data( 256 - 6000000/UART_WORK_BAUDRATE );
#else
	xWriteCH376Data( 0x02 );
	xWriteCH376Data( 256 - 750000/UART_WORK_BAUDRATE );
#endif
	SET_WORK_BAUDRATE( );  /* 将单片机切换到正式通讯波特率 */
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // 异步串口方式不需要
	if ( res != CMD_RET_SUCCESS ) return( ERR_USB_UNKNOWN );  /* 通讯波特率切换失败,建议通过硬件复位CH376后重试 */
#endif
	xWriteCH376Cmd( CMD11_SET_USB_MODE );  /* 设备USB工作模式 */
	xWriteCH376Data( 0x06 );
//	mDelayuS( 20 );  // 异步串口方式不需要
	res = xReadCH376Data( );
//	xEndCH376Cmd( );  // 异步串口方式不需要
	if ( res == CMD_RET_SUCCESS ) return( USB_INT_SUCCESS );
	else return( ERR_USB_UNKNOWN );  /* 设置模式错误 */
}
