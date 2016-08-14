#include <IRLib.h>     // include IR libary

#define USE_DUMP      // disable not used 

int signalLedPin = 10;   // Led for testing
int buttonPin = 8;    // button for testing
int avSvichButton = 12; // physical buton to Svich AV
boolean avSvichButtonState = 0; // Button state
int speekerPin = 9;      // Speeker

int irRecivePin = 11;  // ir reciever 
int irLedPin = 3;      // ir led for control TV

boolean buttonState = 0; 

boolean tvPowerState = 0;       // Flip Bit default state

boolean sleepTimerState = 0;    // Flip Bit default state
int sleepTimerPositionSet = 8;  // off - 15 - 30 - 45 - 60 - 90 - 120 - 180 - 240

boolean menuState = 0;    // Flip Bit default state

boolean okState = 0;      // Flip Bit default state

boolean upState = 0;      // Flip Bit default state

boolean downState = 0;    // Flip Bit default state

boolean avState = 0;    // Flip Bit default state


IRrecv irrecv(irRecivePin); // set reciever to pin
IRsend irsend;

IRdecode results;     // decode recieved resolts
unsigned int Buffer[RAWBUF];

void setup() {
  Serial.begin(9600);       // print output for debug
  irrecv.enableIRIn();      // Start the receiver
  results.UseExtnBuf(Buffer);
  pinMode(signalLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(speekerPin, INPUT);
}

void loop() {

//------------------------------------------------------------------------------------
  if(irrecv.GetResults(&results)) //this checks to see if a code has been received
  {
      results.decode(); // start decode (if not decode value == 0)

      if (results.value == 0xFF629D) // Up - Up Kodi
        {
         Serial.println("Up");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFFA857) // Down - Down Kodi
        {
         Serial.println("Down");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);

        }

      if (results.value == 0xFF22DD) // Left - Left Kodi
        {
         Serial.println("Left");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFFC23D) // Right - Right Kodi
        {
         Serial.println("Right");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }



      if (results.value == 0xFF02FD) // OK - OK Kodi
        {
         Serial.println("OK");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);;
        }


      if (results.value == 0xFF6897)  // 1 - Power switch
        {
         Serial.println("POWER");         // Debug
         if(tvPowerState == 0)            // Check flip bit state
          {
            irsend.send(RC5, 0x180C, 13); // ON/OFF Signal
            delay(300);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            tvPowerState = 1;             // Chandge flip bit state
            
            // On Sound ------------------
            delay(105);
            analogWrite(speekerPin, 32);
            delay(105);
            analogWrite(speekerPin, 0);
            delay(125);
            analogWrite(speekerPin, 38);
            delay(105);
            analogWrite(speekerPin, 0);
            //-----------------------------
          }
        else 
          {
            irsend.send(RC5, 0x100C, 13); // ON/OFF Signal
            delay(300);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            tvPowerState = 0;             // Chandge flip bit state

            // On Sound ------------------
            delay(105);
            analogWrite(speekerPin, 38);
            delay(105);
            analogWrite(speekerPin, 0);
            delay(125);
            analogWrite(speekerPin, 32);
            delay(105);
            analogWrite(speekerPin, 0);
            //-----------------------------
            
          }
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF9867) // 2 - back Kodi
        {
         Serial.println("2");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }

      
      if (results.value == 0xFFB04F) // 3 - Vol UP Kodi
        {
         Serial.println("3");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF30CF) // 4 - Sleep Timer
          {
         Serial.println("TIMER");         // Debug
         for (int i=0; i<sleepTimerPositionSet; i++)  // Push button 8 times
         {
         if(sleepTimerState == 0)         // Check flip bit state
          {
            irsend.send(RC5, 0x82B, 13);  // Sleep Timer Signal
            delay(300);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            sleepTimerState = 1;          // Chandge flip bit state
          }
        else 
          {
            irsend.send(RC5, 0x2B, 13);   // Sleep Timer Signal
            delay(300);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            sleepTimerState = 0;          // Chandge flip bit state
          }
         }
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF18E7) // 5
        {
         Serial.println("5");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF7A85) // 6 - Vol Down Kodi
        {
         Serial.println("6");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF10EF) // 7 - Brightness UP
        {
          Serial.println("Brightness UP"); // Debug

          // Enter Menu ---------------------------------------------------------------------------
          if(menuState == 0)               // Check flip bit state
            {
              irsend.send(RC5, 0x812, 13);  // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 1;                // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x12, 13);   // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 0;                // Chandge flip bit state
            }
          //---------------------------------------------------------------------------------------

          // Press OK button 2 times --------------------------------------------------------------
          for (int i=0; i<2; i++)
            {
              if(okState == 0)                  // Check flip bit state
                {
                  irsend.send(RC5, 0x817, 13);  // OK Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  okState = 1;                  // Chandge flip bit state
                }
              else 
                {
                  irsend.send(RC5, 0x17, 13);   // OK Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  okState = 0;                  // Chandge flip bit state
                }
              delay(100);                       // Not so fast
            }
          //----------------------------------------------------------------------------------------

          // Press UP button 10 times --------------------------------------------------------------
          for (int i=0; i<10; i++)
            {
              if(upState == 0)                  // Check flip bit state
                {
                  irsend.send(RC5, 0x810, 13);  // UP Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  upState = 1;                  // Chandge flip bit state
                }
              else 
                {
                  irsend.send(RC5, 0x10, 13);   // UP Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  upState = 0;                  // Chandge flip bit state
                }
            }
          //----------------------------------------------------------------------------------------

          // Close Menu  -----------------------------------------------------------------------------
          if(menuState == 0)               // Check flip bit state
            {
              irsend.send(RC5, 0x812, 13);  // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 1;                // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x12, 13);   // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 0;                // Chandge flip bit state
            }
         //-------------------------------------------------------------------------------------------
         
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);;
        }


      if (results.value == 0xFF38C7) // 8
        {
         Serial.println("8");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);;
        }


      if (results.value == 0xFF5AA5) // 9
        {
         Serial.println("9");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF4AB5) // 0
        {
         Serial.println("0");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF42BD) // * - Brighness Down
        {
          Serial.println("Brightness Down");// Debug

          // Enter Menu ---------------------------------------------------------------------------
          if(menuState == 0)               // Check flip bit state
            {
              irsend.send(RC5, 0x812, 13);  // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 1;                // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x12, 13);   // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 0;                // Chandge flip bit state
            }
          //---------------------------------------------------------------------------------------

          // Press OK button 2 times --------------------------------------------------------------
          for (int i=0; i<2; i++)
            {
              if(okState == 0)                  // Check flip bit state
                {
                  irsend.send(RC5, 0x817, 13);  // OK Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  okState = 1;                  // Chandge flip bit state
                }
              else 
                {
                  irsend.send(RC5, 0x17, 13);   // OK Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  okState = 0;                  // Chandge flip bit state
                }
              delay(100);                       // Not so fast
            }
          //----------------------------------------------------------------------------------------

          // Press Down button 10 times --------------------------------------------------------------
          for (int i=0; i<10; i++)
            {
              if(downState == 0)                // Check flip bit state
                {
                  irsend.send(RC5, 0x811, 13);  // Down Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  downState = 1;                // Chandge flip bit state
                }
              else 
                {
                  irsend.send(RC5, 0x11, 13);   // Down Signal
                  delay(50);
                  irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
                  downState = 0;                // Chandge flip bit state
                }
            }
          //----------------------------------------------------------------------------------------

          // Close Menu  -----------------------------------------------------------------------------
          if(menuState == 0)               // Check flip bit state
            {
              irsend.send(RC5, 0x812, 13);  // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 1;                // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x12, 13);   // Menu Signal
              delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 0;                // Chandge flip bit state
            }
         //-------------------------------------------------------------------------------------------
        
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF52AD) // #
        {
         Serial.println("#");
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }
        
  irrecv.resume(); //receive the next value  
  results.decode(); //Restart the receiver so it can be capturing another 
  }
