#include <ThreeWire.h>
#include <RtcDS1302.h>

//Objects
ThreeWire myWire(4,5,2); //IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Rtc.Begin();
//  RtcDateTime initialTime = RtcDateTime(__DATE__,"13:30:00");
//  Rtc.SetDateTime(initalTime);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  RtcDateTime now = Rtc.GetDateTime();
  Serial.print("Time: ");
  Serial.print(now.Hour());
  Serial.print(":");
  Serial.print(now.Minute());
  Serial.print(":");
  Serial.print(now.Second());
  Serial.println();
  delay(2000);
}
