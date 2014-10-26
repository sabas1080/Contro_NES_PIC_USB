///////////////////////////////////////////////////////////////////////////
///                          usb_kbd_HID.h                             ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

#IFNDEF __USB_DESCRIPTORS__
#DEFINE __USB_DESCRIPTORS__

#include <usb.h>

   //////////////////////////////////////////////////////////////////
   ///
   ///  HID Report.  Tells HID driver how to handle and deal with
   ///  received data.  HID Reports can be extremely complex,
   ///  see HID specifcation for help on writing your own.
   ///
   ///  First it defines a block for the first report ID for a mouse
   ///  protocol.  Second it defines a block for the second report ID
   ///  for a keyboard protocol.
   ///
   //////////////////////////////////////////////////////////////////

   const char USB_CLASS_SPECIFIC_DESC[] = {
      /*
   0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x08,                    //   USAGE_MAXIMUM (Button 8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
 */
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x15, 0x81,                    //     LOGICAL_MINIMUM (-127)
    0x25, 0x7f,                    //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x08,                    //     USAGE_MAXIMUM (Button 8)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x95, 0x08,                    //     REPORT_COUNT (8)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0xc0                           // END_COLLECTION
  
      
      /*0x05, 0x01, //usage page (generic desktop)   //0,1
      0x09, 0x06, //usage (keyboard)   //2,3
      0xA1, 0x01, //collection (application) //4,5
      0x85, 0x02, //report id (2)   //6,7
      0x05, 0x07, //usage page (key codes)   //8,9
      0x19, 0xE0, //usage min (224) //10,11
      0x29, 0xE7, //usage max (231) //12,13
      0x15, 0x00, //logical min (0) //14,15
      0x25, 0x01, //logical max (1) //16,17
      0x75, 0x01, //report size (1) //18,19
      0x95, 0x08, //report count (8)   //20, 21
      0x81, 0x02, //input (data, variable, absolute) [modifier byte] //22,23
      0x95, 0x01, //report count (1)   //24,25
      0x75, 0x08, //report size (8)    //26,27
      0x81, 0x01, //input (constant) [reserved byte]  //28,29
      0x95, 0x05, //report count (5)   //30,31
      0x75, 0x01, //report size (1)    //32,33
      0x05, 0x08, //usage page (page# for leds) //34,35
      0x19, 0x01, //usage min (1)   //36,37
      0x29, 0x05, //usage max (5)   //38,39
      0x91, 0x02, //output (data, var, abs) [led report] //40,41
      0x95, 0x01, //report count (1)   //42,43
      0x75, 0x03, //report size (3) //44,45
      0x91, 0x01, //output (constant) [led report padding]  //46,47
      0x95, 0x05, //report count (5)   //48,49
      0x75, 0x08, //report size (8) //50,51
      0x15, 0x00, //logical min (0) //52,53
      0x25, 0x65, //logical max (101)  //54,55
      0x05, 0x07, //usage page (key codes)   //56,57
      0x19, 0x00, //usage min (0)   //58,59
      0x29, 0x65, //usage max (101) //60,61
      0x81, 0x00, //input (data, array)   //62,63
      0xC0        //end collection  //64*/
   };

   //if a class has an extra descriptor not part of the config descriptor,
   // this lookup table defines where to look for it in the const
   // USB_CLASS_SPECIFIC_DESC[] array.
   //first element is the config number (if your device has more than one config)
   //second element is which interface number
   //set element to 0xFFFF if this config/interface combo doesn't exist
   const int16 USB_CLASS_SPECIFIC_DESC_LOOKUP[USB_NUM_CONFIGURATIONS][1] =
   {
   //config 1
      //interface 0
         0
   };

   //if a class has an extra descriptor not part of the config descriptor,
   // this lookup table defines the size of that descriptor.
   //first element is the config number (if your device has more than one config)
   //second element is which interface number
   //set element to 0xFFFF if this config/interface combo doesn't exist
   const int16 USB_CLASS_SPECIFIC_DESC_LOOKUP_SIZE[USB_NUM_CONFIGURATIONS][2] =
   {
   //config 1
      //interface 0
      sizeof(USB_CLASS_SPECIFIC_DESC)
   };

