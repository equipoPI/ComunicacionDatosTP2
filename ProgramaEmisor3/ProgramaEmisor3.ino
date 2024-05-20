#include <IRremote.h>
IRsend irsend;

int intensidadR = 255;  //variable donde se manejan las intensidades de los colores
int intensidadG = 255;
int intensidadB = 255;

int R = 255;
int G = 255;
int B = 255;

int registroR = 255;    //variable donde se va a guardar la intensidad del led para prenderlo
int registroG = 255;    //con la configuracion guardada
int registroB = 255;

byte pinesColumnas[] = {8, 9, 10, 11};
byte pinesFilas[] = {7, 6, 5, 4};
const byte numeroFilas = 4;
const byte numeroColumnas = 4;
int teclas[4][4] = {{1, 2, 3, 12},
  {4, 5, 6, 13},
  {7, 8, 9, 14},
  {11, 0, 10, 15}
};
int valor = 0;
byte flag = false;

float antirebote = 0; //variable control anti rebote

void teclado() {
  if ( (millis() - antirebote) > 300) {
    for (int nF = 0; nF < numeroFilas; nF++) {
      digitalWrite(pinesFilas[nF], LOW);
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

void teclado_config() {
  for (int nF = 0; nF < numeroFilas; nF++) {
    pinMode(pinesFilas[nF], OUTPUT);
    digitalWrite(pinesFilas[nF], HIGH);
  }

  for (int nC = 0; nC < numeroColumnas; nC++) {
    pinMode(pinesColumnas[nC], INPUT_PULLUP);
  }
}

void envio() { //el envio con LG permite un envio mas largo, con NEC podemos hasta 255, podemos mandar numeros en LG sin pensar mucho
  //o podemos hacer que que un numero empiece a guardar los valores de cada color
  if (valor == 13) {
    if (flag == true) {
      irsend.sendLG(0xA, 32, 1);
      registroR = intensidadR;
      registroG = intensidadG;
      registroB = intensidadB;
    }
  }

  if (valor == 1) {
    if (flag == true) {
      irsend.sendLG(0xB, 32, 1);
      intensidadR = constrain(intensidadR + 20, 0, 255);
    }
  }

  if (valor == 2) {
    if (flag == true) {
      irsend.sendLG(0xC, 32, 1);
      intensidadG = constrain(intensidadG + 20, 0, 255);
    }
  }

  if (valor == 3) {
    if (flag == true) {
      irsend.sendLG(0xD, 32, 1);
      intensidadB = constrain(intensidadB + 20, 0, 255);
    }
  }

  if (valor == 4) {
    if (flag == true) {
      irsend.sendLG(0xE, 32, 2);
      intensidadR = constrain(intensidadR - 20, 0, 255);
    }
  }

  if (valor == 5) {
    if (flag == true) {
      irsend.sendLG(0xF, 32, 1);
      intensidadG = constrain(intensidadG - 20, 0, 255);
    }
  }

  if (valor == 6) {
    if (flag == true) {
      irsend.sendLG(0x10, 32, 1);
      intensidadB = constrain(intensidadB - 20, 0, 255);
    }
  }

  if (valor == 7) {
    if (flag == true) {
      irsend.sendLG(0x11, 32, 1);
    }
  }

  if (valor == 8) {
    if (flag == true) {
      irsend.sendLG(0x12, 32, 1);
    }
  }

  if (valor == 9) {
    if (flag == true) {
      irsend.sendLG(0x13, 32, 1);
    }
  }

  if (valor == 10) {
    if (flag == true) {
      irsend.sendLG(0x14, 32, 1);
    }
  }

  if (valor == 11) {
    if (flag == true) {
      irsend.sendLG(0x15, 32, 1);
    }
  }

  if (valor == 12) {
    if (flag == false) {
      irsend.sendLG(0x16, 32, 1);
    
      R = registroR + 100;
      irsend.sendLG(0x28, R, 1);
  
      G = registroG + 400;
      irsend.sendLG(0x32, G, 1);
  ;
      B = registroB + 700;
      irsend.sendLG(0x3C, B, 1);
      flag = true;
    }
    else {
      irsend.sendLG(0x16, 32, 1);
      flag = false;
    }
  }

  if (valor == 13) {
    if (flag == true) {
      irsend.sendLG(0x17, 32, 1);
    }
  }

  if (valor == 14) {
    if (flag == true) {
      irsend.sendLG(0x18, 32, 1);
    }
  }

  if (valor == 15) {
    if (flag == true) {
      irsend.sendLG(0x19, 32, 1);
    }
  }

  valor = 80;
}

void setup() {
  teclado_config();

  irsend.begin(2);
  /*
    Serial.begin(9600);
    Serial.println("Teclado 4x4");
    Serial.println();
  */
}

void loop() {
  teclado();
  envio();
 // Serial.println(valor);
}
