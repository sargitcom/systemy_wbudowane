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

unsigned int player1minutes = 0;
unsigned int player1seconds = 0;
unsigned int player2minutes = 0;
unsigned int player2seconds = 0;

unsigned int timeForGame = 0;
unsigned int playerNumberTimeIsElapsing = 0;

unsigned int adc(unsigned char kanal)
{
    switch(kanal)
    {
        case 0: ADCON0=0x01; break; //P1
        case 1: ADCON0=0x05; break; //P2
        case 2: ADCON0=0x09; break; 
    }
    
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}

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

void updatePlayersTime()
{
    if(PORTBbits.RB3 == 0) {
        playerNumberTimeIsElapsing = 2;
        
    }
      
    if((PORTBbits.RB5 == 0))
    {
        playerNumberTimeIsElapsing = 1;
    }
}

void reduceTime(unsigned int ms)
{
    unsigned int i;
    unsigned char j;
   
 for (i =0; i< ms; i++)
 {
 
  for (j =0 ; j < 200; j++)
   {
        Nop();

        updatePlayersTime();
      
        Nop();
      
        updatePlayersTime();
      
        Nop();

        updatePlayersTime();
      
        Nop();

        updatePlayersTime();
      
        Nop();
      
        updatePlayersTime();
   }
 }
    
    if (playerNumberTimeIsElapsing == 1) {        
        if (player1seconds > 0 || player1minutes > 0) {
            if (player1seconds > 0) {
                player1seconds--;
            } else {
                player1minutes--;
                player1seconds = 59;
            }
        }
    }
    
    if (playerNumberTimeIsElapsing == 2) {
        if (player1seconds > 0 || player1minutes > 0) {
            if (player2seconds > 0) {
                player2seconds--;
            } else {
                player2minutes--;
                player2seconds = 59;
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

void printTime()
{
    char player1minutesBuffer[5];
    char player1secondsBuffer[3];
    
    char player2minutesBuffer[5];
    char player2secondsBuffer[3];

    cprog_itos(player1minutes, player1minutesBuffer, 5, 10);
    cprog_itos(player1seconds, player1secondsBuffer, 5, 10);

    cprog_itos(player2minutes, player2minutesBuffer, 5, 10);
    cprog_itos(player2seconds, player2secondsBuffer, 5, 10);
    
    if ((player1minutes == 0 && player1seconds == 0) || (player2minutes == 0 && player2seconds == 0)) {
        if (player1minutes == 0 && player1seconds == 0) {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str("GRACZ 1 PRZEGRAL");
        } else {
            lcd_cmd(L_CLR);
            lcd_cmd(L_L1);
            lcd_str("GRACZ 2 PRZEGRAL");
        }
        
        delay(200);
        
        playerNumberTimeIsElapsing = 0;
        player1minutes = 0;
        player1seconds = 0;
        player2minutes = 0;
        player2seconds = 0;

        timeForGame = 0;
        
    } else {
        lcd_cmd(L_CLR);
        lcd_cmd(L_L1);
        lcd_str(player1minutesBuffer);
        lcd_str(" MIN ");
        lcd_str(player1secondsBuffer);
        lcd_str(" SEC");

        lcd_cmd(L_L2);
        lcd_str(player2minutesBuffer);
        lcd_str(" MIN ");
        lcd_str(player2secondsBuffer);
        lcd_str(" SEC");
    }   
}

void updateTimeRemainingSet()
{
    unsigned int time = (unsigned int)(((unsigned int)adc(1)) / 85);
    
    if(timeForGame == 0 || playerNumberTimeIsElapsing == 0) {       
        switch(time) {
            case 1:
                timeForGame = 5;

                player1minutes = 5;           
                player1seconds = 0;
                player2minutes = 5;
                player2seconds = 0;
                break;

            case 2:
                timeForGame = 3;

                player1minutes = 3;
                player1seconds = 0;
                player2minutes = 3;
                player2seconds = 0;
                break;

            case 3: 
                timeForGame = 1;

                player1minutes = 1;
                player1seconds = 0;
                player2minutes = 1;
                player2seconds = 0;
                break;

        }
    }
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
        updateTimeRemainingSet();
        updatePlayersTime();
        
        if (timeForGame != 0) {
            printTime();
        } else {
            lcd_cmd(L_L1);
            lcd_str("USTAL CZAS GRY");
            lcd_cmd(L_L2);
            lcd_str("UZYWAJAC P2");
        }
        
        if (timeForGame != 0 && playerNumberTimeIsElapsing != 0) {
            reduceTime(20);
        }
    }
    
    return;
}
