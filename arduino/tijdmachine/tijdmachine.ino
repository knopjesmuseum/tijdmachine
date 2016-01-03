int avg0,avg1;
float s = 0.8;

void setup() {
  Serial.begin(9600);
    avg0=analogRead(0);
    avg1=analogRead(1);
//  analogReference(INTERNAL);
}

void loop() {
 
//  int count=15;
  //for (int i=0; i<count; i++) {
    avg0 = (int)round(s*avg0 + (1-s)*analogRead(0));
    avg1 = (int)round(s*avg1 + (1-s)*analogRead(1));
  
  //avg0/=count;
  //avg1/=count;
    
  while (Serial.available()) {
    Serial.read();
    Serial.print(avg0);
    Serial.print(",");
    Serial.print(avg1);
    Serial.println();
  }
}
