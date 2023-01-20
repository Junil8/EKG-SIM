#include <MsTimer2.h>
#include <LiquidCrystal.h>
#define button 3

unsigned int EKG_Array[] = {64, 64, 64, 64, 64, 64, 67, 70, 69, 66, 64, 64, 64, 64, 50, 130, 255, 10, 64, 64, 64, 64, 64, 68, 72, 74, 76, 75, 72, 69, 67, 64, 64, 64, 64, 64, 64, 64, 64, 64}; // normalt hjerte
float EKGDisplay = 0; // Sundt hjerte display
int hjerteTypeIndex = 0; // skal der vises sundt hjerte, ventrikelflimmer eller død?
int amplify = 0; // amplify "power"

void readFromAnalog()
{
  // Ud fra vilken case der er trykket på via knap, case 1 sundt hjerte, case 2 ventrikelflimmer, case 3 død
  static unsigned int index = 0; // index pointer til EKG array
  switch (hjerteTypeIndex) {
    case 0:
      EKGDisplay = (float)EKG_Array[index++] / 100.0f * amplify;
      Serial.println(EKGDisplay);
      if (index >= sizeof(EKG_Array) / sizeof(int))index = 0; // EKG_Array[] skulle vist fylde 2 bytes? udregner antal elementer i EKG arrayet.
      break;
    case 1:
      Serial.println(random(0, 128) / 100.0f * amplify);
      break;
    case 2:
      Serial.println(10); // Sætter value til 10 for at gøre det nemmere at se, den rigtige value er 0
      break;
  }
}

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(115200);
  MsTimer2::set(timerAdjust(), readFromAnalog); // 50ms -> Nyquist siger at dette giver en maks på 10HZ
  MsTimer2::start();
}

void loop()
{
  // Gør det muligt at ændre interval via potentiometer
  static int currentInterval = timerAdjust();
  if (abs(currentInterval - timerAdjust()) >= 1) {
    currentInterval = timerAdjust();
    MsTimer2::set(currentInterval, readFromAnalog);
    MsTimer2::start();
  }
  // læser knappen og skifter hvad der skal vises på plotteren
  if (digitalRead(button) == 0) {
    delay(500);
    hjerteTypeIndex++;
    if (hjerteTypeIndex > 2)hjerteTypeIndex = 0;
  }
  // opdatere amplify "kraft"
   amplify = amplifier();
}
