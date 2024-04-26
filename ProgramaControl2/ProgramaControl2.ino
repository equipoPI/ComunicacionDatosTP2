#include <IRremote.h> //incluimos libreria para el control de las señales de infrarojo en la version 3.3.0

// Definir pines para el LED RGB y llegada del infrarojo
#define PIN_LED_RED 4
#define PIN_LED_GREEN 3
#define PIN_LED_BLUE 2
#define IRpin 9

/*codigo=boton        //esos son los valores de cada boton de un control de un kit de arduino, en el caso de que se utilice otro control se debe de cargar este
  69=1                 //programa y abrir el monitor serie. Con forme presionemos los distintos botones del control veremos el valor asociaddo al mismo
  70=2
  71=3
  68=4
  64=5
  67=6
  7=7
  21=8
  9=9
  25=0
  22=*
  13=#
  28=ok
  90=derecha
  8=izquierda
  24=arriba
  82=abajo
*/

// Definir códigos de los botones del control remoto
#define CODIGO_BOTON_1 69   //prender y apagar
#define CODIGO_BOTON_2 70   //aumentar nivel del rojo
#define CODIGO_BOTON_3 71   //disminuir el nivel de rojo
#define CODIGO_BOTON_4 68   //aumentar nivel de verde
#define CODIGO_BOTON_5 64   //disminuir nivel de verde 
#define CODIGO_BOTON_6 67   //aumentar nivel de azul
#define CODIGO_BOTON_7 7    //disminuir nivel de azul

// variables de operacion
int state = 0;                     //variable donde se almacena el valor decodificado
volatile bool estado = false;      //variable control de prendido y apagado
int intensidadR = 255;             //valores iniciales de intensidad de los colores
int intensidadG = 255;
int intensidadB = 255;

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

    state = IrReceiver.decodedIRData.command; //esta sentencia decodifica la señal recibida y la guarda en la variable state

    // Mapear acciones a botones, define que hacer en cada caso dependiendo del valor que decodificamos de la señal
    switch (state) {
      case CODIGO_BOTON_1:
        // Encender y apagar el LED
        cambiarEstadoLED();
        break;
      case CODIGO_BOTON_2:
        // Aumentar la intensidad del color rojo
        aumentarIntensidadColor(PIN_LED_RED);
        break;
      case CODIGO_BOTON_3:
        // Disminuir la intensidad del color rojo
        disminuirIntensidadColor(PIN_LED_RED);
        break;
      case CODIGO_BOTON_4:
        // Aumentar la intensidad del color verde
        aumentarIntensidadColor(PIN_LED_GREEN);
        break;
      case CODIGO_BOTON_5:
        // Disminuir la intensidad del color verde
        disminuirIntensidadColor(PIN_LED_GREEN);
        break;
      case CODIGO_BOTON_6:
        // Aumentar la intensidad del color azul
        aumentarIntensidadColor(PIN_LED_BLUE);
        break;
      case CODIGO_BOTON_7:
        // Disminuir la intensidad del color azul
        disminuirIntensidadColor(PIN_LED_BLUE);
        break;
    }

    //imprimios por el puerto seie los valores que queremos controlar
    Serial.print("Comando: ");
    Serial.print(state);
    Serial.print("   R:");
    Serial.print(intensidadR);
    Serial.print("   G:");
    Serial.print(intensidadG);
    Serial.print("   B:");
    Serial.print(intensidadB);
    Serial.println();
    
    delay(500);
    
    // Reiniciar el receptor para recibir el próximo código
    IrReceiver.resume();
  }
}

// Función para cambiar el estado del LED (encender/apagar)
void cambiarEstadoLED() {

  estado = !estado;
  if (estado == true) {
    analogWrite(PIN_LED_RED, intensidadR);
    analogWrite(PIN_LED_GREEN, intensidadG);
    analogWrite(PIN_LED_BLUE, intensidadB);
  }

  if (estado == false) {
    analogWrite(PIN_LED_RED, 0);
    analogWrite(PIN_LED_GREEN, 0);
    analogWrite(PIN_LED_BLUE, 0);
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
