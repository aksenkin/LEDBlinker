/**
 *  lcdi2ccontroller.c
 *  Extend wiringPilibrary to use with LCD display
 * ----------------------------------------------------------------
 * (c)2016, Dmitry Aksenkin aksenkin@gmail.com
 ****************************************************/

#include "lcdi2ccontroller.h"
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include <string.h>

#define ENABLE_BIT  0b0000100 // Enable bit

// Timing constants
#define E_PULSE  500
#define  E_DELAY  500



static void lcd_strob(int fd, unsigned char byte)
{
    // data and strob pulse

    delayMicroseconds(E_DELAY);
    wiringPiI2CWrite(fd, (byte | ENABLE_BIT));
    delayMicroseconds(E_PULSE);
    wiringPiI2CWrite(fd, (byte & ~ENABLE_BIT));
    delayMicroseconds(E_DELAY);
}

int lcd_init(const int devId)
{
   static int fd =-1;
   if(fd == -1)
        fd = wiringPiI2CSetup(devId);

    // clear display
   lcd_write_byte(fd, 0x33, LCD_CMD, LCD_BACKLIGHT_ON); // 110011 Initialise
   lcd_write_byte(fd, 0x32, LCD_CMD, LCD_BACKLIGHT_ON); // 110010 Initialise
   lcd_write_byte(fd, 0x06, LCD_CMD, LCD_BACKLIGHT_ON); // 000110 Cursor move direction
   lcd_write_byte(fd, 0x0C, LCD_CMD, LCD_BACKLIGHT_ON); // 001100 Display On,Cursor Off, Blink Off
   lcd_write_byte(fd, 0x28, LCD_CMD, LCD_BACKLIGHT_ON); // 101000 Data length, number of lines, font size
   lcd_write_byte(fd, 0x01, LCD_CMD, LCD_BACKLIGHT_ON); // 000001 Clear display

   return fd;
}



 void lcd_write_byte(int fd, unsigned char bits, unsigned char mode, unsigned char backlightMode )
 { unsigned char highBits = mode | (bits & 0xF0) | backlightMode;
    unsigned char lowBits = mode | ((bits<<4) & 0xF0) | backlightMode;
    wiringPiI2CWrite(fd, highBits);
    lcd_strob(fd, highBits);
    wiringPiI2CWrite(fd, lowBits);
    lcd_strob(fd, lowBits);
}

 void lcd_write_message(int fd, const char* message, char lineAddress, unsigned char backlightMode)
 {

    char* displayText = NULL;
    char buffer[16] = "                ";

    if(message != NULL)
    {
        int length = strlen(message);
        if (length > 16)
        {
            length = 16;
        }

            int i;
            for (i = 0; i<length; i++)
            {
                buffer[i] = message[i];
            }

            displayText = buffer;
           // displayText = strcpy(buffer, message);
           // displayText[length] = " ";

    }
    // set line number

    lcd_write_byte(fd, lineAddress, LCD_CMD, backlightMode);

    int i;
    for (i = 0; i<16; i++)
    {
        lcd_write_byte(fd, displayText[i], LCD_CHR, backlightMode);
    }

 }
