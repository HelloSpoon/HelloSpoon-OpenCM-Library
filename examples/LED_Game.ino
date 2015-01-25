#include <HelloSpoon.h>

HelloSpoon robot;

void setup(){

  robot.begin();
  
}

void loop(){
  
  int num_color = random(1, 8);
  int id = random(1, 5);
  
  robot.LED(id, led_color(num_color));
  delay(1000);

}

char led_color(int num){
char color[];

  switch(num){
    case 1:
            color[] = "red";
            break;
    
    case 2: color[] = "blue";
            break;
            
    case 3:
            color[] = "green";
            break;
    
    case 4: color[] = "yellow";
            break;
            
    case 5:
            color[] = "white";
            break;
    
    case 6: color[] = "cyan";
            break;   
            
    case 7: color[] = "pink";
            break;    
            
  }
  return color[];
}
