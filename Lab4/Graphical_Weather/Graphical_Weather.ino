#include <M5Stack.h>
#include <SimpleDHT.h>

#define BLACK   0x0000
#define RED     0xF800
#define CYAN    0x07FF
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define DHTPIN 5

SimpleDHT11 dht;

int leituraAtual = 1;

#define POS_X_GRAFICO 30
#define POS_Y_GRAFICO 3
#define ALTURA_GRAFICO 180
#define COMPRIMENTO_GRAFICO 270

#define POS_X_DADOS 30
#define POS_Y_DADOS 200

int umidade = 0;
int temperatura = 0;

int lineExample = 20;
int factor = 1;

void setup(void){
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawFastVLine(POS_X_GRAFICO,POS_Y_GRAFICO,ALTURA_GRAFICO,WHITE);
  M5.Lcd.drawFastHLine(POS_X_GRAFICO,ALTURA_GRAFICO+1,COMPRIMENTO_GRAFICO,WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(POS_X_DADOS,POS_Y_DADOS);
  M5.Lcd.print("T: ");
}

void loop(){
  float temp,humid;
  int status = dht.read2(DHTPIN,&temp,&humid,NULL);
  if(status == SimpleDHTErrSuccess){
    temperatura = temp;
    umidade = humid;
  }
  int temperaturaMapeada = map(temperatura,0,100,0,ALTURA_GRAFICO);
  int umidadeMapeada = map(umidade,0,100,0,ALTURA_GRAFICO);
  M5.Lcd.drawPixel(POS_X_GRAFICO+leituraAtual,ALTURA_GRAFICO-temperaturaMapeada,RED);
  M5.Lcd.drawPixel(POS_X_GRAFICO+leituraAtual,ALTURA_GRAFICO-umidadeMapeada,CYAN);
  M5.Lcd.drawPixel(POS_X_GRAFICO+leituraAtual,ALTURA_GRAFICO-lineExample,YELLOW);
  if(lineExample == 50)factor = -1;
  else if(lineExample == 10)factor = 1;
  lineExample += factor;
  leituraAtual++;
  if(leituraAtual == 270 || M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed())
  {
    M5.Lcd.fillRect(POS_X_GRAFICO+1,POS_Y_GRAFICO-1,COMPRIMENTO_GRAFICO,ALTURA_GRAFICO-1,BLACK);
    leituraAtual = 1;
  }
  M5.Lcd.fillRect(POS_X_DADOS+50,POS_Y_DADOS,60,30,BLACK);
  M5.Lcd.fillRect(POS_X_DADOS+165,POS_Y_DADOS,90,30,BLACK);
  M5.Lcd.setCursor(POS_X_DADOS+50,POS_Y_DADOS);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print(temperatura);
  M5.Lcd.print((char)247);
  M5.Lcd.setCursor(POS_X_DADOS+165, POS_Y_DADOS);  
  M5.Lcd.setTextColor(CYAN);
  M5.Lcd.print("U: ");
  M5.Lcd.print(umidade);
  M5.Lcd.print("%");
  delay(300);
  M5.update();
}
