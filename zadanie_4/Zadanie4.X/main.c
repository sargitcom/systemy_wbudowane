// CONFIG1H
#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF

#include <xc.h>

#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0

//dodane linie 3 i 4
#define L_L3    0x90
#define L_L4    0x00

#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

#include <xc.h>

unsigned int heatingMinutes = 0;
unsigned int heatingSeconds = 0;
unsigned int power = 0;
unsigned int wereSettingsUpdated = 1;
unsigned int isHeatingOn = 0;

void lcd_wr(unsigned char val)
{
  LPORT=val;
}


void lcd_dat(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=1;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}

void lcd_str(const char* str)
{
 unsigned char i=0;
  
 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }  
}

void delay(unsigned int ms)
{
    unsigned int i;
    unsigned char j;
   
 for (i =0; i< ms; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
      Nop();
      Nop();
      Nop();
      Nop();
      Nop();
   }
 }
}

void cook(unsigned int ms)
{
    unsigned int i;
    unsigned char j;
   
 for (i =0; i< ms; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
      Nop();

        if(PORTBbits.RB2 == 0) {
            isHeatingOn = (isHeatingOn == 1 ? 0 : 1);
        }
      
      
    if((PORTBbits.RB5 == 0))
    {
        
        
        if (power < 2) {
            power++;
        } else {
            power = 0;
        }
    }

      
      Nop();
      
        if((PORTBbits.RB2 == 0))
        {
            isHeatingOn = isHeatingOn == 1 ? 0 : 1;
        }
      
      
    if((PORTBbits.RB5 == 0))
    {
        
        
        if (power < 2) {
            power++;
        } else {
            power = 0;
        }
    }

      
      Nop();

        if((PORTBbits.RB2 == 0))
        {
            isHeatingOn = isHeatingOn == 1 ? 0 : 1;
        }      

      
    if((PORTBbits.RB5 == 0))
    {
        
        
        if (power < 2) {
            power++;
        } else {
            power = 0;
        }
    }

      
      Nop();

        if((PORTBbits.RB2 == 0))
        {
            isHeatingOn = isHeatingOn == 1 ? 0 : 1;
        }      
      
      
    if((PORTBbits.RB5 == 0))
    {
        
        
        if (power < 2) {
            power++;
        } else {
            power = 0;
        }
    }

      
      Nop();
      
      
        if((PORTBbits.RB2 == 0))
        {
            isHeatingOn = isHeatingOn == 1 ? 0 : 1;
        }      
      
      
    if((PORTBbits.RB5 == 0))
    {       
        if (power < 2) {
            power++;
        } else {
            power = 0;
        }
    }
   }
 }
}

void printMask(unsigned char * mask)
{
    unsigned char value = 0;
    
    value += (mask[7] * 128);
    value += (mask[6] * 64);
    value += (mask[5] * 32);
    value += (mask[4] * 16); 
    value += (mask[3] * 8); 
    value += (mask[2] * 4); 
    value += (mask[1] * 2); 
    value += mask[0];
    
    PORTD = value;
}

char *cprog_strrev(char *s, size_t n)
{
    size_t i, j;
 
    for (i = 0, j = n - 1; i < j; i++, j--) {
        char savev = s[i];
        s[i] = s[j];
        s[j] = savev;
    }
 
    return s;
}
 
char *cprog_itos(unsigned char value, char *buf, size_t size, int radix)
{
    const char *digits = "0123456789ABCDEF";
 
    int sign = value < 0;
    size_t n = 0;
 
    if (radix == 0) {
        radix = 10;
    }
    
    do
        buf[n++] = digits[abs(value % radix)];
    while (n < size - 1 && (value /= radix) != 0);
 
    if (sign)
        buf[n++] = '-';
 
    buf[n] = '\0';
 
    return cprog_strrev(buf, n);
}

void lcd_cmd(unsigned char val)
{
	LENA=1;
        lcd_wr(val);
        LDAT=0;
        //delay(3);
        LENA=0;
        //delay(3);
	LENA=1;
}

void lcd_init(void)
{
	LENA=0;
	LDAT=0;
	delay(20);
	LENA=1;
	
	lcd_cmd(L_CFG);
	delay(5);
	lcd_cmd(L_CFG);
    delay(1);
	lcd_cmd(L_CFG); //configura
	lcd_cmd(L_OFF);
	lcd_cmd(L_ON); //liga
	lcd_cmd(L_CLR); //limpa
	lcd_cmd(L_CFG); //configura
    lcd_cmd(L_L1);
}

