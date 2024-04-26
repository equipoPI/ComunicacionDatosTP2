byte pinesColumnas[] = {14,15,16,17}; 
byte pinesFilas[] = {7,6,5,4};
const byte numeroFilas = 4;
const byte numeroColumnas = 4;
char teclas[4][4] = {{'1','2','3','A'}, 
                     {'4','5','6','B'}, 
                     {'7','8','9','C'}, 
                     {'*','0','%','D'}};
void setup(){
  for (int nF = 0; nF < numeroFilas; nF++) {
     pinMode(pinesFilas[nF], OUTPUT);
     digitalWrite(pinesFilas[nF], HIGH);
  }

  for (int nC = 0; nC < numeroColumnas; nC++) {
     pinMode(pinesColumnas[nC], INPUT_PULLUP);
  } 
   
  Serial.begin(9600);
  Serial.println("Teclado 4x4");
  Serial.println();
}
 
void loop(){
    for (int nF = 0; nF < numeroFilas; nF++){
      digitalWrite(pinesFilas[nF], LOW);
      for (int nC = 0; nC < numeroColumnas; nC++) {
        if (digitalRead(pinesColumnas[nC]) == LOW){
          Serial.print("Tecla: ");
          Serial.println(teclas[nF][nC]);
          while(digitalRead(pinesColumnas[nC]) == LOW){}
        }
      }
      digitalWrite(pinesFilas[nF], HIGH);
    }
   delay(10);
}
