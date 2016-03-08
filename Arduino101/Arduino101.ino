#define button1 10
#define button2 9
#define qtd_button 2
#define LED 13


unsigned long new_time;
unsigned long old_time;
int time_lapse;
int led_state;
int pin_times[20];
int time_gap;
int stopExe;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  Serial.begin(9600);
  new_time = millis();
  old_time = new_time;
  time_lapse = 1000;
  led_state = false; 
  time_gap = 500;
  stopExe = false;
  Serial.println("Comecei ");

}

void loop() {
  if(isItTime()){
    led_state = !led_state;
    digitalWrite(LED, led_state);
    
  }

  //Serial.print("LED: "); Serial.println(led_state);
  
  if(readPin(button1) ){
    if(new_time > (pin_times[button2] + 500)){
       Serial.println("Button1 time");
       Serial.println(time_gap);
       time_gap-=20;
       if(time_gap < 0)
        time_gap=0;
       stopExe = false;
    }
    else{
       stopExe = true;
    }
    
  }
  if(readPin(button2)){
    if(new_time > (pin_times[button1] + 500)){
      Serial.println("Button2 time");
      Serial.println(time_gap);
      time_gap+=20;
      if(time_gap < 0)
        time_gap=0;
      stopExe = false;
    }
    else{
      stopExe = true;
    }
  }
    
}

int isItTime(){
  new_time = millis();
  if(!stopExe && new_time > (old_time + time_lapse)){
    old_time = new_time;
    return true;
  }
  return false;
}

int readPin(int button){
  static int state[20]; // = {LOW, LOW} ;
  if(state[0] == NULL){
    for(int i=0;i<qtd_button;i++){
      state[i] = 0;
      pin_times[i] = 0;
    }
  }
  int r = digitalRead(button);
  if( state[button] != r){
    if(r){
      //Serial.print("R: "); Serial.println(led_state);
      //Serial.print("state: "); Serial.println(led_state);
      //Serial.print("Button: "); Serial.println(led_state);
      state[button] = HIGH;
      pin_times[button] = millis();
      return HIGH;
    }
    else{
      state[button] = LOW;
    }
  }
  return LOW;
}

