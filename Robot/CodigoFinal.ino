#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  //

//Pines de los Motores
int IN1 = 7;      // IN1 de L298N a pin digital 2
int IN2 = 8;      // IN2 de L298N a pin digital 3
int ENA = 9;      // ENA de L298N a pin digital 5
int IN3 =13;
int IN4 =12;
int ENB=11;

//Pines para sensores 
  //Centro 
const int Trigger_centro = 4; 
const int Echo_centro = 5; 

//Izquierda 
const int Trigger_izq = 2; 
const int Echo_izq = 3;

//Derecha 
const int Trigger_der = 6; 
const int Echo_der = 10; 

//Pines infrarrojos
const int sensorPin_izq=A2; 
const int sensorPin_der = A3; 


void setup(){
  Serial.begin(9600);
  //Inicializacion Motores
  pinMode(IN1, OUTPUT);   // pin 2 como salida
  pinMode(IN2, OUTPUT);   // pin 3 como salida  
  pinMode(ENA,OUTPUT);
  pinMode(IN3, OUTPUT);   // pin 2 como salida
  pinMode(IN4, OUTPUT);   // pin 3 como salida  
  pinMode(ENB,OUTPUT);
   // pin 5 como salida

  //Inicializacion de la pantalla LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("Hola Mundo");
  lcd.clear();

  //Inicializacion Sensores
  pinMode(Trigger_centro, OUTPUT); //pin como salida
  pinMode(Echo_centro, INPUT);  //pin como entrada
  digitalWrite(Trigger_centro, LOW);//Inicializamos el pin con 0

  pinMode(Trigger_izq, OUTPUT); //pin como salida
  pinMode(Echo_izq, INPUT);  //pin como entrada
  digitalWrite(Trigger_izq, LOW);//Inicializamos el pin con 0

  pinMode(Trigger_der, OUTPUT); //pin como salida
  pinMode(Echo_der, INPUT);  //pin como entrada
  digitalWrite(Trigger_der, LOW);//Inicializamos el pin con 0

  //Inicializamos infrarrojos 
  pinMode(sensorPin_izq , INPUT);  //definir pin como entrada
  pinMode(sensorPin_der , INPUT);  //definir pin como entrada

  delay(1500);
  
}

void loop(){
  bool accion = false; 
    int valor_ultrasonidos = 0;
    int value_izq = 0;
  int value_der = 0; 
  value_izq = digitalRead(sensorPin_izq );  //lectura digital de pin
  value_der = digitalRead(sensorPin_der ); // lectura digital del p
    
    //Motor avanza 
    motorAvanza();
    
    lcd.clear();
  if (value_izq == 0 && !accion) {
      Serial.println("Detectado obstaculo izq");
      lcd.print("Linea izq");
      motorGiraDer();
      accion = true;
      delay(1000);
  }
  lcd.clear();
  if (value_der == 0 && !accion) {
      Serial.println("Detectado obstaculo der");
      lcd.print("Linea der");
      motorGiraIzq();
      accion = true; 
      delay(1000);

  }
  lcd.clear();
  lcd.setCursor(0,0);

  valor_ultrasonidos = sensores();
    if(valor_ultrasonidos == 0){
        
        lcd.print("ataca delan");
        motorAvanza();
         delay(500);
    }
     if(valor_ultrasonidos == 2){
         lcd.print("ataca der");
        motorGiraDer();
         delay(500);
    }
     if(valor_ultrasonidos == 1){
         lcd.print("ataca izq");
        motorGiraIzq();
         delay(500);
    }
    
   
}

void motorAvanza(){

  
  //Motor Izquierdo
  digitalWrite(IN1, LOW);        // IN1 en 1
  digitalWrite(IN2, HIGH);


  analogWrite(ENA, 255);
         // el valor de velocidad y aplica a ENA
  
  digitalWrite(IN3, LOW);        // IN1 en 1
  digitalWrite(IN4, HIGH); // IN2 en 0
  analogWrite(ENB, 255); 
}

void motorGiraIzq(){

  
  digitalWrite(IN1, HIGH);        // IN1 en 1
  digitalWrite(IN2, LOW);


  analogWrite(ENA, 190);
         // el valor de velocidad y aplica a ENA
  
  digitalWrite(IN3, LOW);        // IN1 en 1
  digitalWrite(IN4, LOW); // IN2 en 0
  analogWrite(ENB, 190); 
}

void motorGiraDer(){

  digitalWrite(IN1, LOW);        // IN1 en 1
  digitalWrite(IN2, LOW);


  analogWrite(ENA, 190);
         // el valor de velocidad y aplica a ENA
  
  digitalWrite(IN3, HIGH);        // IN1 en 1
  digitalWrite(IN4, LOW); // IN2 en 0
  analogWrite(ENB, 190); 
}

int  sensores(){
long t_centro, t_izq, t_der, t_min1, t_min2; //timepo que demora en llegar el eco
  long d; //distancia en centimetros
  
  int centro = 0, izquierda = 1, derecha =2, devolver = -1; 

  //Distancia centro
  digitalWrite(Trigger_centro, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_centro, LOW);
  
  t_centro = pulseIn(Echo_centro, HIGH); //obtenemos el ancho del pulso

  //Distancia izq
  digitalWrite(Trigger_izq, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_izq, LOW);
  
  t_izq = pulseIn(Echo_izq, HIGH); //obtenemos el ancho del pulso

  //Distancia der
  digitalWrite(Trigger_der, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger_der, LOW);
  
  t_der = pulseIn(Echo_der, HIGH); //obtenemos el ancho del pulso

  t_min1 = min(t_centro, t_izq); 
  t_min2 = min(t_min1, t_der);

  if(t_min2 == t_centro){
    devolver = centro;
    Serial.println("Centro");
  }
  if(t_min2 == t_der){
    devolver = derecha;
    Serial.println("Derecha");
  }
  if(t_min2 == t_izq){
    devolver = izquierda;
    Serial.println("Izquierda");
  }


  d = t_min2/59;             //escalamos el tiempo a una distancia en cm
  if(d < 40){
      return devolver;
  }
  else{
      devolver = -1;
    return devolver;
  }
 /* Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(100);       */   //Hacemos una pausa de 100ms*/
}