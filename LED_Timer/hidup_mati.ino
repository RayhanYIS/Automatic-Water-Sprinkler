/* void LED
 * dibuat pada 
 * oleh 
 */
void hidup_mati() {

  if (jam == 18 && menit == 20 && detik == 0) {
    digitalWrite(LED, LOW);
    delay(10000);
  }
  else if (jam == 16 && menit == 12) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }
}


 
