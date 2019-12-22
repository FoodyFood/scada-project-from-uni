void setup()
{
  Serial.begin(57600);                                    //Setup Serial
  for(int pin=2;pin<=12;pin++)
  {
    pinMode(pin, INPUT);           // set pin to input
    digitalWrite(pin, HIGH);       // turn on pullup resistors
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    if(Serial.read() == 'H');
    {
      Serial.flush();

      //Set up the Bytes to be Transmitted
      char bOne=0;
      char bTwo=0;

      //Toggle the onboard LED to show a read happened
      digitalWrite(13, !(digitalRead(13)));

      //Byte One
      if(digitalRead(2))
        bitSet(bOne,0);
      if(digitalRead(3))
        bitSet(bOne,1);
      if(digitalRead(4))
        bitSet(bOne,2);
      if(digitalRead(5))
        bitSet(bOne,3);
      if(digitalRead(6))
        bitSet(bOne,4);
      if(digitalRead(7))
        bitSet(bOne,5);
      if(digitalRead(8))
        bitSet(bOne,6);
      if(digitalRead(9))
        bitSet(bOne,7);

      //Byte Two
      if(digitalRead(10))
        bitSet(bTwo,0);
      if(digitalRead(11))
        bitSet(bTwo,1);
      if(digitalRead(12))
        bitSet(bTwo,2);

      //Transmit the bytes
      Serial.print(10,BYTE);
      Serial.print(bOne,BYTE);
      Serial.print(bTwo,BYTE);
      Serial.print(10,BYTE);
    }
    Serial.flush();
  }
}



