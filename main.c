#define F_CPU   16000000L
#include <util/delay.h>
#include "lcd.h"
#include "teclado.h"
#include <avr/io.h>
#include "bits.h"


void main(void) 
{
    unsigned char tecla;
    int tela = 0;

    SETBIT(DDRC,5);
    SETBIT(DDRC,4);
    SETBIT(DDRC,3);

    CLRBIT(DDRC,2);
    CLRBIT(DDRC,1);
    CLRBIT(DDRC,0);

    SETBIT(PORTC, 2);
    SETBIT(PORTC, 1);
    SETBIT(PORTC, 0);

    lcd_init();

    lcd(0, 3, "IFSP SALTO");
    lcd(1, 3, "MMRE7  ECA");
    _delay_ms(2000);
    lcd_clr();
    lcd(0, 1, "SPLASH SCREEN");
    _delay_ms(2000);
    lcd_clr();

    teclado_init();

    while( 1 )
    {          
        tecla = teclado_scan();
        switch (tela)
        {
        case 0:
            lcd(0, 2, "TELA INICIAL");
            lcd(1, 0, "A: In      B:Out");
            if(tecla == 'A'){           
                lcd_clr();
                tela=1;
                
            }else if(tecla=='B'){            
                lcd_clr();
                tela=2;
            }
            break;
        case 1:
            lcd(0, 0, "INPUTS  *:Return");
            lcd(1, 0, "A0:   A1:   A2: ");

            if(!BIT(PINC,0)){
                lcd(1, 3, "1");
            }else{
                lcd(1, 3, "0");
            }

            if(!BIT(PINC,1)){
                lcd(1, 9, "1");
            }else{
                lcd(1, 9, "0");
            }

            if(!BIT(PINC,2)){
                lcd(1, 15, "1");
            }else{
                lcd(1, 15, "0");
            }

            if(tecla=='*'){
                tela=0;
                lcd_clr();
            }

            break;

        case 2:
            lcd(0, 0, "OUTPUTS *:Return");
            lcd(1, 0, "R[4]  G[5]  B[6]");
            if(tecla=='*'){
                tela=0;
                lcd_clr();
            }else if(tecla=='4'){
                if(!BIT(PINC,5)){
                    SETBIT(PORTC,5);
                }else{
                    CLRBIT(PORTC,5);
                }
            }else if(tecla=='5'){
                if(!BIT(PINC,4)){
                    SETBIT(PORTC,4);
                }else{
                    CLRBIT(PORTC,4);
                }
            }else if(tecla=='6'){
                if(!BIT(PINC,3)){
                    SETBIT(PORTC,3);
                }else{
                    CLRBIT(PORTC,3);
                }
            }
            break;
        }
    }
}