//////////////////////////////////////////////////////////////////
///
///   start config descriptor
///   right now we only support one configuration descriptor.
///   the config, interface, class, and endpoint goes into this array.
///
//////////////////////////////////////////////////////////////////

   #DEFINE USB_TOTAL_CONFIG_LEN      41 //config+interface+class+endpoint

   const char USB_CONFIG_DESC[] = {
   //IN ORDER TO COMPLY WITH WINDOWS HOSTS, THE ORDER OF THIS ARRAY MUST BE:
      //    config(s)
      //    interface(s)
      //    class(es)
      //    endpoint(s)

   //config_descriptor for config index 1
         USB_DESC_CONFIG_LEN, //length of descriptor size          ==0
         USB_DESC_CONFIG_TYPE, //constant CONFIGURATION (CONFIGURATION 0x02)     ==1
         USB_TOTAL_CONFIG_LEN,0, //size of all data returned for this config      ==2,3
         1, //number of interfaces this device supports       ==4
         0x01, //identifier for this configuration.  (IF we had more than one configurations)      ==5
         0x00, //index of string descriptor for this configuration      ==6
         0xC0, //bit 6=1 if self powered, bit 5=1 if supports remote wakeup (we don't), bits 0-4 unused and bit7=1         ==7
         0x32, //maximum bus power required (maximum milliamperes/2)  (0x32 = 100mA)   //8

   //interface descriptor 1 (MOUSE)
         USB_DESC_INTERFACE_LEN, //length of descriptor      =9
         USB_DESC_INTERFACE_TYPE, //constant INTERFACE (INTERFACE 0x04)       =10
         0x00, //number defining this interface (IF we had more than one interface)    ==11
         0x00, //alternate setting     ==12
         2, //number of endpoints for this interface  //13
         0x03, //class code, 03 = HID     ==14
         0x00, //subclass code //boot     ==15
         0x00, //protocol code       ==16
         0x00, //index of string descriptor for interface      ==17

   //class descriptor 1  (HID)
         USB_DESC_CLASS_LEN, //length of descriptor    ==18
         USB_DESC_CLASS_TYPE, //dscriptor type (0x21 == HID)      ==19
         0x00,0x01, //hid class release number (1.0) (try 1.10)      ==20,21
         0x00, //localized country code (0 = none)       ==22
         0x01, //number of hid class descrptors that follow (1)      ==23
         0x22, //report descriptor type (0x22 == HID)                ==24
         USB_CLASS_SPECIFIC_DESC_LOOKUP_SIZE[0][0], 0x00, //length of report descriptor            ==25,26

   //endpoint descriptor 1 IN
         USB_DESC_ENDPOINT_LEN, //length of descriptor                   ==27
         USB_DESC_ENDPOINT_TYPE, //constant ENDPOINT (ENDPOINT 0x05)          ==28
         0x81, //endpoint number and direction (0x81 = EP1 IN)       ==29
         USB_ENDPOINT_TYPE_INTERRUPT, //transfer type supported (0x03 is interrupt)         ==30
         USB_EP1_TX_SIZE,0x00, //maximum packet size supported                  ==31,32
         10  //polling interval, in ms.  (cant be smaller than 10 for slow speed devices)     ==33

   //endpoint descriptor 1 OUT
         USB_DESC_ENDPOINT_LEN, //length of descriptor                   ==34
         USB_DESC_ENDPOINT_TYPE, //constant ENDPOINT (ENDPOINT 0x05)          ==35
         0x01, //endpoint number and direction (0x01 = EP1 OUT)       ==36
         USB_ENDPOINT_TYPE_INTERRUPT, //transfer type supported (0x03 is interrupt)         ==37
         USB_EP1_RX_SIZE,0x00, //maximum packet size supported                  ==38,39
         10  //polling interval, in ms.  (cant be smaller than 10 for slow speed devices)     ==40
   };



   //****** BEGIN CONFIG DESCRIPTOR LOOKUP TABLES ********
   //since we can't make pointers to constants in certain pic16s, this is an offset table to find
   //  a specific descriptor in the above table.

   //NOTE: DO TO A LIMITATION OF THE CCS CODE, ALL HID INTERFACES MUST START AT 0 AND BE SEQUENTIAL
   //      FOR EXAMPLE, IF YOU HAVE 2 HID INTERFACES THEY MUST BE INTERFACE 0 AND INTERFACE 1
   #define USB_NUM_HID_INTERFACES   1

   //the maximum number of interfaces seen on any config
   //for example, if config 1 has 1 interface and config 2 has 2 interfaces you must define this as 2
   #define USB_MAX_NUM_INTERFACES   1

   //define how many interfaces there are per config.  [0] is the first config, etc.
   const char USB_NUM_INTERFACES[USB_NUM_CONFIGURATIONS]={1};

   //define where to find class descriptors
   //first dimension is the config number
   //second dimension specifies which interface
   //last dimension specifies which class in this interface to get, but most will only have 1 class per interface
   //if a class descriptor is not valid, set the value to 0xFFFF
   const int16 USB_CLASS_DESCRIPTORS[USB_NUM_CONFIGURATIONS][1][1]=
   {
   //config 1
      //interface 0
         //class 1
         18
   };

   //****** END CONFIG DESCRIPTOR LOOKUP TABLES ********

   #if (sizeof(USB_CONFIG_DESC) != USB_TOTAL_CONFIG_LEN)
      #error USB_TOTAL_CONFIG_LEN not defined correctly
   #endif


