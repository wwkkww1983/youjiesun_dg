/* 2008.10.18
****************************************
**  Copyright  (C)  W.ch  1999-2009   **
**  Web:  http://www.winchiphead.com  **
****************************************
**  USB Host File Interface for CH376 **
**  TC2.0@PC, KC7.0@MCS51             **
****************************************
*/
/* CH376 �����ļ�ϵͳ�ӿ� */

/*
�����ݴ������ı���ʽ��100�飻
�ṹ: ��:  ����        ���� 
      00: I=200.0A     R=2000.0uo  
      01: I=100.0A     R=1000.0uo  
      .......
      99: I=99.0A      R=1000.0uo  
*/

/* C51   CH376HFT.C */
/* LX51  CH376HFT.OBJ */
/* OHX51 CH376HFT */

//#include <reg52.h>
//#include <stdio.h>
//#include <string.h>
#define		EN_DIR_CREATE	1	/* ֧���½��༶��Ŀ¼ */ 
#define		EN_LONG_NAME	1
#define	    EN_SECTOR_ACCESS 1
#define	    EN_DISK_QUERY 1
 #include "file_ah9837.h" 
//#include  " HAL.H"   //  Ӳ���첽�������ӷ�ʽ */
#include  "FILE_SYS_c51.h" 



 /*
#define group_offset 0x00   
#define I_offset     0x04
#define R_offset     0x0e
#define group_nub    27
#define Udiskstartaddress 40


 void  udisk_content()
 {
   uint8 xdata udisk[2044];  
   uint8 k;
   uint16 address;
   xs_need xs_needon;
    {
	 
	  for(address=0x00;address<2048;address++)
	  	{
	  	 udisk[address]=' ';
	  	}
   	}
   strcpy( udisk,"   �����ջ�HL-IIIA��·���������");
   udisk[Udiskstartaddress-2]=0x0d;
   udisk[Udiskstartaddress-1]=0x0a ;
   
   for(k=0x00;k<sto_group;k++)
   	{
      read_data(k,&xs_needon);
      address=k*group_nub+Udiskstartaddress;
	  
	  udisk[ address+group_offset]=0x30+k/10;
	  udisk[address+group_offset+1]=0x30+k%10;
	  udisk[address+group_offset+2]=':';

	  udisk[address+I_offset]='I';
	  udisk[address+I_offset+1]='=';
        {
		   uint8 j;	
		   sprintf (&udisk[address+I_offset+2], "%3.1f\n", xs_needon.f.i);	
            
		   for(j=0;j<5;j++)
		     {
		      if(udisk[address+I_offset+2+j]==0x0a)
		 	    {
		 	     udisk[address+I_offset+2+j]=' ';
			     for(j++;j<5;j++)
		 	 	  {
		 	 	   udisk[address+I_offset+2+j]=' ';
		 	 	  }
                 break; 
		 	   }
		   	 }
	  	}	
	  udisk[address+I_offset+7]='A';
   

      udisk[address+R_offset]='R';
	  udisk[address+R_offset+1]='=';
        {
		   uint8 j;	
		   sprintf (&udisk[address+R_offset+2], "%4.1f\n", xs_needon.f.r);	
		   for(j=0;j<6;j++)
		     {
		      if(udisk[address+R_offset+2+j]==0x0a)
		 	    {
		 	     udisk[address+R_offset+2+j]=' ';
			     for(j++;j<5;j++)
		 	 	  {
		 	 	   udisk[address+R_offset+2+j]=' ';
		 	 	  }
                 break; 
		 	   }
		   	 }
	  	}	
	  udisk[address+R_offset+8]='u';
	  udisk[address+R_offset+9]=0xa6 ;
	  udisk[address+R_offset+0xa]=0xb8 ;//'��';
	  
	  udisk[address+ group_nub-2]=0x0d ;//'��';
	  udisk[address+ group_nub-1]=0x0a ;

	  
	
   	}
   
 
 
 }
 
*/

