#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //Pinos do LCD

String senhaPadrao = "12345"; //mudar a senha aqui
String senha = "";
int i = 0; 
int movimento; //sensor pir
int buzzer = 11;
int pinServo = 10;
Servo s;
const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS] [COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap (keys), rowPins, colPins, ROWS, COLS);

void setup()
{
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(12, INPUT); //sensor PIR
    pinMode(13, OUTPUT); //display backlight
    s.attach(pinServo);
  	s.write(0);
    lcd.begin(16,2);
    lcd.setCursor (0,0);
    lcd.print("INICIANDO...");
    delay(1000);
    lcd.setCursor(0,0);
    lcd.print("Pressione *");
}

void loop(){
   sensorPir();
}

void sensorPir(){
 	movimento = digitalRead(12); 
  
  if(movimento  == 1){
    digitalWrite(13, HIGH);
    lcd.display();
    char key = keypad.getKey();
    
        if (key == '*'){
            i = 0;
            lcd.clear();
            senha = "";
            digitarSenha();
        }
    
  } else {
    digitalWrite(13, LOW);
    lcd.noDisplay();
  }
}

void digitarSenha (){
    while (i < 5){
      char key = keypad.getKey();
      lcd.setCursor (0,0);
  	  lcd.print("Senha: ");
      lcd.setCursor (0,1);
    	lcd.print("# para limpar ");

      if(key){
        Serial.println(key);
          if(key == '#'){
            lcd.clear(); 
            i=0; 
            senha=""; 
          } else{
            senha += key; 
            lcd.setCursor(senha.length() + 6, 0); 
            lcd.print('*');
            i++; 
          }
      }
    } 

 	checarSenha();
}

void checarSenha(){
  if (senha == senhaPadrao){
    	lcd.clear();
    	Serial.println("Senha correta!");
        lcd.setCursor(0,0);
        lcd.print("Senha Correta!");
        lcd.setCursor(0,1);
        lcd.print("Porta aberta");
        s.write(75);
      	delay(2000);
        s.write(0);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Pressione * ");
      
    } else {
      lcd.clear();
      Serial.println("Senha incorreta, tente de novo!");   
      lcd.setCursor(0,0);
      lcd.print("Senha incorreta!");
      tone(buzzer,293);
      delay(1000);
      noTone(buzzer);
  	  lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pressione *");
    }
}