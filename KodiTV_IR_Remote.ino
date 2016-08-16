#include <IRLib.h>      // include IR libary
#define USE_DUMP        // disable not used 
#include <Keyboard.h>   // Pro micro keyboard lib

int signalLedPin = 15;   // Led for testing
int avSvichButton = 8;  // physical buton to Svich AV
boolean avSvichButtonState = 0; // Button state
int speekerPin = 3;     // Speeker

int irRecivePin = 10;    // ir reciever 
int irLedPin = 9;       // ir led for control TV

boolean tvPowerState = 0;       // Flip Bit default state
boolean sleepTimerState = 0;    // Flip Bit default state
boolean menuState = 0;          // Flip Bit default state
boolean okState = 0;            // Flip Bit default state
boolean upState = 0;            // Flip Bit default state
boolean downState = 0;          // Flip Bit default state
boolean avState = 0;            // Flip Bit default state

IRrecv irrecv(irRecivePin);     // set reciever to pin
IRsend irsend;

IRdecode results;               // decode recieved resolts
unsigned int Buffer[RAWBUF];

void setup() {
  irrecv.enableIRIn();          // Start the receiver
  results.UseExtnBuf(Buffer);
  pinMode(signalLedPin, OUTPUT);
  pinMode(avSvichButton, INPUT);
  pinMode(speekerPin, OUTPUT);
  
  delay(100);
  analogWrite(speekerPin, 6);   // Beep at boot
  delay(105);
  analogWrite(speekerPin, 0);
  
}

void loop() {

//------------------------------------------------------------------------------------
  if(irrecv.GetResults(&results)) //this checks to see if a code has been received
  {
      results.decode(); // start decode (if not decode value == 0)

      if (results.value == 0xFF629D) // Up - Up Kodi
        {
          Keyboard.press(KEY_UP_ARROW); // Up
          delay(50);
          Keyboard.release(KEY_UP_ARROW);
         
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFFA857) // Down - Down Kodi
        {
          Keyboard.press(KEY_DOWN_ARROW); // Down
          delay(50);
          Keyboard.release(KEY_DOWN_ARROW);

          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);

        }

      if (results.value == 0xFF22DD) // Left - Left Kodi
        {
    
          Keyboard.press(KEY_LEFT_ARROW); // Left
          delay(50);
          Keyboard.release(KEY_LEFT_ARROW);

          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFFC23D) // Right - Right Kodi
        {
          Keyboard.press(KEY_RIGHT_ARROW);  // Rihgt
          delay(50);
          Keyboard.release(KEY_RIGHT_ARROW);
          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }



      if (results.value == 0xFF02FD) // OK - OK Kodi
        {
          Keyboard.press(KEY_RETURN);   // Enter
          delay(50);
          Keyboard.release(KEY_RETURN);
          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);;
        }


      if (results.value == 0xFF6897)  // 1 - Power switch
        {
         if(tvPowerState == 0)            // Check flip bit state
          {
            irsend.send(RC5, 0x180C, 13); // ON/OFF Signal
            //delay(100);
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
            //delay(100);
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
          Keyboard.press(KEY_BACKSPACE);   // Backspace
          delay(50);
          Keyboard.release(KEY_BACKSPACE);
          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }

      
      if (results.value == 0xFFB04F) // 3 - Vol UP Kodi
        {
          Keyboard.write('+');    // VolUP

          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF30CF) // 4 - Sleep Timer
          {

         if(sleepTimerState == 0)         // Check flip bit state
          {
            irsend.send(RC5, 0x82B, 13);  // Sleep Timer Signal
            //delay(30);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            sleepTimerState = 1;          // Chandge flip bit state
          }
        else 
          {
            irsend.send(RC5, 0x2B, 13);   // Sleep Timer Signal
            //delay(30);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            sleepTimerState = 0;          // Chandge flip bit state
          }
         digitalWrite(signalLedPin, HIGH);
         delay(30);
         digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF18E7) // 5 - Kodi Play/Pause
        {
          Keyboard.write(' ');    //  Space
                   
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF7A85) // 6 - Vol Down Kodi
        {
          Keyboard.write('-');    //  VolDown
          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF10EF) // 7 - Menu
        {
          if(menuState == 0)               // Check flip bit state
            {
              irsend.send(RC5, 0x812, 13);  // Menu Signal
              //delay(30);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 1;                // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x12, 13);   // Menu Signal
              //delay(30);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              menuState = 0;                // Chandge flip bit state
            }

         digitalWrite(signalLedPin, HIGH);
         delay(30);
         digitalWrite(signalLedPin, LOW);;
        }


      if (results.value == 0xFF38C7) // 8 - Kodi Context menu 
        {
          Keyboard.write('c');    // Context menu
          
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);;
        }


      if (results.value == 0xFF5AA5) // 9 - TV Up
        {
          if(upState == 0)                  // Check flip bit state
            {
              irsend.send(RC5, 0x810, 13);  // UP Signal
              //delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              upState = 1;                  // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x10, 13);   // UP Signal
              //delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              upState = 0;                  // Chandge flip bit state
            }
            
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF4AB5) // 0
        {
          analogWrite(speekerPin, 32);       // Beep
          delay(105);
          analogWrite(speekerPin, 0);
          digitalWrite(signalLedPin, HIGH);
          delay(500);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF42BD) // * - TV OK
        {
          if(okState == 0)                  // Check flip bit state
            {
              irsend.send(RC5, 0x817, 13);  // OK Signal
              //delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              okState = 1;                  // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x17, 13);   // OK Signal
              //delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              okState = 0;                  // Chandge flip bit state
            }
                    
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }


      if (results.value == 0xFF52AD) // # - TV Down
        {
          if(downState == 0)                // Check flip bit state
            {
              irsend.send(RC5, 0x811, 13);  // Down Signal
              //delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              downState = 1;                // Chandge flip bit state
            }
          else 
            {
              irsend.send(RC5, 0x11, 13);   // Down Signal
              //delay(50);
              irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
              downState = 0;                // Chandge flip bit state
            }
            
          digitalWrite(signalLedPin, HIGH);
          delay(30);
          digitalWrite(signalLedPin, LOW);
        }
        
  irrecv.resume(); //receive the next value  
  results.decode(); //Restart the receiver so it can be capturing another 
  }
//------------------------------------------------------------------------------




      avSvichButtonState = digitalRead(avSvichButton); // Physical button to Chandge AV
      if(avSvichButtonState == HIGH)
        {
         if(avState == 0)                 // Check flip bit state
          {
            irsend.send(RC5, 0x1838, 13); // AV Signal
            //delay(100);
            irrecv.enableIRIn();          // Enable IR Reciving (after IRsend reciving disable)
            avState = 1;                  // Chandge flip bit state

          }
        else 
          {
            irsend.send(RC5, 0x1038, 13); // AV Signal
            //delay(100);
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