/*
 void exram_init()
{
// uint8 k;
 uint16 i;
 uint8 xdata *p;
// uint8 SFRPAGE_save=SFRPAGE;
// EMI_in_Init();
 ERAMcs_set;
 p=(uint8 xdata *)0x00;
 for(i=0x00;i<0x200;i++)
 	{
 	 *p++=0x38;
 	}
 //EMI_out_Init();
 // SFRPAGE=CONFIG_PAGE;
  p=(uint8 xdata *)0x00;
  ERAMcs_UA;
     for(i=0x00;i<0x800;i++)
 	 {
 	   *p++=0x30+1;
 	 }
	 ERAMcs_UB;
	  p=(uint8 xdata *)0x00;
     for(i=0x00;i<0x800;i++)
 	 {
 	   *p++=0x30+2;
 	 }
	  ERAMcs_UC;
	   p=(uint8 xdata *)0x00;
     for(i=0x00;i<0x800;i++)
 	 {
 	   *p++=0x30+3;
 	 }
	  
 
// SFRPAGE=SFRPAGE_save;
}
*/                  
                                              
const uint8  Udiskname[4]={'O','i','l','_'} ;


void file_name(uint8 *buf )
  {
    uint8 k;
	union
		{
		 uint8 byte[2];	
         uint16 group;
		}name;
	
	
  
	{
		uint8 i;
		for (i=0x00;i<4;i++)
			{
			 buf[i]=Udiskname[i];
			}
 	}
   name.group=(unsigned int)udiskname_address ;
   readbyte_much( name.group,2, name.byte);


     for(k=4-1;k<4;k--)
   	      {
          	 buf[k+4]=(name.group%10)+0x30;
	         name.group/=10;
        	}
     	
   
   	buf[8]='.';
	buf[9]='T';
	buf[10]='X';
	buf[11]='T';
	buf[12]='\0';

  }


/* Ϊָ���ļ����ô������ں�ʱ�� */
/* �������:   ԭʼ�ļ�����iFileName��, �µĴ������ں�ʱ��: iCreateDate, iCreateTime */
/* ����״̬��: USB_INT_SUCCESS = ���óɹ�,
               ����״̬��ο�CH376INC.H */
		
 unsigned char bcd_hex1(unsigned char i)
     {
       i=(i>>4)*10+(i&0x0f);
       return (i);
     }
			 

uint16 CreateDate( time_type *time)
{
  uint8 year ;
  uint8 month;
  uint8 day;

  year=(uint8)(2000-1980+bcd_hex1(time->time.year));
  month=bcd_hex1(time->time.month);
  day=bcd_hex1(time->time.day);
  return( (year<<9) + (month<<5) + day );
}

uint16 CreateTime( time_type *time)
{
  uint8 hour ;
  uint8 minute;
  uint8 second;

  hour= bcd_hex1(time->time.hour);
  minute=bcd_hex1(time->time.minute);
  second=bcd_hex1(time->time.second);
  return ( (hour<<11) + (minute<<5) + (second>>1));
}




UINT8	SetFileCreateTime( UINT16 iCreateDate, UINT16 iCreateTime)//,uint8 *buf )
{
	UINT8	s; 
	uint8 bufz[2];
	//P_FAT_DIR_INFO	pDir;
	
	//s = CH376FileOpen( iFileName );  /* ���ļ� */
	//if ( s == USB_INT_SUCCESS ) {
		/* �ļ���д������... */
		s = CH376DirInfoRead( );  /* ��ȡ��ǰ�ļ���Ŀ¼��ϢFAT_DIR_INFO,��������ݵ����ڴ��� */
		if ( s == USB_INT_SUCCESS )
		 {

		 //  	CH376ReadBlock( buf );  /* ���ڴ滺������ȡFAT_DIR_INFO���ݿ�,���س�������sizeof(FAT_DIR_INFO) */
		//	pDir = (P_FAT_DIR_INFO)buf;  /* ��ǰ�ļ�Ŀ¼��Ϣ */
			
			bufz[0] = (UINT8)iCreateTime;  /* �ļ�������ʱ��,��8λ��ǰ */
			bufz[1] = (UINT8)(iCreateTime>>8);  /* �ļ�������ʱ��,��8λ�ں� */
			CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_CrtTime ), 2 );  /* ���ڲ�������ƫ�Ƶ�ַDIR_CrtTimeд��2���ֽ� */
            CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_WrtTime ), 2 ); 
			
			bufz[0] = (UINT8)iCreateDate;  /* �ļ�����������,��8λ��ǰ */
			bufz[1] = (UINT8)(iCreateDate>>8);  /* �ļ�����������,��8λ�ں� */
			CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_CrtDate ), 2 );  /* ���ڲ�������ƫ�Ƶ�ַDIR_CrtDateд��2���ֽ� */
			CH376WriteOfsBlock( bufz, STRUCT_OFFSET( FAT_DIR_INFO, DIR_WrtDate ), 2 ); 
			s = CH376DirInfoSave( );  /* �����ļ���Ŀ¼��Ϣ */
			if ( s == USB_INT_SUCCESS ) {  /* �ɹ��޸Ĳ����� */
				/* �ļ���д������... */
			}
	//	CH376FileClose( FALSE );  /* �ر��ļ� */
	}
	return( s );
}

