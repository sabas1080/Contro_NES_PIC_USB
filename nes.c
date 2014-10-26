 /////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                          USB Nintendo Controller                          //
//                                                                           //
//  Author: Drew Hall (dhall@zero-soft.com)                                  //
//  Date: June 05, 2005                                                      //
//  Purpose: Connects a Nintendo game controller to a PC via USB             //
//                                                                           //
//                                                                           //
// Modifications from CSS 4.xxx: Andres Eduardo Sabas Jimenez                //
// Date: June 17, 2012                                                       //
// (sabasjimenez@gmail.com)                                                                          //
//                                                                           //
//                                                                           //
//  Notes:                                                                   //
//  1) Connect the NES controller to pins A0, A1, and A2 as shown below      //
//     Yellow Wire -> PIN_A0                                                 //
//     Red Wire -> PIN_A1                                                    //
//     Orange Wire -> PIN_A2                                                 //
//  2) Connect a 4Mhz ceramic resonator/crystal (or change the fuses)       //
//  3) Connect a 220nF capacitor from Vusb to Gnd                            //
//  4) Connect the USB cable to Vcc, Gnd, D+, and D-                         //
//     D+ (Green Wire) -> PIN_RC5                                            // 
//     D- (White Wire) -> PIN_RC4                                            //
//  5) If you want status information, connect the status LED's to pins      //
//     B0 and B1                                                             //
//     Both LEDs Off - PIC not initialized                                   //
//     LED0 Blinking, LED1 Off - Waiting for enumeration                     //
//     Both LEDs On - Normal Operation                                       //
//  6) For information on the development, please visit www.Zero-Soft.com    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////
 
 
//////////////////////////
//    DEVICE  CONFIG    //
//////////////////////////

#include <18F4550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL3,CPUDIV1,VREGEN
#use delay(clock=48000000)

#DEFINE USB_HID_DEVICE TRUE

#define USB_EP1_TX_ENABLE USB_ENABLE_INTERRUPT //turn on EP1 for IN bulk/interrupt transfers
#define USB_EP1_TX_SIZE 8

#define USB_EP1_RX_ENABLE USB_ENABLE_INTERRUPT //turn on EP1 for IN bulk/interrupt transfers
#define USB_EP1_RX_SIZE 8

#include <pic18_usb.h>
#include <usb_kbd_HID.h> //USB Configuration and Device descriptors for this UBS device
#include <usb.c> //handles usb setup tokens and get descriptor reports


/////////////////////////////////////////////////////////////////////////////
//
// Defines y Zarandajas
//
/////////////////////////////////////////////////////////////////////////////

#define NES_DATA   PIN_A0                  // Input
#define NES_CLK      PIN_A1                  // Output
#define NES_LATCH   PIN_A2                  // Output
#define LED0      PIN_B0                  // Output
#define LED1      PIN_B1                  // Output

//////////////////////////
//   GLOBAL VARIABLES   //
//////////////////////////
int8 ConState;                           // RIGHT, LEFT, DOWN, UP, START, SELECT, B, A
#define A      0x01
#define B      0x02
#define SELECT   0x04
#define START   0x08
#define UP       0x10
#define DOWN   0x20
#define LEFT   0x40
#define RIGHT   0x80

//////////////////////////
//        NES FSM       //
//////////////////////////
#int_timer1
void NES_Read()
{
   static int8 PS = 0;
   static int8 FIFO;                     // Setup a buffer
   
   set_timer1(65036);                     // 2 KHz

   if(ps == 0)
   {
      output_bit(NES_LATCH, 1);
      output_bit(NES_CLK, 0);
   }
   else if(ps == 1)
   {
      output_bit(NES_LATCH, 0);
      FIFO = 0;
      shift_right(&FIFO, 1, !input(NES_DATA));
   }
   else if(ps == 15)
   {
      shift_right(&FIFO, 1, !input(NES_DATA));
      output_bit(NES_CLK, 0);
      ConState = FIFO;
      ps = 255;
   }
   else if(bit_test(PS,0))                  // Falling edge
   {
      shift_right(&FIFO, 1, !input(NES_DATA));
      output_bit(NES_CLK, 0);
   }
   else                              // Rising edge
   {
      output_bit(NES_CLK, 1);
   }
   
   if(++ps > 15)
      ps = 0;
}

//////////////////////////
//     ENTRY POINT      //
//////////////////////////
void main() 
{
    signed int8 out_data[3];
       
   set_tris_a(0x01);                     // PortA outputs except for NES_DATA (RA0)
   setup_timer_1(T1_INTERNAL);               // Scan the NES controller
   usb_init();                           // Initialize USB subsystem
   setup_wdt(WDT_ON);
   
   enable_interrupts(INT_TIMER1);            // Timer1 interrupts
   enable_interrupts(GLOBAL);               // Get the clock pulse rocking
      

   while (TRUE) 
   {
      output_bit(LED0, 0);               // Both LED's off
      output_bit(LED1, 0);
      
      while(!usb_enumerated()) 
      {
         restart_wdt();                  // Reset the watchdog
            
            output_toggle(LED0);
            delay_ms(250);
        }
        
      
        output_bit(LED0, 1);
        output_bit(LED1, 1);
        
        while(usb_enumerated()) 
       {
          restart_wdt();                  // Reset the watchdog
          out_data[0] = 0;               // Transform the data to match the HID
          out_data[1] = 0;                    // This is done this way to match many of
          out_data[2] = 0;                    // the older games that require the data to
                                              // come in a specified order
          if(ConState & A)
             out_data[2] |= 0x01;
          
          if(ConState & B)
             out_data[2] |= 0x02;
             
          if(ConState & SELECT)
             out_data[2] |= 0x04;
          
          if(ConState & START)
             out_data[2] |= 0x08;
          
          if(ConState & UP)
          {
             out_data[2] |= 0x10;
             out_data[1] = -127;
          }
          
          if(ConState & DOWN)
          {
             out_data[2] |= 0x20;
             out_data[1] = 127;
         }
       
          if(ConState & LEFT)
          {
             out_data[0] = -127;
             out_data[2] |= 0x40;
          }
          
          if(ConState & RIGHT)
          {
             out_data[0] = 127;
             out_data[2] |= 0x80;
         }
          
          usb_put_packet(1, &out_data[0], 3, USB_DTS_TOGGLE);   // Send the data off
          
           delay_ms(10);                        // Wait for the next polling event
         }
         
       
   }

}

