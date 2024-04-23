#include <IRremote.h>  //icluimos la libreria para trabajar con el control, es la version 3.3.0

#define IRpin 9        //pin de de entrada de datos del receptor infrarojo
int state = 0;        //bariable utilizada para guardar el valor decodificado de ña señal

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


void setup() {
  Serial.begin(9600);      //seteamos la velocidad del purto a 9600 baudios
  IrReceiver.begin(IRpin); //definimos como entrada de señal infraroja utilizando la sentencia de la libreria
}

void loop() {
  if (IrReceiver.decode()) { //cuando el decodificado es 0 entra en un bucle

    Serial.print("Tipo de protocolo: ");
    Serial.println(IrReceiver.decodedIRData.protocol); //obtenemos el tipo de protocolo que utiliza el control, nos brinda un numero ya que no esta incorparado
    //el registro de los valores dentro de estas libreria pero por ejemplo el valor para NEC es 7 mientras que para
    //los Samsumg es 16

    state = IrReceiver.decodedIRData.command; //esta sentencia decodifica la señal recibida y la guarda en la variable state
    Serial.print("Comando: ");
    Serial.println(state);                   //imprime el valor obtenido en el puero serie para seber el valor asociado a ese boton

    delay(1000);
    IrReceiver.resume();                     //limpia y deja en espera las centencias de la libreria utilizadas para la decodificacion
  }
}
