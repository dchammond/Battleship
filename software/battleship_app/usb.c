/*---------------------------------------------------------------------------
  --      usb.c                                                    	   --
  --      Christine Chen                                                   --
  --      Ref. DE2-115 Demonstrations by Terasic Technologies Inc.         --
  --      Fall 2014                                                        --
  --                                                                       --
  --      For use with ECE 298 Experiment 7                                --
  --      UIUC ECE Department                                              --
  ---------------------------------------------------------------------------*/

#include "usb.h"

#include "system.h"
#include "alt_types.h"
#include <unistd.h>  // usleep
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#include "io_handler.h"
#include "cy7c67200.h"
#include "lcp_cmd.h"
#include "lcp_data.h"

#include "sys/alt_irq.h"

static alt_u8 data_size;

//-------------USB operation sub function-----------
/*****************************************************************************/
/**
 *
 * This function writes data to the internal registers of the Cypress
 * CY7C67200 USB controller.
 *
 * @param    Address is the address of the register.
 * @param    Data is the data to be written to the register.
 *
 * @return   None
 *
 * @note     None
 *
 ******************************************************************************/
void UsbWrite(alt_u16 Address, alt_u16 Data)
{
	IO_write(HPI_ADDR, Address);
	IO_write(HPI_DATA, Data);
}

/*****************************************************************************/
/**
 *
 * This function reads data from the internal registers of the Cypress
 * CY7C67200 USB controller.
 *
 * @param    Address is the address of the register.
 *
 * @return   The data read from the specified address
 *
 * @note     None
 *
 ******************************************************************************/
alt_u16 UsbRead(alt_u16 Address)
{
	IO_write(HPI_ADDR, Address);
	return IO_read(HPI_DATA);
}


/*****************************************************************************/
/**
 *
 * This function does a software reset of the Cypress CY7C67200 USB controller.
 *
 * @param    UsbBaseAddress is the starting location of the USB internal memory
 *           to which this bin file data is written.
 *
 * @return   None
 *
 * @note     None
 *
 ******************************************************************************/
void UsbSoftReset()
{
	//XIo_Out16(USB_MAILBOX, COMM_RESET);
	IO_write(HPI_MAILBOX,COMM_RESET); //COMM_JUMP2CODE
	usleep(100000);
	printf("[USB INIT]:reset finished!\n");

	usleep(500000);
	printf("[USB INIT]:Clear up the interrupt\r\n");
	IO_read(HPI_MAILBOX);
	IO_read(HPI_STATUS);

	// Had to add the write due to a bug in BIOS where they overwrite
	// the mailbox after initialization with garbage.  The read clears
	// any pending interrupts.
	UsbRead (HPI_SIE1_MSG_ADR);
	UsbWrite (HPI_SIE1_MSG_ADR, 0);
	UsbRead (HPI_SIE2_MSG_ADR);
	UsbWrite (HPI_SIE2_MSG_ADR, 0);


	UsbWrite (HOST1_STAT_REG, 0xFFFF);
	UsbWrite (HOST2_STAT_REG, 0xFFFF);
}


void UsbSetAddress()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	// TD #1: 6 writes
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	// TASK: Complete with 4 more IOWR functions
	IO_write(HPI_DATA,0x00D0);
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);
	// TD #2: 4 writes
	// TASK: Complete with 4 IOWR functions
	IO_write(HPI_DATA,0x0500);
	IO_write(HPI_DATA,0x0002);
	IO_write(HPI_DATA,0x0000);
	IO_write(HPI_DATA,0x0000);
	// TD #3: 6 writes
	// TASK: Complete with 6 IOWR functions
	IO_write(HPI_DATA,0x0000); //
	IO_write(HPI_DATA,0x0000);//
	IO_write(HPI_DATA,0x0090);//
	IO_write(HPI_DATA,0x0041);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0000);

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
}


