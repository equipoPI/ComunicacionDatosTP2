#include <IRremote.h>
IRsend irsend;

int intensidadR = 255;  //variable donde se manejan las intensidades de los colores
int intensidadG = 255;
int intensidadB = 255;

int registroR = 255;    //variable donde se va a guardar la intensidad del led para prenderlo
int registroG = 255;    //con la configuracion guardada
int registroB = 255;

byte pinesColumnas[] = {8, 9, 10, 11}; //definimos  pines donde estaran las columnas del teclado
byte pinesFilas[] = {7, 6, 5, 4};      //definimos donde estaran las filas del teclado
const byte numeroFilas = 4;            //definimos la cantidad de dilas y columnas del teclado
const byte numeroColumnas = 4;
int teclas[4][4] = {{1, 2, 3, 12},     //definimos los valores de las teclas con una matriz
  {4, 5, 6, 13},
  {7, 8, 9, 14},
  {11, 0, 10, 15}
};
int valor = 0;                         //variable que almacenara el numero de la tecla presionada
float antirebote = 0;                  //variable control anti rebote de teclado

byte flag = false;                     //bandera que permitira el envio o no de datos en funcion si precionamos prender(flag de bajo a alto) o apagar (flag de alto a bajo)

void teclado() {
  if ( (millis() - antirebote) > 500) {             //funcion de anti rebote
    for (int nF = 0; nF < numeroFilas; nF++) {      //con sentencias for mapeamos que entradas y salidas del teclado se combinan para obtener que tecla se
      digitalWrite(pinesFilas[nF], LOW);            //esta presionando
      for (int nC = 0; nC < numeroColumnas; nC++) {
        if (digitalRead(pinesColumnas[nC]) == LOW) {
          valor = teclas[nF][nC];
          antirebote = millis();
          Serial.print("Tecla: ");
          Serial.println(teclas[nF][nC]);
        }
      }
      digitalWrite(pinesFilas[nF], HIGH);
    }
  }
}

void teclado_config() {                          //funcion que utilizan sentencias for para configurar los pines que estan asociados al teclado
  for (int nF = 0; nF < numeroFilas; nF++) {
    pinMode(pinesFilas[nF], OUTPUT);
    digitalWrite(pinesFilas[nF], HIGH);
  }

  for (int nC = 0; nC < numeroColumnas; nC++) {
    pinMode(pinesColumnas[nC], INPUT_PULLUP);
  }
}

void envio() {  //enviamos los valores en formato LG pero podriamos enviarlo con formato SONY o NEC
  if (valor == 13) {                 //si el valor obtenido con la funcion teclado() es 13 y la la falg indica que habiamos enviado prender anteriormente se guardan los valores de intensidad
    if (flag == true) {
      irsend.sendLG(0x17, 16, 1);    //enviamos señal 
      registroR = intensidadR;       //guardamos valores intensidad en sus respectivos registros
      registroG = intensidadG;
      registroB = intensidadB;
    }
  }

  if (valor == 1) {
    if (flag == true) {
      irsend.sendLG(0xB, 16, 1);
      intensidadR = constrain(intensidadR + 20, 0, 255);
    }
  }

  if (valor == 2) {
    if (flag == true) {
      irsend.sendLG(0xC, 16, 1);
      intensidadG = constrain(intensidadG + 20, 0, 255);
    }
  }

  if (valor == 3) {
    if (flag == true) {
      irsend.sendLG(0xD, 16, 1);
      intensidadB = constrain(intensidadB + 20, 0, 255);
    }
  }

  if (valor == 4) {
    if (flag == true) {
      irsend.sendLG(0xE, 16, 2);
      intensidadR = constrain(intensidadR - 20, 0, 255);
    }
  }

  if (valor == 5) {
    if (flag == true) {
      irsend.sendLG(0xF, 16, 1);
      intensidadG = constrain(intensidadG - 20, 0, 255);
    }
  }

  if (valor == 6) {
    if (flag == true) {
      irsend.sendLG(0x10, 16, 1);
      intensidadB = constrain(intensidadB - 20, 0, 255);
    }
  }

  if (valor == 7) {
    if (flag == true) {
      irsend.sendLG(0x11, 16, 1);
    }
  }

  if (valor == 8) {
    if (flag == true) {
      irsend.sendLG(0x12, 16, 1);
    }
  }

  if (valor == 9) {
    if (flag == true) {
      irsend.sendLG(0x13, 16, 1);
    }
  }

  if (valor == 10) {
    if (flag == true) {
      irsend.sendLG(0x14, 16, 1);
    }
  }

  if (valor == 11) {
    if (flag == true) {
      irsend.sendLG(0x15, 16, 1);
    }
  }

  if (valor == 12) {
    if (flag == false) {
      irsend.sendLG(0x16, 16, 1);

   
      irsend.sendLG(0x28, registroR, 1);

     
      irsend.sendLG(0x32, registroG, 1);

      
      irsend.sendLG(0x3C, registroB, 1);
      flag = true;
    }
    else {
      irsend.sendLG(0x5C, 16, 1);
      flag = false;
    }
  }

  if (valor == 14) {
    if (flag == true) {
      irsend.sendLG(0x18, 16, 1);
    }
  }

  if (valor == 15) {
    if (flag == true) {
      irsend.sendLG(0x19, 16, 1);
    }
  }

  valor = 80;
}

void setup() {
  teclado_config();  //funcion configuracion del teclado

  irsend.begin(2);   //funcion de la libreria IRremote para defini el pin donde se conecta el emisor
  /*
    Serial.begin(9600);
    Serial.println("Teclado 4x4");
    Serial.println();
  */
}

void loop() {
  teclado();     //funcion llamado a buscar que tecla se apreto
  envio();       //funcion donde vamos a enviar los datos
  // Serial.println(valor);
}
