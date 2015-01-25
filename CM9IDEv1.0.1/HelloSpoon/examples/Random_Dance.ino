#include <HelloSpoon.h>

HelloSpoon robot;

void setup(){
  robot.begin();
  dance();
}

void loop(){
  
}

void dance(){
  for(int mov = 1; mov < 10; mov++){
    int positions[4] = {random(100, 600), random(400, 800), random(300, 800), random(300, 800)};
  
    for(int id = 1; id < 5; id++){
      int num_color = random(1, 8);
    
      robot.moveJoint(id, positions[id-1]);
      robot.LED(id, led_color(num_color));
    }
    delay(2000);
  }
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