void UsbGetDeviceDesc1()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //device address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0680);//c
	IO_write(HPI_DATA,0x0100); //device 0x01
	IO_write(HPI_DATA,0x0000);
	IO_write(HPI_DATA,0x0008);

	//data phase IN
	IO_write(HPI_DATA,0x052C); //
	IO_write(HPI_DATA,0x0008);//
	IO_write(HPI_DATA,0x0290);//
	IO_write(HPI_DATA,0x0041);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0520);

	//    //status phase
	IO_write(HPI_DATA,0x0000); //don't care
	IO_write(HPI_DATA,0x0000);//port number
	IO_write(HPI_DATA,0x0210);//device address
	IO_write(HPI_DATA,0x0041);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0000);

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
}

void UsbGetDeviceDesc2()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //device address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0680);//c
	IO_write(HPI_DATA,0x0100);//e //device 0x01
	IO_write(HPI_DATA,0x0000);//0
	IO_write(HPI_DATA,0x0012);//2

	//data phase IN-1
	IO_write(HPI_DATA,0x0544); //514
	IO_write(HPI_DATA,0x0008);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0520);//e

	//data phase IN-2
	IO_write(HPI_DATA,0x054c); //520
	IO_write(HPI_DATA,0x0008);//2
	IO_write(HPI_DATA,0x0290);//4
	IO_write(HPI_DATA,0x0001);//6
	IO_write(HPI_DATA,0x0013);//8
	IO_write(HPI_DATA,0x052c);//a

	//data phase IN-3
	IO_write(HPI_DATA,0x0554); //c
	IO_write(HPI_DATA,0x0002);//e
	IO_write(HPI_DATA,0x0290);//530
	IO_write(HPI_DATA,0x0041);//2
	IO_write(HPI_DATA,0x0013);//4
	IO_write(HPI_DATA,0x0538);//6

	//status phase
	IO_write(HPI_DATA,0x0000); //538
	IO_write(HPI_DATA,0x0000);//a
	IO_write(HPI_DATA,0x0210);//c
	IO_write(HPI_DATA,0x0041);//e
	IO_write(HPI_DATA,0x0013);//540
	IO_write(HPI_DATA,0x0000);//2

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
}


void UsbGetConfigDesc1()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //device address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0680);//c
	IO_write(HPI_DATA,0x0200);//e //config 0x02
	IO_write(HPI_DATA,0x0000);//0
	IO_write(HPI_DATA,0x0009);//2

	//data phase IN-1
	IO_write(HPI_DATA,0x0544); //514
	IO_write(HPI_DATA,0x0008);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0520);//e

	//data phase IN-2
	IO_write(HPI_DATA,0x054c); //520
	IO_write(HPI_DATA,0x0001);//2
	IO_write(HPI_DATA,0x0290);//4
	IO_write(HPI_DATA,0x0001);//6 //data0
	IO_write(HPI_DATA,0x0013);//8
	IO_write(HPI_DATA,0x052c);//a

	//status phase
	IO_write(HPI_DATA,0x0000); //52c
	IO_write(HPI_DATA,0x0000);//e
	IO_write(HPI_DATA,0x0210);//530
	IO_write(HPI_DATA,0x0041);//2
	IO_write(HPI_DATA,0x0013);//4
	IO_write(HPI_DATA,0x0000);//6

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
}


void UsbGetConfigDesc2()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //device address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0680);//c
	IO_write(HPI_DATA,0x0200);//e //config 0x02
	IO_write(HPI_DATA,0x0000);//0
	IO_write(HPI_DATA,0x00FF);//2

	//data phase IN-1
	IO_write(HPI_DATA,0x055c); //514
	IO_write(HPI_DATA,0x0008);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0520);//e

	//data phase IN-2
	IO_write(HPI_DATA,0x0564); //520
	IO_write(HPI_DATA,0x0008);//2
	IO_write(HPI_DATA,0x0290);//4
	IO_write(HPI_DATA,0x0001);//6 //data0
	IO_write(HPI_DATA,0x0013);//8
	IO_write(HPI_DATA,0x052c);//a

	//data phase IN-3
	IO_write(HPI_DATA,0x056c); //52c
	IO_write(HPI_DATA,0x0008);//e
	IO_write(HPI_DATA,0x0290);//530
	IO_write(HPI_DATA,0x0041);//2
	IO_write(HPI_DATA,0x0013);//4
	IO_write(HPI_DATA,0x0538);//6

	//data phase IN-4
	IO_write(HPI_DATA,0x0574); //538
	IO_write(HPI_DATA,0x0008);//a
	IO_write(HPI_DATA,0x0290);//c
	IO_write(HPI_DATA,0x0001);//e //data0
	IO_write(HPI_DATA,0x0013);//540
	IO_write(HPI_DATA,0x0544);//2

	//data phase IN-5
	IO_write(HPI_DATA,0x057c); //544
	IO_write(HPI_DATA,0x0002);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a //data1
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0550);//e

	//status phase
	IO_write(HPI_DATA,0x0000); //550
	IO_write(HPI_DATA,0x0000);//2
	IO_write(HPI_DATA,0x0210);//4
	IO_write(HPI_DATA,0x0041);//6
	IO_write(HPI_DATA,0x0013);//8
	IO_write(HPI_DATA,0x0000);//a

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
}

