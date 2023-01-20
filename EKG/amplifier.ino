int amplifier() {
  int amplifyValg = map(analogRead(A5), 0, 1023, 100, 0);
  return amplifyValg;
}
// Opdatere hvor mange procent der skal vises ud fra via potentiometer
