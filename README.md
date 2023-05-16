display:

```cpp
#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

#define DELAY 1

TM1637Display display(CLK,DIO);

uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };

  
void setup() {
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(0);
  data[2] = display.encodeDigit(0);
}

void num(int dig, int val) {
  data[dig] = display.encodeDigit(val);
}

void loop(){
  int k;
  display.setBrightness(0x0f);
  
  for (int i = 1; i <= 10; i++){
    for (int j = 1; j <= 10; j++){
      for (int k = 1; k <= 10; k++){
        for (int l = 1; l <= 10; l++){
    
    
          num(3, l);
          display.setSegments(data);
          
          delay(DELAY);
        }
    
        num(2, k);
        display.setSegments(data);
        
        delay(DELAY);
      }
    
      num(1, j);
      display.setSegments(data);
      
      delay(DELAY);
    } 
    
    num(0, i);
    display.setSegments(data);
    
    delay(DELAY);
  }
  
}
```