void updatePowerSettings()
{
    unsigned int i = 6000;

    while(PORTBbits.RB5  && i > 0)
    {
        i--;
    }

    if((PORTBbits.RB5 == 0))
    {
        wereSettingsUpdated = 1;
        
        if (power < 2) {
            power++;
        } else {
            power = 0;
        }
    }

    return;
}

void printPowerSettings()
{
    switch(power) {
        case 0:
            if (isHeatingOn == 1) {
                lcd_str("800W grzanie");
            } else {
                lcd_str("800W stop");
            }
            break;

        case 1:
            if (isHeatingOn == 1) {
                lcd_str("600W grzanie");
            } else {
                lcd_str("600W stop");
            }
            break;

        case 2:
            if (isHeatingOn == 1) {
                lcd_str("350W grzanie");
            } else {
                lcd_str("350W stop");
            }
            break;

        case 3:
            if (isHeatingOn == 1) {
                lcd_str("200W grzanie");
            } else {
                lcd_str("200W stop");
            }
            break;
    }
}

int updateMinutes()
{
    unsigned int i = 6000;

    while(PORTBbits.RB4  && i > 0)
    {
        i--;
    }

    if((PORTBbits.RB4 == 0))
    {
        wereSettingsUpdated = 1;
        
        if (heatingMinutes < 998) {
            heatingMinutes++;
        }
        
        return 1;
    }

    return 0;
}

int updateSeconds()
{
    unsigned int i = 6000;

    while(PORTBbits.RB3  && i > 0)
    {
        i--;
    }

    if((PORTBbits.RB3 == 0))
    {
        wereSettingsUpdated = 1;
        
        if (heatingSeconds == 50 && heatingMinutes < 998) {
            heatingMinutes++;
            heatingSeconds = 0;
        } else {
            heatingSeconds += 10;
        }
        
        return 1;
    }

    return 0;
}

void printTime()
{
    char minutesBuffer[5];
    char secondsBuffer[3];
    
    cprog_itos(heatingMinutes, minutesBuffer, 5, 10);
    cprog_itos(heatingSeconds, secondsBuffer, 5, 10);
    
    lcd_cmd(L_L2);
    lcd_str(minutesBuffer);
    lcd_str(" MIN ");
    lcd_str(secondsBuffer);
    lcd_str(" SEC");
}

void updateSettingsOnReset()
{
    unsigned int i = 6000;

    while(PORTBbits.RB1  && i > 0)
    {
        i--;
    }

    if((PORTBbits.RB1 == 0))
    {
        wereSettingsUpdated = 1;
        
        heatingMinutes = 0;
        heatingSeconds = 0;

        return;
    }

    return;
}

void updateStartHeating()
{
    unsigned int i = 6000;

    while(PORTBbits.RB2 && i > 0)
    {
        i--;
    }

    if(PORTBbits.RB2 == 0)
    {   
        PORTD = 255;
        
        isHeatingOn = isHeatingOn == 0 ? 1 : 0;

        return;
    }

    return;
    
}

void heating()
{
    PORTD = 255;

    while ((heatingMinutes > 0 || heatingSeconds > 0) && isHeatingOn == 1) {

        lcd_cmd(L_CLR);

        printPowerSettings();
        printTime();

        
        if (heatingMinutes > 0 || heatingSeconds > 0) {
            if (heatingSeconds > 0) {
                heatingSeconds--;
            } else {
                heatingSeconds = 59;
                heatingMinutes--;
            }
        }
        
        cook(50);
    }

    PORTD = 0;
    isHeatingOn = 0;
    
    printPowerSettings();
    printTime();

    wereSettingsUpdated = 1;
}

void main(void) {
    
    ADCON0=0x01;
    ADCON1=0x0B;
    ADCON2=0x01;
    
    TRISA=0xC3;
    TRISB=0x3F;   
    TRISC=0x01;
    TRISD=0x00;
    TRISE=0x00;
    
    lcd_init();
    
    while(1) {
        
        if (wereSettingsUpdated == 1) {
            lcd_cmd(L_CLR);
            printPowerSettings();
            printTime();
            wereSettingsUpdated = 0;
        }
        
        updatePowerSettings();
        updateMinutes();
        updateSeconds();
        updateSettingsOnReset();
        updateStartHeating();
        if (isHeatingOn == 1) {
            heating();
        }
        
    }
    
    return;
}