void UsbSetConfig()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //port address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0900);
	IO_write(HPI_DATA,0x0001);//device address
	IO_write(HPI_DATA,0x0000);
	IO_write(HPI_DATA,0x0000);
	//in packet
	IO_write(HPI_DATA,0x0000); //don't care
	IO_write(HPI_DATA,0x0000);//port number
	IO_write(HPI_DATA,0x0290);//device address
	IO_write(HPI_DATA,0x0041); //data 1
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0000);

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr

}

void UsbClassRequest()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //port address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0A21);
	IO_write(HPI_DATA,0x0000);//device address
	IO_write(HPI_DATA,0x0000);
	IO_write(HPI_DATA,0x0000);
	//in packet
	IO_write(HPI_DATA,0x0000); //don't care
	IO_write(HPI_DATA,0x0000);//port number /data length
	IO_write(HPI_DATA,0x0290);//device address
	IO_write(HPI_DATA,0x0041); //data 1
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0000);

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
}


void UsbGetHidDesc()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //port address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0681);//c
	IO_write(HPI_DATA,0x2100);//e //HID 0x21
	IO_write(HPI_DATA,0x0000);//0
	IO_write(HPI_DATA,0x007B);//2

	//data phase IN-1
	IO_write(HPI_DATA,0x0544); //514
	IO_write(HPI_DATA,0x0008);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0520);//e

	//status phase
	IO_write(HPI_DATA,0x0000); //52c
	IO_write(HPI_DATA,0x0000);//e
	IO_write(HPI_DATA,0x0210);//530
	IO_write(HPI_DATA,0x0041);//2
	IO_write(HPI_DATA,0x0013);//4
	IO_write(HPI_DATA,0x0000);//6

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr

}


