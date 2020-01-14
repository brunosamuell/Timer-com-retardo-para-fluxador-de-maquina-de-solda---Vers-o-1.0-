//============================================================================//
//                  fluxador (timer) - Versão 1.0                             //
// Autor: Eng. Bruno Samuel Luiz de Oliveira                                  //                                                
// Compilador: PCWHD v5.080      Início: 10/01/2020    TÉRMINO: 14/01/2020    //
// Status: Finalizado                                                         //
//============================================================================//
//Descrição:Este projeto tem por objetivo o desenvolvimento de um controlador //
//para o controle do fluxo de solda de uma maquina de solda  por onda, devido // 
//a  antiga  placa estar  inoperante e por não  haver placa de  reposição  na //
//empresa facricante, sendo assim foi se  necessario o devenvolvimento de tal //
//projeto, onde atravez  deste se pode controlar o retardo p/  acionamento do //
//rele (Comando para acionamento  da onda de solda e do fluxador) conectado a //
//porta  B4 do PIC 16F1827 e os potecimestros de  controle estão conectados a //
//entrada A0 e  A1 respectivamente, onde atravez desse se tem o  controle  de //
//tempo aciona e por fim se tem o sensor optico conectado a  porta B0.        //
//============================================================================//
#include <16F1827.h>  //define uC;
#device ADC=10        //define numero de bits do conversor A/D;
#fuses INTRC_IO,NOWDT,NOPUT,NOPROTECT,NOCPD,NOMCLR// Define fusíveis
#use delay(internal=4000000)
#use FIXED_IO( B_outputs=PIN_B4 )
#define relay PIN_B4
#define sensor PIN_B0
int32 tempo_alta;
int32 tempo_baixa;
void main()
{
setup_adc_ports(ALL_ANALOG | VSS_VREF); 
setup_adc(ADC_CLOCK_DIV_2);
delay_ms(1000);
set_tris_B(0x41);
while(TRUE)
{
output_low(relay);
set_adc_channel(0);    //le canal 1
delay_us(12);
tempo_alta= read_adc();
if(tempo_alta<=80){tempo_alta=0;}
delay_ms(12);
set_adc_channel(1);    //le canal 2
delay_us(12);
tempo_baixa=read_adc();
if(tempo_baixa<=80){tempo_baixa=0;}
delay_ms(12);    
if(input(sensor)==0)
  {
  while(tempo_baixa!=0)
        {
        tempo_baixa--;
        delay_ms(12);
        output_low(relay);
        }
  while(tempo_alta!=0)
        {
        tempo_alta--;
        delay_ms(12);
        output_high(relay);
        }  
  }  
} 
}

