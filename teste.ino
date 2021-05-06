#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //Pinos do LCD

String senha = "123456";
String buf = "";
int i = 0; 
int lampada = 11;
const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS] [COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'6', '7', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap (keys), rowPins, colPins, ROWS, COLS);

void setup()
{
    Serial.begin(9600);
    pinMode(lampada, OUTPUT);
  	digitalWrite(lampada, LOW);
    lcd.begin(16,2);
    lcd.setCursor (0,0);
    lcd.print("INICIANDO...");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("Pressione *");
}

void loop(){
  
    char key = keypad.getKey();

    if(key != NO_KEY){
        if (key == '*'){
            i = 0;
            lcd.clear();
            buf = "";
            password(); 
        }
    }
}

void password (){
    while (i < 6){
        lcd.setCursor (0,0);
        lcd.print("Senha: ");
      
        char key = keypad.getKey();
        if(key != NO_KEY){
            buf += key;
            lcd.print(buf);
            i++;
        }
    }

    if (buf == senha){
        lcd.setCursor(0,1);
        lcd.print("Porta aberta");
      	digitalWrite(lampada, HIGH);
      	delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Pressione * ");
      
    } else {
      lcd.setCursor(0,0);
      lcd.print("Pressione * ");
      lcd.setCursor(0,1);
      lcd.print("SENHA INCORRETA");
      digitalWrite(lampada, LOW);
	}
}