void UsbGetReportDesc()
{
	//the starting address
	IO_write(HPI_ADDR,0x0500); //the start address
	IO_write(HPI_DATA,0x050C);
	IO_write(HPI_DATA,0x0008); //4 port number
	IO_write(HPI_DATA,0x02D0); //device address
	IO_write(HPI_DATA,0x0001);
	IO_write(HPI_DATA,0x0013);
	IO_write(HPI_DATA,0x0514);

	//td content 4 bytes
	IO_write(HPI_DATA,0x0681);//c
	IO_write(HPI_DATA,0x2200);//e //report 0x22
	IO_write(HPI_DATA,0x0000);//0
	IO_write(HPI_DATA,0x007B);//2

	//data phase IN-1
	IO_write(HPI_DATA,0x0580); //514
	IO_write(HPI_DATA,0x0008);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0520);//e

	//data phase IN-2
	IO_write(HPI_DATA,0x0588); //520
	IO_write(HPI_DATA,0x0008);//2
	IO_write(HPI_DATA,0x0290);//4
	IO_write(HPI_DATA,0x0001);//6 //data0
	IO_write(HPI_DATA,0x0013);//8
	IO_write(HPI_DATA,0x052c);//a

	//data phase IN-3
	IO_write(HPI_DATA,0x0590); //52c
	IO_write(HPI_DATA,0x0008);//e
	IO_write(HPI_DATA,0x0290);//530
	IO_write(HPI_DATA,0x0041);//2
	IO_write(HPI_DATA,0x0013);//4
	IO_write(HPI_DATA,0x0538);//6

	//data phase IN-4
	IO_write(HPI_DATA,0x0598); //538
	IO_write(HPI_DATA,0x0008);//a
	IO_write(HPI_DATA,0x0290);//c
	IO_write(HPI_DATA,0x0001);//e //data0
	IO_write(HPI_DATA,0x0013);//540
	IO_write(HPI_DATA,0x0544);//2

	//data phase IN-5
	IO_write(HPI_DATA,0x05a0); //544
	IO_write(HPI_DATA,0x0008);//6
	IO_write(HPI_DATA,0x0290);//8
	IO_write(HPI_DATA,0x0041);//a //data1
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0550);//e

	//data phase IN-6
	IO_write(HPI_DATA,0x05a8); //550
	IO_write(HPI_DATA,0x0008);//2
	IO_write(HPI_DATA,0x0290);//4
	IO_write(HPI_DATA,0x0001);//6 //data0
	IO_write(HPI_DATA,0x0013);//8
	IO_write(HPI_DATA,0x055c);//a

	//data phase IN-7
	IO_write(HPI_DATA,0x05b0); //c
	IO_write(HPI_DATA,0x0008);//e
	IO_write(HPI_DATA,0x0290);//560
	IO_write(HPI_DATA,0x0041);//2 //data1
	IO_write(HPI_DATA,0x0013);//4
	IO_write(HPI_DATA,0x0568);//6

	//data phase IN-8
	IO_write(HPI_DATA,0x05b8); //8
	IO_write(HPI_DATA,0x0003);//a
	IO_write(HPI_DATA,0x0290);//c
	IO_write(HPI_DATA,0x0001);//e //data0
	IO_write(HPI_DATA,0x0013);//570
	IO_write(HPI_DATA,0x0574);//2

	//status phase
	IO_write(HPI_DATA,0x0000); //574
	IO_write(HPI_DATA,0x0000);//6
	IO_write(HPI_DATA,0x0210);//8
	IO_write(HPI_DATA,0x0041);//a
	IO_write(HPI_DATA,0x0013);//c
	IO_write(HPI_DATA,0x0000);//e

	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr

}


alt_u16 UsbWaitTDListDone()
{
	alt_u16 usb_ctl_val;

	usb_ctl_val = UsbRead(HPI_SIE1_MSG_ADR); // STEP 3 j
	UsbWrite(HPI_SIE1_MSG_ADR, 0);
	while (usb_ctl_val != HUSB_TDListDone)  // k, read sie1 msg register
	{
		if(usb_ctl_val == 0x0000)
		{
		}
		else
		{
			printf("[SIE1 MSG]:SIE1 msg reg is %x\n",usb_ctl_val);
		}
		usb_ctl_val = UsbRead(HPI_SIE1_MSG_ADR);
		UsbWrite(HPI_SIE1_MSG_ADR, 0);
	}

	return usb_ctl_val;
}


alt_u16 UsbGetRetryCnt()
{
	alt_u16 usb_ctl_val;

	IO_read(HPI_STATUS);
	if(UsbRead(HPI_SIE1_MSG_ADR) == HUSB_TDListDone)
	{
		UsbWrite(HPI_SIE1_MSG_ADR, 0);

		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
		}
	}
	//usleep(1000);
	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);

	return usb_ctl_val;
}


void UsbPrintMem()
{
	int i, code;
	IO_write(HPI_ADDR,0x0500); //the start address
	for (i = 0; i <= 200; i += 2)
	{
		code = IO_read(HPI_DATA);
		printf("\naddr %x = %04x\n", 0x0500+i, code);
	}
}

