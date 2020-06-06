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

unsigned char direction = 0;

void intToBinary(unsigned char * buffor, unsigned char value) 
{
    short i = 7;
    while (i >= 0) {
        buffor[i] = ((value >> i) & 1);
        i--;
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

void lcd_str(const char* str)
{
 unsigned char i=0;
  
 while(str[i] != 0 )
 {
   lcd_dat(str[i]);
   i++;
 }  
}

void subProgram1()
{
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 1 start");
    
    unsigned char counter = 0;
    
    unsigned char binBuffer[8];
    
    do {
        intToBinary(binBuffer, counter); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;        
        
        counter++;
    } while (counter < 255);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 1 end");
    delay(200);
}

void subProgram2()
{
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 2 start");
    
    unsigned char counter = 255;
    
    unsigned char binBuffer[8];
    
    do {
        intToBinary(binBuffer, counter); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;        
        
        counter--;
    } while (counter > 1);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 2 end");
    delay(200);
}

unsigned char convertValueToGrayCode(unsigned char value)
{
    return value ^ (value >> 1);
}

void subProgram3()
{
    unsigned char counter = 0;
    unsigned char counterDisplay = 0;
    
    unsigned char binBuffer[8];
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 3 start");
    
    do {
        counterDisplay = convertValueToGrayCode(counter);
        
        intToBinary(binBuffer, counterDisplay); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;        
        
        counter++;
    } while (counter < 255);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 3 end");
}

void subProgram4()
{
    unsigned char counter = 255;
    unsigned char counterDisplay = 0;
    
    unsigned char binBuffer[8];
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 4 start");
    
    do {
        counterDisplay = convertValueToGrayCode(counter);
        
        intToBinary(binBuffer, counterDisplay); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;        
        
        counter--;
    } while (counter > 0);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 4 end");
}

unsigned char convertIntoToBCD(unsigned char counter)
{
    return ((counter / 10) << 4) | (counter % 10);
}

void subProgram5()
{
    unsigned char counter = 0;
    unsigned char counterDisplay = 0;
    
    unsigned char binBuffer[8];
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 5 start");
    
    do {
        counterDisplay = convertIntoToBCD(counter);
        
        intToBinary(binBuffer, counterDisplay); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;        
        
        counter++;
    } while (counter < 99);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 5 end");
}

void subProgram6()
{
    unsigned char counter = 99;
    unsigned char counterDisplay = 0;
    
    unsigned char binBuffer[8];
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 6 start");
    
    do {
        counterDisplay = convertIntoToBCD(counter);
        
        intToBinary(binBuffer, counterDisplay); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;        
        
        counter--;
    } while (counter > 0);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 6 end");
}

unsigned char nextSnake(unsigned char snake)
{
    unsigned char result = snake;
    
    if (result == 7) {
        direction = 0;
    } else if (result == 224) {
        direction = 1;
    }
    
    if (direction == 0) {
        result <<= 1;
    } else {
        result >>= 1;
    }
    
    return result;
}

void subProgram7()
{
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 7 start");
    
    unsigned char counterDisplay = 0;
    unsigned char snake = 7;
    unsigned char binBuffer[8];

    while (1) {
        counterDisplay = snake;
       
        intToBinary(binBuffer, counterDisplay); 
        
        printMask(binBuffer);
        
        if (isProgramInterupted() == 1) return;
        
        delay(200);
        
        if (isProgramInterupted() == 1) return;
        
        snake = nextSnake(snake);
    }
}

void clearMaskFromNthPosition(unsigned char * mask, int position)
{
    for (int i = position - 1; i >= 0; i--) {
        mask[i] = 0;
    }
}

void subProgram8()
{
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 8 start");
    

    unsigned char mask[8];
    mask[7] = 0;
    mask[6] = 0;
    mask[5] = 0;
    mask[4] = 0;
    mask[3] = 0;
    mask[2] = 0;
    mask[1] = 0;
    mask[0] = 1;


    for (int j = 7; j >= 0; j--) {
        for (int i = 0; i <= j; i++) {
            mask[i] = 1;
            if (isProgramInterupted() == 1) return;
            clearMaskFromNthPosition(mask, i);
            if (isProgramInterupted() == 1) return;
            printMask(mask);
            if (isProgramInterupted() == 1) return;
            delay(100);
            if (isProgramInterupted() == 1) return;
        }
    }

    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 8 end");
    delay(500);
}

unsigned char getGeneratedValue(unsigned char seed)
{
    unsigned char rolledSeed = seed >> 1;
    
    unsigned char firstBit = seed & 1;
    unsigned char secondBit = (seed >> 2) & 1;
    unsigned char fifthBit = (seed >> 5) & 1;
    unsigned char sixthBit = (seed >> 6) & 1;
    
    unsigned char xoredBits = firstBit ^ secondBit;
    
    xoredBits ^= fifthBit;
    xoredBits ^= sixthBit;
    
    return rolledSeed | (xoredBits << 5);
}

void subProgram9()
{
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("Program 9 start");
    
    unsigned char seed = 1;
    unsigned char binBuffer[8];
    
    while (1) {
        intToBinary(binBuffer, seed); 
        
        printMask(binBuffer);
    
        seed = getGeneratedValue(seed);
        
        delay(200);
    }   
}

void runSubProgram(unsigned int program)
{
    switch (program) {
        case 1:
            subProgram1();
            break;
            
        case 2:
            subProgram2();
            break;
            
        case 3:
            subProgram3();
            break;

        case 4:
            subProgram4();
            break;
            
        case 5:
            subProgram5();
            break;
            
        case 6:
            subProgram6();
            break;
            
        case 7:
            subProgram7();
            break;
            
        case 8:
            subProgram8();
            break;
            
        case 9:
            subProgram9();
            break;
    }
}

int isProgramInterupted()
{
    unsigned int i = 6000;

    while(PORTBbits.RB4 && PORTBbits.RB3 && i > 0)
    {
        i--;
    }

    if((PORTBbits.RB3 == 0) || (PORTBbits.RB4 == 0))
    {
        return 1;
    }

    return 0;
}

void changeProgram(unsigned int * program)
{
    unsigned int i = 6000;

    while(PORTBbits.RB4 && PORTBbits.RB3 && i > 0)
    {
        i--;
    }

    if(PORTBbits.RB3 == 0)
    {
        if (*program < 9) {
            (*program)++;
        } else {
            *program = 1;
        }
    }
    else if(PORTBbits.RB4 == 0)
    {
        if (*program > 1) {
            (*program)--;
        } else {
            *program = 9;
        }
    }
}

unsigned int potentiometr = 0;

char potentiomer1value[6];
char potentiomer2value[6];

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
    lcd_cmd(L_CLR);
    
    unsigned int program = 1;
    
    while(1) {      
        changeProgram(&program);

        runSubProgram(program);
    }
    
    return;
}
