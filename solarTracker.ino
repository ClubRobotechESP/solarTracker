//#include <Servo.h> 
 
//Servo myservo; 
int pos = 0;   // initial position
int sens1 = A0; // LRD 1 pin
int sens2 = A1; //LDR 2 pin
int tolerance = 5;
int positionMax=3;
int posRetour = 10;

int periode=20000;// période entre chaque début d'impulsion en microsecondes

int pinServo=9; // variable pour le pin connecté à la commande du servo
int angle =0;

void setup() {
  Serial.begin(9600);
  pinMode(pinServo,OUTPUT);// on prépare le pin en mode OUTPUT
  digitalWrite(pinServo,LOW); // on l'initialise à l'état bas
  Serial.begin(9600);
  //myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  //myservo.write(pos);
  delay(2000); // a 2 seconds delay while we position the solar panel
}  
 
void loop() 
{ 
  int val1 = analogRead(sens1); // read the value of sensor 1
  int val2 = analogRead(sens2); // read the value of sensor 2
  Serial.print(val1);
  Serial.print(" ");
  Serial.println(val2);
  if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
   
  } else {    
    if(val1 > val2)
    {
      //if(pos < positionMax)
        avancerParPas(10);
//      else{
//        Serial.print("valeur maximale avancee atteinte");
//      }
    }
    if(val1 < val2) 
    {
      //if(posRetour > positionMax)
        reculerParPas(10);
//       else{
//        Serial.print("valeur maximale reculee atteinte");
//      }
     // pos = ++pos;
    }
  }
 
  

  delay(1000);
}

void setAngle(int a){

  int duree=map(a,0,180,1000,2000);// on transforme l'angle en microsecondes et on stocke dans la variable duree
  Serial.println(duree);
  delay(100);
  digitalWrite(pinServo,HIGH);
  delayMicroseconds(duree);
  digitalWrite(pinServo,LOW);

}

void avancerParPas(int pas){
  while(angle < 90){
    setAngle(angle);
    angle+=pas;
  }
  angle=0;
  pos++;
  posRetour++;
  //
}

void reculerParPas(int pas){
  angle=90;
  while(angle < 180){
    setAngle(angle);
    angle+=pas;
  }
  angle =0;
  posRetour = posRetour == 0 ? 0 : posRetour--;
  pos = pos == 0 ? 0 : pos--;
}
