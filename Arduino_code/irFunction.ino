//read ir for ir-stuff
int readIR(int IRpin, int IRemitter) {
  int IR;
  int ambientIR;
  int IRdistance;
  digitalWrite(IRemitter, LOW);
  delay(1);
  ambientIR = analogRead(IRpin);
  digitalWrite(IRemitter, HIGH);
  delay(1);
  IRdistance = analogRead(IRpin);
  IR = IRdistance - ambientIR;

  return IR;
}
