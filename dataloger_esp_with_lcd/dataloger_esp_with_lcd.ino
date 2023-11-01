#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
const int rs = 9, en = 8, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

File dataFile;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  while (!Serial);
  Serial.print("Initializing SD card...");
  lcd.print("Initializing.");
  delay(1000);
  lcd.clear();
  if (!SD.begin()) {
    Serial.println("Initialization failed!");
    lcd.print("failed!");
    while (1);
  }
  Serial.println("Initialization done.");
  lcd.print("done.");
  delay(2000);
  lcd.clear();
}
String receivedData = "";
char buf[47];
void loop() {
  if (Serial.available()) {
    for(int i=1;i<46;i++)
    {
        buf[i-1]=buf[i];
    }
    buf[45] = Serial.read();
   
    if (buf[0]=='6'&& buf[1]=='0'&& buf[2]==':') {
      buf[46]='\0';
      Serial.println(buf);
      lcd.clear();
      lcd.print(buf+18); 
  
    
      
     
    //lcd.clear();
    //Serial.print("Received data: ");
    //lcd.print("RX:");
    //Serial.println(receivedData);
    //lcd.println(receivedData);
    //delay(1000);
    
    dataFile = SD.open("test1.csv", FILE_WRITE);
    if (dataFile) {
      dataFile.println(buf);
      dataFile.close();
    }
     else {
      Serial.println("Error opening test.txt");
      lcd.println("Error");
    }
    }
  }
}