/*
//==U�̱�׼ʱ��


DWORD get_fattime (void)
{
	unsigned char Dec[6];
    RTC_T time;

	ReadRtc(&time);
	Dec[0] =  time.Year    - (time.Year>>4) * 6;
	Dec[1] =  time.Month   - (time.Month>>4) * 6;
	Dec[2] =  time.Date    - (time.Date>>4) * 6;
	Dec[3] =  time.Hours   - (time.Hours>>4) * 6;
	Dec[4] =  time.Minutes - (time.Minutes>>4) * 6;
	Dec[5] =  time.Seconds - (time.Seconds>>4) * 6;
	return    ((Dec[0]+20)  << 25)           // Year = 2007
            | ( Dec[1]      << 21)           // Month = June
            | ( Dec[2]      << 16)           // Day = 5
            | ( Dec[3]      << 11)           // Hour = 11
            | ( Dec[4]      << 5)            // Min = 38
            | ( Dec[5]      >> 1)            // Sec = 0
            ;
#if 0
    return    ((2007UL-1980) << 25) // Year = 2007
            | (6UL << 21)           // Month = June
            | (5UL << 16)           // Day = 5
            | (11U << 11)           // Hour = 11
            | (38U << 5)            // Min = 38
            | (0U >> 1)             // Sec = 0
            ;
#endif
} 

*/






