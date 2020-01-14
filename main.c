//=============================================================================//
//    Timer com retardo para fluxador de maquina de solda - Versão 1.0         //
// Autor: Eng. Bruno Samuel Luiz de Oliveira                                   //                                                
// Compilador: PCWHD v5.080      Início: 10/01/2020    TÉRMINO: 11/01/2020     //
// Status: Finalizado                                                          //
//=============================================================================//
//  Descrição:Este projeto tem por objetivo o desenvolvimento de um controlador//
//para o controle do  fluxo de solda de  uma máquina de solda  por onda, devido// 
//a  antiga placa estar  inoperante  e  por não  haver  placa de  reposição  na//
//empresa fabricante, sendo  assim  foi se  necessário o desenvolvimento de tal//
//projeto, onde através  desta se pode  controlar o retardo para acionamento do//
//rele ( Comando para  acionamento  da onda de solda e do fluxador) conectado a//
//porta  B4 do PIC  16F1827, os potenciômetros de  controle estão  conectados a//
//entrada A0 e  A1 respectivamente, onde através desses se tem o  controle  de //
//tempo de acionamento e de retardo para o acionamento. Por fim se tem o sensor//
//óptico  conectado a  porta B0 que  tem por objetivo    monitorar a entrada de//
//placas na maquina, assim que   detectada uma placa na entrada da maquina,  o //
//uC aguarda o tempo programado pelo potenciometro de baixa com o rele desliga-//
//do e posteriormente liga o rele e aguarda o tempo ajustado atras do potencio-//
//metro de alta.                                                               //
//=============================================================================//
#include <16F1827.h>                               // Define uC;               //
#device ADC=10                                     // Define numero de bits do //
                                                   // conversor A/D;           //
#fuses INTRC_IO,NOWDT,NOPUT,NOPROTECT,NOCPD,NOMCLR // Define fusíveis;         //
#use delay(internal=4000000)                       // Define clock interno de  //
                                                   // 4mhz;                    //
#use FIXED_IO( B_outputs=PIN_B4 )                  // Porta B de acesso rapido;//
#define relay PIN_B4                               // Define pino do rele de   //
                                                   // controle;                //
#define sensor PIN_B0                              // Define pino de entrada do//
                                                   // sensor;                  //
int32 tempo_alta;                                  // Var. tempo de alta;      //
int32 tempo_baixa;                                 // Var. tempo de baixa;     //
void main()                                        // Função principal;        //
{                                                                              //
setup_adc_ports(ALL_ANALOG | VSS_VREF);            // Config. conversor A/D;   //
setup_adc(ADC_CLOCK_DIV_2);                        // Tempo de clock A/C;      //
delay_ms(1000);                                    // Espera 1s;               //
set_tris_B(0x41);                                  // Config. porta B          //
while(TRUE)                                        // Loop infinito            //
{                                                                              //
output_low(relay);                                 // Desliga rele;            // 
set_adc_channel(0);                                // Seta canal 1 do A/D;     //    
delay_us(12);                                      // Espera 12us;             //
tempo_alta= read_adc();                            // Atribui valor do A/D p/ a//
                                                   // var. tempo_alta;         //
if(tempo_alta<=80){tempo_alta=0;}                  // Verifica se o valor da   //
                                                   // var. é menor que 80 se   //
                                                   // sim zera a var. tempo de //
                                                   // alta(filtro de ruidos    //
                                                   // para o potenciomento);   //
delay_ms(12);                                      // Espera 12us;             //
set_adc_channel(1);                                // Seta canal 2 do A/D;     //    
delay_us(12);                                      // Espera 12us;             //
tempo_baixa=read_adc();                            // Atribui valor do A/D p/ a//
                                                   // var. tempo_baixa;        //
if(tempo_baixa<=80){tempo_baixa=0;}                // Verifica se o valor da   //
                                                   // var. é menor que 80 se   //
                                                   // sim zera a var. tempo de //
                                                   // baixa (filtro de ruidos  //
                                                   // para o potenciomento);   //
delay_ms(12);                                      // Espera 12us;             //
if(input(sensor)==0)                               // Verifica sensor;         //
  {                                                                            //
  while(tempo_baixa!=0)                            // Verifica se a var. tempo_//
                                                   // baixa é diferente de 0;  //
        {                                                                      //
        tempo_baixa--;                             // Decrementa variavel tempo//
                                                   // _baixa;                  //
        delay_ms(12);                              // Espera 12us;             //
        output_low(relay);                         // Desliga rele             //
        }                                                                      //
  while(tempo_alta!=0)                             // Verifica se tempo de alta//
                                                   // é diferente de zero.     //
        {                                                                      //
        tempo_alta--;                              // decrementa var. tempo_   //
                                                   // alta;                    //
        delay_ms(12);                              // Espera 12us;             //
        output_high(relay); // liga rele           // Liga rele                //
        }                                                                      //
  }                                                                            //
}                                                                              //
}                                                                              //
//=============================================================================//
//FIM                                                                          //
//=============================================================================//