uint16_t usb_read_key(void)
{
    static int toggle = 0;
    IO_write(HPI_ADDR,0x0500); //the start address
    //data phase IN-1
    IO_write(HPI_DATA,0x051c); //500

    IO_write(HPI_DATA,0x000f & data_size);//2 data length

    IO_write(HPI_DATA,0x0291);//4 //endpoint 1
    if(toggle%2)
    {
        IO_write(HPI_DATA,0x0001);//6 //data 1
    }
    else
    {
        IO_write(HPI_DATA,0x0041);//6 //data 1
    }
    IO_write(HPI_DATA,0x0013);//8
    IO_write(HPI_DATA,0x0000);//a
    UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr

    while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
    {
        IO_write(HPI_ADDR,0x0500); //the start address
        //data phase IN-1
        IO_write(HPI_DATA,0x051c); //500

        IO_write(HPI_DATA,0x000f & data_size);//2 data length

        IO_write(HPI_DATA,0x0291);//4 //endpoint 1
        if(toggle%2)
        {
            IO_write(HPI_DATA,0x0001);//6 //data 1
        }
        else
        {
            IO_write(HPI_DATA,0x0041);//6 //data 1
        }
        IO_write(HPI_DATA,0x0013);//8
        IO_write(HPI_DATA,0x0000);//
        UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
        usleep(1*1000);
    }//end while

    UsbWaitTDListDone();

    // The first two keycodes are stored in 0x051E. Other keycodes are in
    // subsequent addresses.
    return UsbRead(0x051e) & 0xFF;
}

