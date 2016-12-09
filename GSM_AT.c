#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "lcddrv.h"				/* LCD driver function prototypes*/
#include "TIMERAPI.h"


#define FBUS 24000000
#define BAUDIOS_SCI2 9600
#define REG_BAUDIOS_SCI2 FBUS/16/BAUDIOS_SCI2

void ADC0(void);
void ADC1(void);
void Port_Init(void);
void Init_Ports(void);
void Init_Pll(void);
void SCI2_PUTCHAR(unsigned char c); //FUNCION PARA ENVIAR UN CARACTER
void SCI2_PUTS(const unsigned char *str2);//FUNCION PARA ENVIAR UNA CADENA
void SCI2_INIT (void);  //INICIALIZACION DE TRANS SERIAL  2
void IRQ_Init(void);
void Celular(void);
void Msm(void);
void Inten(void);
void Recibir(void);
void NoCel(void);
void AbrirMensaje(void);
void Borrar(void);


void main(void) {
  Init_Ports();
  Init_Pll();
  SCI2_INIT();  //PARA INICIALIZAR SERIAL 2
  IRQ_Init();
  EnableInterrupts;
  /* include your code here */


  for(;;) {
   // __RESET_WATCHDOG();	/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
void IRQ_Init (void){
	IRQSC=0X12;
}

void Celular(void){// Configure the GSM module to connect with a SimCard
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('F');
	SCI2_PUTCHAR('U');
	SCI2_PUTCHAR('N');
	SCI2_PUTCHAR('=');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}

void Msm(void){// Configure the GSM module to send sms messages
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('M');
	SCI2_PUTCHAR('G');
	SCI2_PUTCHAR('F');
	SCI2_PUTCHAR('=');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}

void Inten(void){ // Ask fot intensity of the signal
	//unsigned char Intensidad[8]={'A','T','+','C','S','Q',0x0D,0x0A};
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('S');
	SCI2_PUTCHAR('Q');
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}

void Borrar(void){// Command to delete the sms messages
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('M');
	SCI2_PUTCHAR('G');
	SCI2_PUTCHAR('D');
	SCI2_PUTCHAR('=');
	if(i<10){
	SCI2_PUTCHAR(i+0x30);
	}
	else
	{
		SCI2_PUTCHAR((i/10)+0x30);
		SCI2_PUTCHAR((i%10)+0x30);
	}
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}
void Recibir(void){// This command gives the instruction to the GMS module to be a receptor for sms
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('N');
	SCI2_PUTCHAR('M');
	SCI2_PUTCHAR('I');
	SCI2_PUTCHAR('=');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR(',');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR(',');
	SCI2_PUTCHAR('0');
	SCI2_PUTCHAR(',');
	SCI2_PUTCHAR('0');
	SCI2_PUTCHAR(',');
	SCI2_PUTCHAR('0');
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}

void AbrirMensaje(void){ // Command to open the sms that the micro receives
	//AT+CMGR=1<CR><LF>
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('M');
	SCI2_PUTCHAR('G');
	SCI2_PUTCHAR('R');
	SCI2_PUTCHAR('=');
	if(posicion<10){
		SCI2_PUTCHAR(posicion+0x30);
	}
	else{
		SCI2_PUTCHAR((posicion/10)+0x30);
		SCI2_PUTCHAR((posicion%10)+0x30);
	}
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}


void NoCel(void){// The micro send the number of the SimCard that is in the GSM module.
	//AT+CMGS=�numero_de_Celular�<CR><LF>
	SCI2_PUTCHAR('A');
	SCI2_PUTCHAR('T');
	SCI2_PUTCHAR('+');
	SCI2_PUTCHAR('C');
	SCI2_PUTCHAR('M');
	SCI2_PUTCHAR('G');
	SCI2_PUTCHAR('S');
	SCI2_PUTCHAR('=');
	SCI2_PUTCHAR('"');
	SCI2_PUTCHAR('3');
	SCI2_PUTCHAR('2');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR('7');
	SCI2_PUTCHAR('7');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR('5');
	SCI2_PUTCHAR('6');
	SCI2_PUTCHAR('2');
	SCI2_PUTCHAR('1');
	SCI2_PUTCHAR('"');
	SCI2_PUTCHAR(0x0D);
	SCI2_PUTCHAR(0x0A);
}
void SCI2_INIT (void){// Serial port inition

  SCI2BD = REG_BAUDIOS_SCI2;
  SCI2C2 = 0x2C;
}

void SCI2_PUTCHAR(unsigned char h){// Send a character in the serial port
	 while(!SCI2S1_TDRE){ }
 	 SCI2D = h;
}
void SCI2_PUTS(const unsigned char *str2){// Send a String of characters

	while (*str2!=0x00)
			{
				SCI2_PUTCHAR(*str2++);
			}

}

void Init_Ports(void){
	PTBD = 0x04;
	PTBDD_PTBDD2=1;
	PTBDD_PTBDD3=1;
	PTBDD_PTBDD4=1;
	PTBDD_PTBDD5=1;
	/*PTD0--PTD7 are all available for JM60*/

}

void ADC0 (void){//ADC Port 0
	ADCCFG=0x05;
	ADCSC1=0X00;
	while (!ADCSC1_COCO) {}
	Val_ADC0=ADCR;
}

void ADC1 (void){//ADC port 1
	ADCCFG=0x05;
	ADCSC1=0X01;
	while (!ADCSC1_COCO) {}
	Val_ADC1=ADCR;
}

void Init_Pll(void){
	SOPT1 = 0x20; //disable COP
	MCGC2 = 0x36;
	while(!(MCGSC & 0x02));		      //wait for the OSC stable
	MCGC1 = 0x1B;
	MCGC3 = 0x48;
	while ((MCGSC & 0x48) != 0x48);	//wait for the PLL is locked
	FCDIV=0x4E;
}

 void interrupt 23  SCI2_ISR (void) {

   DATO_SCI2= SCI2S1;
   DATO_SCI2= SCI2D;
   bandSCI=1;

   //------------------------------------
   //ESPACIO PARA PROGRAMAR


   //------------------------------------
}


//Interrupcion por IRQ
interrupt VectorNumber_Virq void IRQ_ISR (void){
	IRQSC_IRQACK=1;
	bandIRQ=1;
}
