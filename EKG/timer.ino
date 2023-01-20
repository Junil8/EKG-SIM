int timerAdjust ()
{
  int timervalg = map(analogRead(A1), 0, 1023, 6, 38);
  return timervalg;
}

// bruges til timervalg, sætter beats per minute
//40 * 40 = 1600, 60 / 1600 = 0,0375 interval 37,5 ms
//240 * 40 = 9600, 60 / 9600 = 0,00625 interval 6,2 ms
