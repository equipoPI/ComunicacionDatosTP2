#include <IRremote.h> //incluimos libreria para el control de las señales de infrarojo en la version 3.3.0

// Definir pines para el LED RGB y llegada del infrarojo
#define PIN_LED_RED 8
#define PIN_LED_GREEN 7
#define PIN_LED_BLUE 6
#define IRpin 2

/*codigo=boton        //esos son los valores de cada boton de un control hecho por nosotros con un aruino,utilizamos teclado matricial 4x4
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
#define CODIGO_BOTON_AON 22   //prender
#define CODIGO_BOTON_AOFF 92  //apagar
#define CODIGO_RED 40         //codigo que identifica el color rojo
#define CODIGO_GREEN 50       //codigo que identifica el color verde
#define CODIGO_BLUE 60        //codigo que identifica el color azul
#define CODIGO_BOTON_1 11     //aumentar nivel del rojo
#define CODIGO_BOTON_4 14     //disminuir el nivel de rojo
#define CODIGO_BOTON_2 12     //aumentar nivel de verde
#define CODIGO_BOTON_5 15     //disminuir nivel de verde 
#define CODIGO_BOTON_3 13     //aumentar nivel de azul
#define CODIGO_BOTON_6 16     //disminuir nivel de azul

// variables de operacion
int state = 0;                     //variable donde se almacena el valor decodificado
int control = 0;                   //variable donde se almacena el valor decodificado
float reset = 0;                 //variable de control de tiempo
bool estado = false;             //variable control de prendido y apagado
int intensidadR = 0;             //valores iniciales de intensidad de los colores
int intensidadG = 0;
int intensidadB = 0;

int registroR = 0;             //variable donde guardaremos los valores enviados desde el emisor
int registroG = 0;             //son netamente de control
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
    control = IrReceiver.decodedIRData.command; //esta sentencia decodifica el tamaño de la señal mandada y la guarda en control


    if (state == CODIGO_BOTON_AON) {
      estado = true;
    }

    if ( state == CODIGO_BOTON_AOFF) {          //si llega el codigo del boton A se imprime 0 en las salidas ya que es la señal de apagado desde el emisor
      analogWrite(PIN_LED_RED, 0);
      analogWrite(PIN_LED_GREEN, 0);
      analogWrite(PIN_LED_BLUE, 0);
      estado = false;
    }

    if (estado == true) {
      if (state == CODIGO_RED) {        //funcion para guardar la señal recibida desde el emisor para prender el controla en el valor guardado
        intensidadR = control;         //es para el color rojo
        analogWrite(PIN_LED_RED, intensidadR);
      }

      if (state == CODIGO_GREEN) {               //se repite lo mismo para el color verde y azul en la linea anterior
        intensidadG = control;
        analogWrite(PIN_LED_GREEN, intensidadG);
      }

      if (state == CODIGO_BLUE) {
        intensidadB = control;
        analogWrite(PIN_LED_BLUE, intensidadB);
      }
    }

    if (state == CODIGO_BOTON_1) {                //condicionales donde dependiendo del valor recibido se llama a una o otra funcion
      aumentarIntensidadColor(PIN_LED_RED);
    }
    if (state == CODIGO_BOTON_4) {
      disminuirIntensidadColor(PIN_LED_RED);
    }
    if (state == CODIGO_BOTON_2) {
      aumentarIntensidadColor(PIN_LED_GREEN);
    }
    if (state == CODIGO_BOTON_5) {
      disminuirIntensidadColor(PIN_LED_GREEN);
    }
    if (state == CODIGO_BOTON_3) {
      aumentarIntensidadColor(PIN_LED_BLUE);
    }
    if (state == CODIGO_BOTON_6) {
      disminuirIntensidadColor(PIN_LED_BLUE);
    }

    Serial.print("Comando: ");
    Serial.print(state);
    Serial.print("   R:");
    Serial.print(registroR);
    Serial.print("  ");
    Serial.print(intensidadR);
    Serial.print("   G:");
    Serial.print(registroG);
    Serial.print("  ");
    Serial.print(intensidadG);
    Serial.print("   B:");
    Serial.print(registroB);
    Serial.print("  ");
    Serial.print(intensidadB);
    Serial.println();
    //imprimios por el puerto seie los valores que queremos controlar*/
    // Reiniciar el receptor para recibir el próximo código

    IrReceiver.resume();
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
