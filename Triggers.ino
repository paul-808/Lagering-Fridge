
// Triggers() checks the PID algorithms and timers, and decides whether to change the state of any of the relays.

void Triggers () {
  coolPID.Compute();

  // Check PID
  if (Output > PIDpos && PIDpos > 180 ) {
    coolON = 1;
  }
  else {
    coolON = 0;
  }

  // Write to temp relay pins
  if (coolON == 1) {
    digitalWrite(ControlCpin, LOW);
  }
  else {
    digitalWrite(ControlCpin, HIGH);
  }

  // Control fans
  if (coolON == 1 || heatON == 1 || tempDiff > 1) {
    fanOFFmillis = millis();
    fanONmillis = millis();
    fanstate = true;
    digitalWrite(ControlApin, LOW);
  }
  else {
    fanstate = false;
    digitalWrite(ControlApin, HIGH);
  }
}
