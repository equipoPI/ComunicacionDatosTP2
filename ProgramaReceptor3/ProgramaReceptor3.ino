#include <IRremote.h> //incluimos libreria para el control de las señales de infrarojo en la version 3.3.0

// Definir pines para el LED RGB y llegada del infrarojo
#define PIN_LED_RED 8
#define PIN_LED_GREEN 9
#define PIN_LED_BLUE 10
#define IRpin 2

/*codigo=boton        //esos son los valores de cada boton de un control hecho por nosotros con un aruino,
  11=1
  12=2
  13=3
  14=4
  15=5
  16=6
  17=7
  18=8
  19=9
  10=0
  21=*
  20=#
  22=A
  23=B
  24=C
  25=D
*/

// Definir códigos de los botones del control remoto
#define CODIGO_BOTON_1 22   //prender y apagar
#define CODIGO_BOTON_2 11  //aumentar nivel del rojo
#define CODIGO_BOTON_3 14   //disminuir el nivel de rojo
#define CODIGO_BOTON_4 12  //aumentar nivel de verde
#define CODIGO_BOTON_5 15  //disminuir nivel de verde 
#define CODIGO_BOTON_6 13   //aumentar nivel de azul
#define CODIGO_BOTON_7 16    //disminuir nivel de azul

// variables de operacion
int flag = false;
int control = 0;
float reset = 0;
int state = 0;                     //variable donde se almacena el valor decodificado
bool estado = false;      //variable control de prendido y apagado
int intensidadR = 0;             //valores iniciales de intensidad de los colores
int intensidadG = 0;
int intensidadB = 0;

int registroR = 0;             //variable donde guardaremos los valores guardados en el emisor
int registroG = 0;
int registroB = 0;

void setup() {
  // Inicializar el receptor infrarrojo
  IrReceiver.begin(IRpin); //definimos como entrada de señal infraroja utilizando la sentencia de la libreria

  //iniciamos el puerto serie para control de la modificacion de variables y llegada de datos de señal infraroja
  Serial.begin(9600);

  // Configurar los pines del LED RGB como salidas
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
}

void loop() {
  // Si se ha recibido una señal del control remoto
  if (IrReceiver.decode()) {
    state = IrReceiver.decodedIRData.address; //esta sentencia decodifica la señal recibida y la guarda en la variable state
    control = IrReceiver.decodedIRData.command;
if (state == 40) {
    if (  100 <= control  and control < 390) {
      registroR = control ;
      intensidadR = control - 100;
      analogWrite(PIN_LED_RED, intensidadR);
    }
  }

  if (state == 50) {
    if ( 400 <= control and control < 690) {
      registroG = control;
      intensidadG = control - 400;
      analogWrite(PIN_LED_GREEN, intensidadG);
    }
  }

  if (state == 60) {
    if (  700 <= control and control < 990) {
      registroB = control;
      intensidadB = control - 700;
      analogWrite(PIN_LED_BLUE, intensidadB);
    }
  }

  if (state == CODIGO_BOTON_1) {
    cambiarEstadoLED();
  }
  if (state == CODIGO_BOTON_2) {
    aumentarIntensidadColor(PIN_LED_RED);
  }
  if (state == CODIGO_BOTON_3) {
    disminuirIntensidadColor(PIN_LED_RED);
  }
  if (state == CODIGO_BOTON_4) {
    aumentarIntensidadColor(PIN_LED_GREEN);
  }
  if (state == CODIGO_BOTON_5) {
    disminuirIntensidadColor(PIN_LED_GREEN);
  }
  if (state == CODIGO_BOTON_6) {
    aumentarIntensidadColor(PIN_LED_BLUE);
  }
  if (state == CODIGO_BOTON_7) {
    disminuirIntensidadColor(PIN_LED_BLUE);
  }

  Serial.print("Comando: ");
  Serial.print(state);
  Serial.print("   R:");
  Serial.print(registroR);
  Serial.print(intensidadR);
  Serial.print("   G:");
  Serial.print(registroG);
  Serial.print(intensidadG);
  Serial.print("   B:");
  Serial.print(registroB);
  Serial.print(intensidadB);
  Serial.println();
  flag = false;
    // Reiniciar el receptor para recibir el próximo código
    IrReceiver.resume();
  }

  
  reset=millis();
  //imprimios por el puerto seie los valores que queremos controlar*/
  if(millis()-reset >= 1500){
    Serial.print("reset");
   IrReceiver.resume();}
}
// Función para cambiar el estado del LED (encender/apagar)
void cambiarEstadoLED() {

  if (estado == false and flag == false) {

    estado = true;
    flag = true;
  }

  if (estado == true and flag == false) {
    analogWrite(PIN_LED_RED, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_BLUE, 0);
    estado = false;
    flag = true;
  }
}

// Función para aumentar la intensidad de un color
void aumentarIntensidadColor(int pinLED) {
  if (estado == true) {
    if (pinLED == PIN_LED_RED) {
      intensidadR = constrain(intensidadR + 20, 0, 255); //la sentencia contrain() hace trabajar el valor que queremos entre un limite minimo y maximo
      analogWrite(pinLED, intensidadR);
    }
    if (pinLED == PIN_LED_GREEN) {
      intensidadG = constrain(intensidadG + 20, 0, 255);
      analogWrite(pinLED, intensidadG);
    }
    if (pinLED == PIN_LED_BLUE) {
      intensidadB = constrain(intensidadB + 20, 0, 255);
      analogWrite(pinLED, intensidadB);
    }
  }
}

// Función para disminuir la intensidad de un color
void disminuirIntensidadColor(int pinLED) {
  if (estado == true) {
    if (pinLED == PIN_LED_RED) {
      intensidadR = constrain(intensidadR - 20, 0, 255);
      analogWrite(pinLED, intensidadR);
    }
    if (pinLED == PIN_LED_GREEN) {
      intensidadG = constrain(intensidadG - 20, 0, 255);
      analogWrite(pinLED, intensidadG);
    }
    if (pinLED == PIN_LED_BLUE) {
      intensidadB = constrain(intensidadB - 20, 0, 255);
      analogWrite(pinLED, intensidadB);
    }
  }
}