//////////////////////////////////////////////////////////////////
///
///   start device descriptors
///
//////////////////////////////////////////////////////////////////

   const char USB_DEVICE_DESC[] = {
      //starts of with device configuration. only one possible
         USB_DESC_DEVICE_LEN, //the length of this report   ==1
         0x01, //the constant DEVICE (DEVICE 0x01)  ==2
         0x10,0x01, //usb version in bcd (pic167xx is 1.1) ==3,4
         0x00, //class code ==5
         0x00, //subclass code ==6
         0x00, //protocol code ==7
         USB_MAX_EP0_PACKET_LENGTH, //max packet size for endpoint 0. (SLOW SPEED SPECIFIES 8) ==8
         0x61,0x04, //vendor id (0x04D8 is Microchip, or is it 0x0461 ??)
         0x57,0x00, //product id   ==11,12  //don't use ffff says usb-by-example guy.  oops
         0x00,0x01, //device release number  ==13,14
         0x01, //index of string description of manufacturer. therefore we point to string_1 array (see below)  ==15
         0x02, //index of string descriptor of the product  ==16
         0x00, //index of string descriptor of serial number  ==17
         USB_NUM_CONFIGURATIONS  //number of possible configurations  ==18
   };

   #if (sizeof(USB_DEVICE_DESC) != USB_DESC_DEVICE_LEN)
      #error USB_DESC_DEVICE_LEN not defined correctly
   #endif


//////////////////////////////////////////////////////////////////
///
///   start string descriptors
///   String 0 is a special language string, and must be defined.  People in U.S.A. can leave this alone.
///
//////////////////////////////////////////////////////////////////

//the offset of the starting location of each string.  offset[0] is the start of string 0, offset[1] is the start of string 1, etc.
const char USB_STRING_DESC_OFFSET[]={0,4,12};

//number of strings you have, including string 0.
#define USB_STRING_DESC_COUNT sizeof(USB_STRING_DESC_OFFSET)

char const USB_STRING_DESC[]={
   //string 0
         4, //length of string index
         USB_DESC_STRING_TYPE, //descriptor type 0x03 (STRING)
         0x09,0x04,   //Microsoft Defined for US-English
   //string 1
         8, //length of string index
         USB_DESC_STRING_TYPE, //descriptor type 0x03 (STRING)
         'S',0,
         'b',0,
         's',0,
   //string 2
         46, //length of string index
         USB_DESC_STRING_TYPE, //descriptor type 0x03 (STRING)
         'U',0,
         'S',0,
         'B',0,
         ' ',0,
         'K',0,
         'e',0,
         'y',0,
         'b',0,
         'o',0,
         'a',0,
         'r',0,
         'd',0,
         ' ',0,
         'b',0,
         'y',0,
         ' ',0,
         'S',0,
         'a',0,
         'b',0,
         'a',0,
         's',0,
         ':',0
};
