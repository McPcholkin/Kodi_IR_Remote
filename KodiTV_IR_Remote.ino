#include <IRremote.h> // include IR libary

int testLedPin = 10;   // Led for testing
int buttonPin = 12;    // button for testing
int irRecivePin = 11;  // ir reciever 
int irLedPin = 3;      // ir led for control TV
boolean buttonStatus = 0; 
boolean tvPowerState = 0; //control power state of TV
int sleepTimerState = 0;  // Default Sleep Timer is off

IRrecv irrecv(irRecivePin); // set reciever to pin
IRsend irsend;

decode_results results;     // decode recieved resolts


void setup() {
  Serial.begin(9600);       // print output for debug
  irrecv.enableIRIn();      // Start the receiver
  pinMode(testLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
}

void loop() {

//------------------------------------------------------------------------------------
  if(irrecv.decode(&results)) //this checks to see if a code has been received
  {
     
      if (results.value == 0xFF629D) // Up - Up Kodi
        {
         Serial.println("Up");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFFA857) // Down - Down Kodi
        {
         Serial.println("Down");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);

        }

      if (results.value == 0xFF22DD) // Left - Left Kodi
        {
         Serial.println("Left");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFFC23D) // Right - Right Kodi
        {
         Serial.println("Right");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }



      if (results.value == 0xFF02FD) // OK - OK Kodi
        {
         Serial.println("OK");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);;
        }


      if (results.value == 0xFF6897)  // 1 - Power switch
        {
         Serial.println("POWER");     // Debug
         if(tvPowerState == 0)        // check if TV OFF
          {
            irsend.sendRC5(0x80C, 12);  // ON Signal
            delay(300);
            irrecv.enableIRIn();        // Enable IR Reciving
            tvPowerState = 1;           // Chandge TV status to ON
          }
        else 
          {
            irsend.sendRC5(0XC, 12);    // OFF Signal
            delay(300);
            irrecv.enableIRIn();        // Enable IR Reciving
            tvPowerState = 0;           // Chandge TV status to OFF
          }
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF9867) // 2 - back Kodi
        {
         Serial.println("2");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }

      
      if (results.value == 0xFFB04F) // 3 - Vol UP Kodi
        {
         Serial.println("3");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF30CF) // 4 - sleep timer
        {
         Serial.println("4");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF18E7) // 5
        {
         Serial.println("5");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF7A85) // 6 - Vol Down Kodi
        {
         Serial.println("6");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF10EF) // 7
        {
         Serial.println("7");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);;
        }


      if (results.value == 0xFF38C7) // 8
        {
         Serial.println("8");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);;
        }


      if (results.value == 0xFF5AA5) // 9
        {
         Serial.println("9");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF4AB5) // 0
        {
         Serial.println("0");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF42BD) // *
        {
         Serial.println("*");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


      if (results.value == 0xFF52AD) // #
        {
         Serial.println("#");
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }
        
  irrecv.resume(); //receive the next value  
  }
//------------------------------------------------------------------------------


      buttonStatus = digitalRead(buttonPin); // Physical button to set sleep timer
      if(buttonStatus == HIGH)
        {
         Serial.println("POWER");     // Debug
         if(tvPowerState == 0)        // check if TV OFF
          {
            irsend.sendRC5(0x80C, 12);  // ON Signal
            delay(300);
            irrecv.enableIRIn();        // Enable IR Reciving
            tvPowerState = 1;           // Chandge TV status to ON
          }
          else 
          {
            irsend.sendRC5(0XC, 12);    // OFF Signal
            delay(300);
            irrecv.enableIRIn();        // Enable IR Reciving
            tvPowerState = 0;           // Chandge TV status to OFF
          }
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


/* button As Power Switch

      buttonStatus = digitalRead(buttonPin); // Physical button to on TV
      if(buttonStatus == HIGH)
        {
         Serial.println("POWER");     // Debug
         if(tvPowerState == 0)        // check if TV OFF
          {
            irsend.sendRC5(0x80C, 12);  // ON Signal
            delay(300);
            irrecv.enableIRIn();        // Enable IR Reciving
            tvPowerState = 1;           // Chandge TV status to ON
          }
          else 
          {
            irsend.sendRC5(0XC, 12);    // OFF Signal
            delay(300);
            irrecv.enableIRIn();        // Enable IR Reciving
            tvPowerState = 0;           // Chandge TV status to OFF
          }
         digitalWrite(testLedPin, HIGH);
         delay(100);
         digitalWrite(testLedPin, LOW);
        }


*/
  // put your main code here, to rIRrecv irrecv(RECV_PIN);

}
