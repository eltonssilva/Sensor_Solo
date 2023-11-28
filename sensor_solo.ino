#include <ModbusRTU.h>


ModbusRTU mb;

bool cbWrite(Modbus::ResultCode event, uint16_t transactionId, void* data) {

  Serial1.printf("Request result: 0x%02X, Mem: %d\n", event, ESP.getFreeHeap());

  return true;
}

uint16_t res[9];

void setup() {

  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 22, 19);
  mb.begin(&Serial1);

  mb.master();
}

bool coils[20];
float umidade;
float temperatura;
float condutividade;
float ph;
float nitrogenio;
float phosforo;
float potassio;
float salinidade;

void loop() {

  if (!mb.slave()) {
    mb.readHreg(1, 0, res, 8);
  }

  umidade       = res[0]/10;
  temperatura   = res[1]/10;
  condutividade = res[2]/10;
  ph            = res[3]/10;
  nitrogenio    = res[4];
  phosforo      = res[5];
  potassio      = res[6];
  salinidade    = res[7];

  Serial.println("---------");
  Serial.println("");
  printf("Umidade %0.2f\%\n", umidade);
  printf("Temperatura %0.2f°C\n", temperatura);
  printf("PH %0.2f\n", ph);
  printf("Nitrogenio %0.2fmg/kg\n", nitrogenio);
  printf("Phosforo %0.2fmg/kg\n", phosforo);
  printf("Potassio %0.2fmg/kg\n", potassio);
  printf("salinidade %0.2fmg/L\n", salinidade);
  Serial.println("");
  Serial.println("---------");

  // delay(1000);

  // if (!mb.slave()) {
  //   mb.readHreg(1, 1, res, 1);
  // }
  // Serial.println("---------");
  // Serial.println(res[0]);
  // float temperatura = res[0];

  // printf("Temperatura %0.2f°C\n", temperatura/10);

  mb.task();
  delay(2000);
  yield();
}