uint8  udisk_ch376()
   {
   // uint8  SFRPAGE_save=SFRPAGE;
	UINT8	s;
    uint8			buf[40];
//	uint8 name ;
	mDelaymS( 100 );  /* ��ʱ100���� */
	//if(Udisk_uartflag==EUdisk_initNO)
    {
      s = mInitCH376Host();  /* ��ʼ��CH376 */
   
	if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	{
    	 return(s);
    	}
	} 
     rx_flag=1;
	// China_swing(easydisk_warnlin,easydisk_warncolumn,&text_zzcz,easydisk_warnscreen|0x80);	//	U��ʧ��		 
	/* ������·��ʼ�� */
	//printf( "Wait Udisk/SD\n" );�ȴ�U��		 
//	while ( 1 )
	  {
		
	for(s=0;s<20;s++)
	     {
	       if( CH376DiskConnect( ) != USB_INT_SUCCESS ) 
		   { 
			  mDelaymS( 100 );   /* ���U���Ƿ�����,�ȴ�U�̲���,����SD��,�����ɵ�Ƭ��ֱ�Ӳ�ѯSD�����Ĳ��״̬���� */
            		  
		   }
		   else
		   	{
		   	 break;
		   	}
		}
		
		mDelaymS( 200 );        /* ��ʱ,��ѡ����,�е�USB�洢����Ҫ��ʮ�������ʱ */

          if(s>=20) 
		    {
		     return(ERR_USB_UNKNOWN);
          	}
         //printf( "Ready ?\n" ); ����ת��   
		for ( s = 0; s < 10; s ++ )
		   {                       /*   ���ڼ�⵽USB�豸��,���ȴ�10*50mS  ��ȴ�ʱ��,10*50mS */
			mDelaymS( 50 );
			if ( CH376DiskMount( ) == USB_INT_SUCCESS ) 
				 break;  /* ��ʼ�����̲����Դ����Ƿ���� */
		   }
        if(s>=10)
        	{
        	  return(s);
        	}
         
		
#if 0		
		s = CH376ReadBlock( buf );  /* �����Ҫ,���Զ�ȡ���ݿ�CH376_CMD_DATA.DiskMountInq,���س��� */
		if ( s == sizeof( INQUIRY_DATA ) )
		{  /* U�̵ĳ��̺Ͳ�Ʒ��Ϣ */
			buf[ s ] = 0;
			printf( "UdiskInfo: %s\n", ((P_INQUIRY_DATA)buf) -> VendorIdStr );
		}
#endif
		s = CH376DirCreate( "/�����ջ�" );  /* �½����ߴ�Ŀ¼,��Ŀ¼���ڸ�Ŀ¼�� */
		//if ( s == ERR_FOUND_NAME ) printf( "Found a file with same name\n" );
		//mStopIfError( s );
	
		CH376FileClose( FALSE );  /* �ر�Ŀ¼ */
	   if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	{
    	 return(s);
    	}

/* �����½�������Ŀ¼ */
		
		strcpy( buf, "/�����ջ�/KD9001A" );  /* Ŀ¼��,��Ŀ¼����YEAR2008��Ŀ¼��,YEAR2008Ŀ¼�������ȴ���,CH376DirCreatePath���ļ���������������RAM�� */
      	s = CH376DirCreatePath( buf );  /* �½����ߴ�Ŀ¼,��Ŀ¼���ڶ༶Ŀ¼��,����·��������RAM�� */
	    if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	{
    	 return(s);
    	}
//		CH376FileClose( FALSE );  /* ��ʱ���ر�Ŀ¼,��Ϊ����Ҫ������½����ߴ򿪵�Ŀ¼���½��ļ� */

/* Ŀ¼�½����ߴ򿪳ɹ�,�����������Ŀ¼���½�һ����ʾ�ļ�,
   ���ַ���:һ��CH376FileCreatePath�½��༶Ŀ¼�µ��ļ�,����CH376FileCreate�ڵ�ǰĿ¼���½��ļ�(���ǰ������ϼ�Ŀ¼����û�йر�) */
	

//		strcpy( buf, "/YEAR2008/MONTH05/DEMO2008.TXT" );  /* �ļ���,��Ŀ¼����YEAR2008/MONTH05�༶Ŀ¼��,Ŀ¼�������ȴ���,CH376FileCreatePath���ļ���������������RAM�� */
//		s = CH376FileCreatePath( buf );  /* �½��༶Ŀ¼�µ��ļ�,����ļ��Ѿ���������ɾ�������½�,����·��������RAM�� */


  
  
     {
        file_name(buf);
    //	s = CH376FileOpen( buf );  /* ���ļ�,���ļ��ڸ�Ŀ¼�� */
	//	if ( s == USB_INT_SUCCESS )
	//		{  /* �ļ����ڲ����Ѿ�����,�ƶ��ļ�ָ�뵽β���Ա��������� */
	//	 	 s = CH376ByteLocate( 0xFFFFFFFF );  /* �Ƶ��ļ���β�� */  /* �ر�Ŀ¼ */
	//	    }
   //		else if ( s == ERR_MISS_FILE ) 
			{  /* û���ҵ��ļ�,�����½��ļ� */
		   	  s = CH376FileCreate(buf);// NULL );  /* �½��ļ�����,����ļ��Ѿ���������ɾ�������½�,�������ṩ�ļ���,�ղ��Ѿ��ṩ��CH376FileOpen */
			 
		    }
	
        
     }
}


	//	s = CH376FileCreate( buf );//("DEMO2009.TXT" );  /* �ڵ�ǰĿ¼���½��ļ�,����ļ��Ѿ���������ɾ�������½� */
		if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	 {
    	   return(s);
    	 }
                //����ʱ��
     
     if(rx_flag==1)//  �ֽ�ת��
       {
          uint8 i; 
          uint8  byte[pageLong ];
		  for(i=0;i<viewpage_nub;i++)
		  	{
		      uint16  address=VIEWsto_addr+i*pageLong;
		      readbyte_much( address,pageLong ,byte);
	       	  s = CH376ByteWrite(byte,pageLong , NULL ); 
	 	      if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	       {
             	 return(s);
    	       }
		  	}  
    	
       }

		
      
     
		else   // ����ת��
		    {
		     //  SFRPAGE=CONFIG_PAGE;
	           s = CH376SecLocate( 0xFFFFFFFF );
			   if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	        {
    	         return(s);
    	        }
               s = CH376SecWrite( (uint8  *)0x00, (UINT8)(0x4200/DEF_SECTOR_SIZE), NULL );  
			  if(s==ERR_USB_UNKNOWN) 		//��ʾch376 ok?
    	      {
    	       return(s);
    	       }
        	}
       	
		//printf( "Close\n" );ת�����
		{
		 time_type   time;
         read_time(&time);
	     SetFileCreateTime( CreateDate(&time), CreateTime(&time));//,buf );
		}
		s = CH376FileClose( TRUE );  /* �ر��ļ�,�Զ������ļ����� */
		

		mDelaymS( 200 );
        return(succ_USB_KNOWN) ;
    
	}
// SFRPAGE=SFRPAGE_save;			 




