#define ANALOG_INPUT_PIN 36
hw_timer_t * ledTimer = NULL; /* กำหนดตัวแปรสำหรับฮาร์ดแวร์ไทเมอร์ */
int ledPin = 32; /* ขาที่ใช้ควบคุม LED */

void IRAM_ATTR toggleLED(){
  digitalWrite(ledPin, !digitalRead(ledPin));
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);  
  /* ใช้ไทเมอร์ตัวที่ 1 จากทั้งหมด 4 ตัว */
  /* 1 ทิก ใช้เวลา 1/(80MHz/80) = 1us ดังนั้นตั้งค่าตัวแบ่งเป็น 80 และนับขึ้น */
  ledTimer = timerBegin(0, 80, true);
  /* เชื่อมโยงฟังก์ชัน toggleLED กับไทเมอร์ */
  timerAttachInterrupt(ledTimer, &toggleLED, true);
  /* กำหนดให้เรียกฟังก์ชัน toggleLED ทุก ๆ 1 วินาที */
  timerAlarmWrite(ledTimer, 1000000, true);
  /* เปิดใช้งานไทเมอร์ */
  timerAlarmEnable(ledTimer);
}

void loop() {
  int analogValue = analogRead(ANALOG_INPUT_PIN);  // อ่านค่าสัญญาณแอนะล็อกจากขา 36

  Serial.println(analogValue);  // แสดงค่าบน Serial Monitor
    if (analogValue >= 4021 && analogValue <= 4035) {  // เมื่อกดปุ่ม P1
      timerAlarmWrite(ledTimer, 250000, true);  // ความถี่ 2 Hz (กระพริบ 2 ครั้งต่อวินาที)
    } 
    else if (analogValue >= 3240 && analogValue <= 3260) {  // เมื่อกดปุ่ม P2
      timerAlarmWrite(ledTimer, 100000, true);  // ความถี่ 5 Hz (กระพริบ 5 ครั้งต่อวินาที)
    } 
    else if (analogValue >= 2600 && analogValue <= 2620) {  // เมื่อกดปุ่ม P3
      timerAlarmWrite(ledTimer, 50000, true); // ความถี่ 10 Hz (กระพริบ 10 ครั้งต่อวินาที)
    } 
    else if (analogValue >= 1840 && analogValue <= 1860) {  // เมื่อกดปุ่ม P4
      timerAlarmWrite(ledTimer, 20000, true);  // ความถี่ 25 Hz (กระพริบ 25 ครั้งต่อวินาที) 
    } 
    else if (analogValue >= 1120 && analogValue <= 1160) {  // เมื่อกดปุ่ม P5
      timerAlarmWrite(ledTimer, 16667, true); // ความถี่ 30 Hz (กระพริบ 30 ครั้งต่อวินาที)
    }
    else {  // กรณีไม่มีการกดปุ่มใด ๆ
      timerAlarmWrite(ledTimer, 1000000, true); // ความถี่ 1 Hz (กระพริบ 1 ครั้งต่อวินาที)
    }
}
