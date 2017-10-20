#include <Servo.h>
Servo serIzq;   //8
Servo serDer;   //7
int pos = 0;

int izqA = 10; 
int izqB = 9; 
int derA = 6; 
int derB = 5; 
int vel = 255;            // Velocidad de los motores (0-255)
int estado = 'g';         // inicia detenido

int pecho = 12;            // define el pin 2 como (pecho) para el Ultrasonido
int ptrig = 11;            // define el pin 3 como (ptrig) para el Ultrasonido
int duracion, distancia;  // para Calcular distacia

void setup()  { 
  Serial.begin(9600);    // inicia el puerto serial para comunicacion con el Bluetooth
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
    
  pinMode(pecho, INPUT);   // define el pin 2 como entrada (pecho) 
  pinMode(ptrig,OUTPUT);   // define el pin 3 como salida  (ptrig) 
  pinMode(13,OUTPUT);

  serIzq.attach(8);
  serDer.attach(7);

  serIzq.write(0);
  serDer.write(180);
} 

void loop(){ 
  if(Serial.available()>0){        // lee el bluetooth y almacena en estado
    estado = Serial.read();
  }
  if(estado == 'a'){           // Boton desplazar al Frente
    avanzar();         
  }
  if(estado=='b'){          // Boton IZQ 
    izquierda();
  }
  if(estado=='c'){         // Boton retroceder
    retroceder();
  }
  if(estado=='d'){          // Boton DER
    derecha();   
  } 
  if(estado=='e'){          // servo derecho
    servoDer();
  }
  if(estado=='f'){          // servo izquierdo
    servoIzq();
  }
  if(estado == 'z'){
    parar();
  }
}

void avanzar(){
  analogWrite(izqA, vel);
  analogWrite(izqB, 0);
  analogWrite(derA, vel);
  analogWrite(derB, 0);
  }

void retroceder(){
  analogWrite(izqA, 0);
  analogWrite(izqB, vel);
  analogWrite(derA, 0);
  analogWrite(derB, vel);
  }

void izquierda(){
  analogWrite(izqA, vel);
  analogWrite(izqB, 0);
  analogWrite(derA, 0);
  analogWrite(derB, vel);
  }

void derecha(){
  analogWrite(izqA, 0);
  analogWrite(izqB, vel);
  analogWrite(derA, vel);
  analogWrite(derB, 0);
  }
  
void parar(){
  analogWrite(izqA, 0);
  analogWrite(izqB, 0);
  analogWrite(derA, 0);
  analogWrite(derB, 0);
  }

void servoIzq(){
  for (pos = 180; pos >= 0; pos -= 1){ 
    serDer.write(pos);
    delay(10);
  }
  for (pos = 0; pos <= 180; pos += 1){
    serDer.write(pos);              
    delay(10);                       
  }
}
void servoDer(){
  for (pos = 0; pos <= 180; pos += 1){
    serIzq.write(pos);              
    delay(10);                       
  }
  for (pos = 180; pos >= 0; pos -= 1){ 
    serIzq.write(pos);
    delay(10);
  }
}
