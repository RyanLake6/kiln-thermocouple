
void setup() {
  Serial.begin(9600);

  pinMode(14, INPUT_PULLUP);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
}

void loop() {
  Serial.println(digitalRead(14));
   delay(1000);
}