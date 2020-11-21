#include <IRremote.h>
#include <IRremoteInt.h>  //İndirdiğimiz IR kütüphanelerini programımıza dahil ediyoruz

const int RECV_PIN = 2;      // Kızılötesi alıcımızın pinini belirliyoruz.

//L298N Bağlantısı
const int SolMotor1  = 5;  // L298N'in IN1 Girişi
const int SolMotor2  = 6;  // L298N'in IN2 Girişi
const int SolMotorEN  = 9; // L298N'in ENA Girişi
const int SagMotor1  = 7;  // L298N'in IN3 Girişi
const int SagMotor2 = 8; // L298'in IN4 Girişi
const int SagMotorEN = 10; // L298'in ENB Girişi

int spd = 100;  // Motorumuzun hız değişkenini tanımlıyoruz

IRrecv irrecv(RECV_PIN);
decode_results results;

#define CH1 0xFFA25D
#define CH 0xFF629D
#define CH2 0xFFE21D
#define PREV 0xFF22DD
#define NEXT 0xFF02FD
#define PLAYPAUSE 0xFFC23D
#define VOL1 0xFFE01F
#define VOL2 0xFFA857
#define EQ 0xFF906F
#define BUTON0 0xFF6897
#define BUTON100 0xFF9867
#define BUTON200 0xFFB04F
#define BUTON1 0xFF30CF
#define BUTON2 0xFF18E7
#define BUTON3 0xFF7A85
#define BUTON4 0xFF10EF
#define BUTON5 0xFF38C7
#define BUTON6 0xFF5AA5
#define BUTON7 0xFF42BD
#define BUTON8 0xFF4AB5
#define BUTON9 0xFF52AD

void setup()
{
  pinMode(SolMotorEN, OUTPUT);
  pinMode(SagMotorEN, OUTPUT);
  pinMode(SolMotor1, OUTPUT);
  pinMode(SagMotor1, OUTPUT);
  pinMode(SolMotor2, OUTPUT);
  pinMode(SagMotor2, OUTPUT);

  digitalWrite(SolMotorEN, LOW);
  digitalWrite(SagMotorEN, LOW);
  digitalWrite(SolMotor1, LOW);
  digitalWrite(SagMotor1, LOW);
  digitalWrite(SolMotor2, LOW);
  digitalWrite(SagMotor2, LOW);

  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {

    if (irrecv.decode(&results))  //kumandadan sinyal geldiğinde,
    {
      if (results.value == BUTON2) // Buton2'ye bastığımızda robot ileri yönde hareket etsin.
      {
        Serial.println("duz");
        forward();
      }
      if (results.value == BUTON8) // Buton8'e bastığımızda robot geri yönde hareket etsin.
      {
        Serial.println("geri");
         backward();
      }
      if (results.value == BUTON4) // Buton4'e bastığımızda robot sola doğru hareket etsin.
      {
        Serial.println("sol");
        left();        
      }
      if (results.value == BUTON6) // Buton6'ya bastığımızda robot sağa doğru hareket etsin.
      {
        Serial.println("sag");
        right();
      }
      if (results.value == BUTON5) // Buton0'a bastığımızda robot dursun.
      {
        Serial.println("dur");
        stops();
      }
      irrecv.resume();
    }
}

void sol_motor(String dir, int spd) // sol motor kontrolü
{ // yön(dir) ve hız(spd) için değişkenler.
  if ( dir == "ILERI")             // FORWARD komutu ileri hareket için.
  {
    digitalWrite(SolMotor1, HIGH);
    digitalWrite(SolMotor2, LOW);
    analogWrite(SolMotorEN, spd);
  }
  if ( dir == "GERI")           //BACKWARD komutu geriye hareket için.
  {
    digitalWrite(SolMotor1, LOW);
    digitalWrite(SolMotor2, HIGH);
    analogWrite(SolMotorEN, spd);
  }
}

void sag_motor(String dir, int spd)// sağ motor kontrolü
{ // yön(dir) ve hız(spd) için değişkenler.
  if ( dir == "ILERI")             // FORWARD komutu ileri hareket için.
  {
    digitalWrite(SagMotor1, HIGH);
    digitalWrite(SagMotor2, LOW);
    analogWrite(SagMotorEN, spd);
  }

  if ( dir == "GERI")           //BACKWARD komutu geriye hareket için.
  {
    digitalWrite(SagMotor1, LOW);
    digitalWrite(SagMotor2, HIGH);
    analogWrite(SagMotorEN, spd);
  }
}

void left() // Robot ileri gitsin.
{
  sag_motor("ILERI", spd); // Sağ ve sol motorlar ileri yönde 200 hızında
  sol_motor("ILERI", spd);
}
void forward() // Robot sağa dönsün.
{
  sag_motor("GERI", spd); 
  sol_motor("ILERI", spd); 
}

void right() // Robot geri gitsin.
{
  sag_motor("GERI", spd); //Sağ motor 200 hızında geri
  sol_motor("GERI", spd); //Sol motor 200 hızında geri
}

void backward()
{
  sag_motor("ILERI", spd);
  sol_motor("GERI", spd);
}

void stops()
{
  sag_motor("ILERI", 0);
  sol_motor("ILERI", 0);
}
