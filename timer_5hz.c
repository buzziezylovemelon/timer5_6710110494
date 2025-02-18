hw_timer_t * timer = NULL;  /* create a hardware timer */
int led = 32; /* LED pin */
//Also, interrupt handling routines should only call functions also placed in IRAM
void IRAM_ATTR onTimer(){
  digitalWrite(led, !digitalRead(led));
}

void setup() {
  pinMode(led, OUTPUT);
  /* Use 1st timer of 4 */
  /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);
  /* Set alarm to call onTimer function every second 1 tick is 1us  => 1 second is 100000us */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 100000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}

void loop() {
}