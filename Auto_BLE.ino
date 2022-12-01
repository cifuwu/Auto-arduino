#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales
                             // para comunicacion serie

SoftwareSerial miBT(10, 11);  // pin 10 como RX, pin 11 como TX

int dato = 0;
// FRENO: 83
// ADELANTE: 70
// ATRAS: 66
// IZQUIERDA: 76
// DERECHA: 82
// ADELANTE IZQUIERDA: 71
// ADELANTE DERECHA:  73
// ATRAS IZQUIERDA: 72
// ATRAS DERECHA: 74

int IN1 = 2;
int IN2 = 3;
int ENA = 5;
int IN3 = 6;
int IN4 = 7;
int ENB = 8;

int VELOCIDAD = 200;  // variable para almacenar valor de velocidad


void setup() {
  Serial.begin(9600);       // comunicacion de monitor serial a 9600 bps
  Serial.println("Listo");  // escribe Listo en el monitor
  miBT.begin(9600);         // comunicacion serie entre Arduino y el modulo a 38400 bps

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {

  if (miBT.available()){  // si hay informacion disponible desde modulo
    dato = miBT.read();
    if(dato != 83){
      Serial.println(dato); 	// lee Bluetooth y envia a monitor serial de Arduino  
    }}
    
  // FRENO
  if (dato == 83) {
    Freno(1);
    Freno(2);
  }
  // ADELANTE
  else if (dato == 70) {
    Motor(1, 0, VELOCIDAD);
    Motor(2, 0, VELOCIDAD);
  }
  // ATRAS
  else if (dato == 66) {
    Motor(1, 1, VELOCIDAD);
    Motor(2, 1, VELOCIDAD);
  }
  // IZQUIERDA
  else if (dato == 76) {
    Motor(1, 1, VELOCIDAD);
    Motor(2, 0, VELOCIDAD);
  }
  // DERECHA
  else if (dato == 82) {
    Motor(1, 0, VELOCIDAD);
    Motor(2, 1, VELOCIDAD);
  }
  // PRENDE LUCES DELANTERAS
  else if (dato == 87){
    Serial.println("PRENDE LUCES DELANTERAS");
  }
  // APAGA LUCES DELANTERAS
  else if (dato == 119){
    Serial.println("APAGA LUCES DELANTERAS");  
  }
  else {
    Freno(1);
    Freno(2);
  }
}

// VELOCIDAD MAX : 255
void Motor(int Motor, int Direccion, int Velocidad) {

  if (Motor == 1) {
    if (Direccion == 0) {
      analogWrite(ENA, Velocidad);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    } else if (Direccion == 1) {
      analogWrite(ENA, Velocidad);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
  } else if (Motor == 2) {
    if (Direccion == 0) {
      analogWrite(ENB, Velocidad);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (Direccion == 1) {
      analogWrite(ENB, Velocidad);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
  }
}

void Freno(int Motor) {

  if (Motor == 1) {
    digitalWrite(ENA, LOW);
  } else if (Motor == 2) {
    digitalWrite(ENB, LOW);
  }
}