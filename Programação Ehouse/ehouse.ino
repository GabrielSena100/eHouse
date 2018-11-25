
#include <Modbus.h>         // Biblioteca Modbus para utilização do protocolo junto com o meio fisico RS485     
#include <ModbusSerial.h> 
#include <Servo.h>         // Biblioteca para a utilização do servo motor
#include "DHT.h"   // Biblioteca para a utilização do sensor de temperatura e umidade DHT11

//---------------------------------------------- Definição dos Pinos--------------------------------------------
#define Lamp1 3       
#define Lamp2 4
#define Lamp3 5
#define Lamp4 6
#define Lamp5 7
#define Lamp6 8
#define pinServo 9
#define pinCooler 13
#define DHTPIN 11

#define DHTTYPE DHT11
//---------------------------- Atribuição de Objetos dentro das bibliotecas utilizadas -------------------------  
DHT dht(DHTPIN, DHTTYPE); // Objeto da biblioteca DHT11 e setagem do pino utilizado
ModbusSerial mb; // Objeto da biblioteca ModBus Serial
Servo servo1; // Objeto da biblioteca do Servo Motor
//------------------------- Endereçamento dos Registradores utilizados no ScadaBR------------------------------
const int L1 = 0; // Endereço do L1 - L6 responsáveis pelo controle dos LED´s tipo Coil (Binário OUTPUT)
const int L2 = 1;
const int L3 = 2;
const int L4 = 3;
const int L5 = 4;
const int L6 = 5;
const int ServoMOTOR = 6; // Endereço do Servo Motor tipo Status do Coil (Binário OUTPUT)
const int COOLER = 11; // Endereço do Cooler tipo Status do Coil (Binário OUTPUT)
const int temp = 8; // Endereço da temperatura tipo Registrador de Entrada (Analógico INPUT) 
const int umid = 9;// Endereço da umidade tipo Registrador de Entrada (Analógico INPUT) 

void setup() {
  mb.config(&Serial,9600,SERIAL_8N1,2); // Configuração inicial da biblioteca MODBUS Serial, configurando a velocidade de comunicação e o pino de controle
  mb.setSlaveId(1); // Configuração do ESCRAVO
  dht.begin();
//===============================================================| Configuração de Cada Registrador |  ====================================================
 
  mb.addCoil(L1);  //                         | Tipo de Registrador | Utilização     | Acesso | Código da Biblioteca |
  mb.addCoil(L2);  //                         |---------------------|----------------|--------|----------------------|
  mb.addCoil(L3);  //                         |        Coil         | Digital Output |  R/W   |   addCoil(), Coil()  |
  mb.addCoil(L4);  //                         |   Holding Register  | Analog Output  |  R/W   |   addHreg(), Hreg()  |
  mb.addCoil(L5);  //                         |    Input Status     | Digital Input  |  Read  |   addIsts(), Ists()  |
  mb.addCoil(L6);  //                         |    Input Register   | Analog Input   |  Read  |   addIreg(), Ireg()  |
  mb.addCoil(ServoMOTOR);
  mb.addCoil(COOLER);
  mb.addIreg(temp);
  mb.addIreg(umid);
//=========================================================================================================================================================
  servo1.attach(pinServo); // Configuração do pino do servo motor
  pinMode(Lamp1,OUTPUT); // pinos de saída e Entrada
  pinMode(Lamp2,OUTPUT);
  pinMode(Lamp3,OUTPUT);
  pinMode(Lamp4,OUTPUT);
  pinMode(Lamp5,OUTPUT);
  pinMode(Lamp6,OUTPUT);
  pinMode(pinServo,OUTPUT);
  pinMode(pinCooler,OUTPUT);
  
}

void loop() {
  mb.task(); // Início da comunicação serial
  digitalWrite(Lamp1, mb.Coil(L1)); // Atribuindo o valor da variável L1 ao pino Lamp1
  digitalWrite(Lamp2, mb.Coil(L2)); // Atribuindo o valor da variável L2 ao pino Lamp2
  digitalWrite(Lamp3, mb.Coil(L3)); // Atribuindo o valor da variável L3 ao pino Lamp3
  digitalWrite(Lamp4, mb.Coil(L4)); // Atribuindo o valor da variável L4 ao pino Lamp4
  digitalWrite(Lamp5, mb.Coil(L5)); // Atribuindo o valor da variável L5 ao pino Lamp5
  digitalWrite(Lamp6, mb.Coil(L6)); // Atribuindo o valor da variável L6 ao pino Lamp6
  digitalWrite(pinCooler, mb.Coil(COOLER)); // Atribuindo o valor da variável COOLER ao pino que liga o Cooler

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  mb.Ireg(temp,t); // Atribuição da temperatura ao registrador da temperatura
  mb.Ireg(umid,h); // Atribuição da umidade ao registrador da umidade

  if(mb.Coil(ServoMOTOR)==HIGH){ // Condição de abertura do portão
    servo1.write(179);
  }else{
    servo1.write(0);
  }

 
}
