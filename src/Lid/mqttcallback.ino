
// ==================================  mqtt callback ==================================
// This function is executed when some device publishes a message to a topic that this ESP8266 is subscribed to.
// The MQTT payload is the filename of the message to play when the phone is picked up.  The payload is case-sensitive.
//
void callback(String topic, byte * payload, unsigned int length) {
  char message[length + 1];

  // copy contents of payload to message
  // convert the payload from a byte array to a char array
  memcpy(message, payload, length);
  message[length] = '\0';                 // add NULL terminator to message

  // Sometimes in the MQTT tool, I accdentally hit "Enter" on my keyboard.
  // This removes it.
  for (size_t i = 0; i == strlen(message); i++) {
    if (message[i] == 10) {
      message[i] = '\0';
      break;
    }
  }


  Serial.println();
  Serial.println();
  Serial.print(F("Message arrived on topic: "));
  Serial.print(topic);
  Serial.println(F("."));

  Serial.print("message: ");
  Serial.println(message);
  Serial.print(F("Length= "));
  Serial.print(strlen(message));
  Serial.println();

  // If the message terminates in a line-feed, make it the terminating null char.
  int j = strlen(message) - 1;
  if (message[j] == 10) message[j] = '\0';



  // --------- Command ---------
  if (topic == cmndTopic) {                    // Process incoming commands
    Serial.print(F("received message on cmdTopic: '"));
    Serial.print(message);
    Serial.println(F("'"));

    if (!strcmp(message, "fanon")) {
      //Turn on the mist fan.
      Serial.println(F("Fan On"));
      analogWrite(FAN_PIN, 250);
    }

    if (!strcmp(message, "fanoff")) {
      //Turn on the mist fan.
      Serial.println(F("Fan Off"));
      analogWrite(FAN_PIN, 0);
    }

    if (!strcmp(message, "eyeson")) {
      //Turn on the eyes
      Serial.println(F("Eyes On"));
      analogWrite(EYES_PIN, eyesVal);

    }

    if (!strcmp(message, "eyesoff")) {
      //Turn off the eyes
      Serial.println(F("Eyes Off"));
      analogWrite(EYES_PIN, 0);
    }

    if (!strcmp(message, "open")) {
      //Open the lid
      Serial.println(F("Open the lid"));
      openTheLid();
    }

    if (!strcmp(message, "close")) {
      //Close the lid
      Serial.println(F("Close the lid"));
      closeTheLid();
    }

    if (!strcmp(message, "openclose")) {
      //Close the lid
      openTheLid();
      delay(250);
      closeTheLid();
    }


    if (!strcmp(message, "help")) {
      client.publish (statusTopic, "MQTT commands: fanon fanoff eyeson eyesoff open close roar");
      //Print the available commands
      //Serial.println(F("Commands: "));
      //Serial.println(F("fanOn -  Turn on the mist fan."));
      //Serial.println(F("fanOff - Turn off the mist fan."));
      //Serial.println(F("eyesOn - Turn on the eyes LEDs."));
      //Serial.println(F("eyesOff - Turn off the eyes LEDs."));
      //Serial.println(F("open - Open the lid."));
      //Serial.println(F("close - Close the lid."));
      //Serial.println(F("Open and Close the lid."));
    }


    if (!strcmp(message, "roar")) {
      //Tell the sound board to start
      client.publish ("dfplayer/cmnd", "roar");
      //Start the open/close sequence.
      syncClose();                    //Close the lid and start the sync open timer.
    }
  }




  // --------- syncTopic ---------
  if (topic == syncTopic) {
    //Start the open/close sequence.
    //dfplayer.ino also subscribes to this topic.
    Serial.println(F("Roar"));
    syncClose();                    //Close the lid and start the sync open timer.
  }


} //callback