//------------------------------------------------------------------------------




      avSvichButtonState = digitalRead(avSvichButton); // Physical button to Chandge AV
      if(avSvichButtonState == HIGH)
        {
         Serial.println("AV");            // Debug
         if(avState == 0)                 // Check flip bit state
          {
            irsend.send(RC5, 0x1838, 13); // AV Signal
            delay(100);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            avState = 1;                  // Chandge flip bit state

          }
        else 
          {
            irsend.send(RC5, 0x1038, 13); // AV Signal
            delay(100);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            avState = 0;                  // Chandge flip bit state
          }
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
         
         analogWrite(speekerPin, 32);       // Beep
         delay(105);
         analogWrite(speekerPin, 0);
        }



//-----------------------------------------------------------------------------
/* button As Power Switch
      buttonState = digitalRead(buttonPin); // Physical button to on TV
      if(buttonState == HIGH)
        {
         Serial.println("POWER");         // Debug
         if(tvPowerState == 0)            // Check flip bit state
          {
            irsend.send(RC5, 0x180C, 13); // ON/OFF Signal
            delay(300);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            tvPowerState = 1;             // Chandge flip bit state
          }
        else 
          {
            irsend.send(RC5, 0x100C, 13); // ON/OFF Signal
            delay(300);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            tvPowerState = 0;             // Chandge flip bit state
          }
         digitalWrite(signalLedPin, HIGH);
         delay(100);
         digitalWrite(signalLedPin, LOW);
        }

*/


}
