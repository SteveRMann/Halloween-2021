//=============== loop ===============
void loop() {
  ArduinoOTA.handle();
  mqttReconnect();         //Make sure we stay connected to the mqtt broker
  menu();
  
  closeTheLid();
  delay(FIVESEC);
  openTheLid();
  delay(FIVESEC);

  /*
    closeTheLid();
    delay(6000);

    //Thrash the lid
    motorPwm = 200;                   //Fast
    for (int i = 0; i < 5; i++) {
    openTheLid();
    closeTheLid();
    }
    motorPwm = MIN_PWM;               //Default speed
    delay(15000);
  */
}