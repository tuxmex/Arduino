/**
 * Autor: TCHAR
 * Fecha: 13042022
 * Descripción: 
 */

//Bibliotecas
//Constantes
const int BOTON_1 = 14;
const int LED_1 = 15;

//Variables
int dato1;

//Definicion de objetos


//Condiciones iniciales
void setup() {
  pinMode(BOTON_1, INPUT_PULLUP); //Configurar el pin donde se conecta el boton1
  pinMode(LED_1, OUTPUT); //Configurar el pin donde se conecta el led como
  digitalWrite(LED_1, LOW); //0, false, LOW, 1, TRUE, HIGH
}//Fin de void setup


//Cuerpo del programa
void loop() {
  dato1=!digitalRead(BOTON_1); //Leer el boton1
  digitalWrite(LED_1, dato1); //Escribir en el led lo que trae dato1
  

 
  
}//Fin de void loop
