int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    if(incomingByte ==10){
      digitalWrite(2, HIGH);  
      digitalWrite(3, LOW);  
    }else if (incomingByte ==20){
      digitalWrite(2, HIGH);  
      digitalWrite(3, LOW);  
    }else{
      digitalWrite(2, LOW);  
      digitalWrite(3, LOW); 
    }
  }
  delay(1000);
}