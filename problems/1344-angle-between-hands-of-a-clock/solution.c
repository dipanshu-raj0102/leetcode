double angleClock(int hour, int minutes) {

   if (hour < 0 || minutes < 0 || hour > 12 || minutes > 59) return 0;

   hour = hour % 12;
   double angle = fabs(30.0 * hour - 5.5 * minutes);
   return fmin(angle, 360.0 - angle);
}