void setup_usb(void)
{
	IO_init();

	alt_u16 intStat;
	alt_u16 usb_ctl_val;
	static alt_u16 ctl_reg = 0;
	static alt_u16 no_device = 0;
	alt_u8 hot_plug_count;
	alt_u16 code;

	//----------------------------------------SIE1 initial---------------------------------------------------//
	USB_HOT_PLUG:
	UsbSoftReset();

	// STEP 1a:
	UsbWrite (HPI_SIE1_MSG_ADR, 0);
	UsbWrite (HOST1_STAT_REG, 0xFFFF);

	/* Set HUSB_pEOT time */
	UsbWrite(HUSB_pEOT, 600); // adjust the according to your USB device speed

	usb_ctl_val = SOFEOP1_TO_CPU_EN | RESUME1_TO_HPI_EN;// | SOFEOP1_TO_HPI_EN;
	UsbWrite(HPI_IRQ_ROUTING_REG, usb_ctl_val);

	intStat = A_CHG_IRQ_EN | SOF_EOP_IRQ_EN ;
	UsbWrite(HOST1_IRQ_EN_REG, intStat);
	// STEP 1a end

	// STEP 1b begin
	UsbWrite(COMM_R0,0x0000);//reset time
	UsbWrite(COMM_R1,0x0000);  //port number
	UsbWrite(COMM_R2,0x0000);  //r1
	UsbWrite(COMM_R3,0x0000);  //r1
	UsbWrite(COMM_R4,0x0000);  //r1
	UsbWrite(COMM_R5,0x0000);  //r1
	UsbWrite(COMM_R6,0x0000);  //r1
	UsbWrite(COMM_R7,0x0000);  //r1
	UsbWrite(COMM_R8,0x0000);  //r1
	UsbWrite(COMM_R9,0x0000);  //r1
	UsbWrite(COMM_R10,0x0000);  //r1
	UsbWrite(COMM_R11,0x0000);  //r1
	UsbWrite(COMM_R12,0x0000);  //r1
	UsbWrite(COMM_R13,0x0000);  //r1
	UsbWrite(COMM_INT_NUM,HUSB_SIE1_INIT_INT); //HUSB_SIE1_INIT_INT
	IO_write(HPI_MAILBOX,COMM_EXEC_INT);

	while (!(IO_read(HPI_STATUS) & 0xFFFF) )  //read sie1 msg register
	{
	}
	while (IO_read(HPI_MAILBOX) != COMM_ACK)
	{
		printf("[ERROR]:routine mailbox data is %x\n",IO_read(HPI_MAILBOX));
		goto USB_HOT_PLUG;
	}
	// STEP 1b end

	printf("STEP 1 Complete");
	// STEP 2 begin
	UsbWrite(COMM_INT_NUM,HUSB_RESET_INT); //husb reset
	UsbWrite(COMM_R0,0x003c);//reset time
	UsbWrite(COMM_R1,0x0000);  //port number
	UsbWrite(COMM_R2,0x0000);  //r1
	UsbWrite(COMM_R3,0x0000);  //r1
	UsbWrite(COMM_R4,0x0000);  //r1
	UsbWrite(COMM_R5,0x0000);  //r1
	UsbWrite(COMM_R6,0x0000);  //r1
	UsbWrite(COMM_R7,0x0000);  //r1
	UsbWrite(COMM_R8,0x0000);  //r1
	UsbWrite(COMM_R9,0x0000);  //r1
	UsbWrite(COMM_R10,0x0000);  //r1
	UsbWrite(COMM_R11,0x0000);  //r1
	UsbWrite(COMM_R12,0x0000);  //r1
	UsbWrite(COMM_R13,0x0000);  //r1

	IO_write(HPI_MAILBOX,COMM_EXEC_INT);

	while (IO_read(HPI_MAILBOX) != COMM_ACK)
	{
		printf("[ERROR]:routine mailbox data is %x\n",IO_read(HPI_MAILBOX));
		goto USB_HOT_PLUG;
	}
	// STEP 2 end

	ctl_reg = USB1_CTL_REG;
	no_device = (A_DP_STAT | A_DM_STAT);
	usb_ctl_val = UsbRead(ctl_reg);

	if (!(usb_ctl_val & no_device))
	{
		for(hot_plug_count = 0 ; hot_plug_count < 5 ; hot_plug_count++)
		{
			usleep(5*1000);
			usb_ctl_val = UsbRead(ctl_reg);
			if(usb_ctl_val & no_device) break;
		}
		if(!(usb_ctl_val & no_device))
		{
			printf("\n[INFO]: no device is present in SIE1!\n");
			printf("[INFO]: please insert a USB keyboard in SIE1!\n");
			while (!(usb_ctl_val & no_device))
			{
				usb_ctl_val = UsbRead(ctl_reg);
				if(usb_ctl_val & no_device)
					goto USB_HOT_PLUG;

				usleep(2000);
			}
		}
	}
	else
	{
		/* check for low speed or full speed by reading D+ and D- lines */
        /*
		if (usb_ctl_val & fs_device)
		{
			/printf("[INFO]: full speed device\n");
		}
		else
		{
			printf("[INFO]: low speed device\n");
		}
        */
	}



	// STEP 3 begin
	//------------------------------------------------------set address -----------------------------------------------------------------
	UsbSetAddress();

	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		UsbSetAddress();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506); // i
	printf("[ENUM PROCESS]:step 3 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508); // n
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 3 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03) // retries occurred
	{
		usb_ctl_val = UsbGetRetryCnt();

		goto USB_HOT_PLUG;
	}

	//printf("------------[ENUM PROCESS]:set address done!---------------\n");

	// STEP 4 begin
	//-------------------------------get device descriptor-1 -----------------------------------//
	// TASK: Call the appropriate function for this step.
	UsbGetDeviceDesc1(); 	// Get Device Descriptor -1

	usleep(10*1000);
	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbGetDeviceDesc1();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	printf("[ENUM PROCESS]:step 4 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 4 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}

	//printf("---------------[ENUM PROCESS]:get device descriptor-1 done!-----------------\n");


	//--------------------------------get device descriptor-2---------------------------------------------//
	//get device descriptor
	// TASK: Call the appropriate function for this step.
	UsbGetDeviceDesc2(); 	// Get Device Descriptor -2

	//if no message
	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		//resend the get device descriptor
		//get device descriptor
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbGetDeviceDesc2();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	//printf("[ENUM PROCESS]:step 4 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	//printf("[ENUM PROCESS]:step 4 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}

	//printf("------------[ENUM PROCESS]:get device descriptor-2 done!--------------\n");


	// STEP 5 begin
	//-----------------------------------get configuration descriptor -1 ----------------------------------//
	// TASK: Call the appropriate function for this step.
	UsbGetConfigDesc1(); 	// Get Configuration Descriptor -1

	//if no message
	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		//resend the get device descriptor
		//get device descriptor

		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbGetConfigDesc1();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	//printf("[ENUM PROCESS]:step 5 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 5 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}
	//printf("------------[ENUM PROCESS]:get configuration descriptor-1 pass------------\n");

	// STEP 6 begin
	//-----------------------------------get configuration descriptor-2------------------------------------//
	//get device descriptor
	// TASK: Call the appropriate function for this step.
	UsbGetConfigDesc2(); 	// Get Configuration Descriptor -2

	usleep(100*1000);
	//if no message
	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbGetConfigDesc2();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	//printf("[ENUM PROCESS]:step 6 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 6 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}


	//printf("-----------[ENUM PROCESS]:get configuration descriptor-2 done!------------\n");


	// ---------------------------------get device info---------------------------------------------//

	// TASK: Write the address to read from the memory for byte 7 of the interface descriptor to HPI_ADDR.
	IO_write(HPI_ADDR,0x056c);
	code = IO_read(HPI_DATA);
	code = code & 0x003;
	//printf("\ncode = %x\n", code);

	if (code == 0x01)
	{
	//	printf("\n[INFO]:check TD rec data7 \n[INFO]:Keyboard Detected!!!\n\n");
	}
	else
	{
		printf("\n[INFO]:Keyboard Not Detected!!! \n\n");
	}

	// TASK: Write the address to read from the memory for the endpoint descriptor to HPI_ADDR.

	IO_write(HPI_ADDR,0x0576);
	IO_write(HPI_DATA,0x073F);
	IO_write(HPI_DATA,0x8105);
	IO_write(HPI_DATA,0x0003);
	IO_write(HPI_DATA,0x0008);
	IO_write(HPI_DATA,0xAC0A);
	UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0576); //HUSB_SIE1_pCurrentTDPtr

	//data_size = (IO_read(HPI_DATA)>>8)&0x0ff;
	//data_size = 0x08;//(IO_read(HPI_DATA))&0x0ff;
	//UsbPrintMem();
	IO_write(HPI_ADDR,0x057c);
	data_size = (IO_read(HPI_DATA))&0x0ff;
	//printf("[ENUM PROCESS]:data packet size is %d\n",data_size);
	// STEP 7 begin
	//------------------------------------set configuration -----------------------------------------//
	// TASK: Call the appropriate function for this step.
	UsbSetConfig();		// Set Configuration

	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbSetConfig();		// Set Configuration
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	printf("[ENUM PROCESS]:step 7 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 7 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}

	printf("------------[ENUM PROCESS]:set configuration done!-------------------\n");

	//----------------------------------------------class request out ------------------------------------------//
	// TASK: Call the appropriate function for this step.
	UsbClassRequest();

	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbClassRequest();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	printf("[ENUM PROCESS]:step 8 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 8 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}


	printf("------------[ENUM PROCESS]:class request out done!-------------------\n");

	// STEP 8 begin
	//----------------------------------get descriptor(class 0x21 = HID) request out --------------------------------//
	// TASK: Call the appropriate function for this step.
	UsbGetHidDesc();

	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbGetHidDesc();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	printf("[ENUM PROCESS]:step 8 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]:step 8 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}

	printf("------------[ENUM PROCESS]:get descriptor (class 0x21) done!-------------------\n");

	// STEP 9 begin
	//-------------------------------get descriptor (class 0x22 = report)-------------------------------------------//
	// TASK: Call the appropriate function for this step.
	UsbGetReportDesc();
	//if no message
	while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
	{
		// TASK: Call the appropriate function again if it wasn't processed successfully.
		UsbGetReportDesc();
		usleep(10*1000);
	}

	UsbWaitTDListDone();

	IO_write(HPI_ADDR,0x0506);
	printf("[ENUM PROCESS]: step 9 TD Status Byte is %x\n",IO_read(HPI_DATA));

	IO_write(HPI_ADDR,0x0508);
	usb_ctl_val = IO_read(HPI_DATA);
	printf("[ENUM PROCESS]: step 9 TD Control Byte is %x\n",usb_ctl_val);
	while (usb_ctl_val != 0x03)
	{
		usb_ctl_val = UsbGetRetryCnt();
	}

	printf("---------------[ENUM PROCESS]:get descriptor (class 0x22) done!----------------\n");
}

