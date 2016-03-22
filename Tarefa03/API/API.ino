
/**** GLOBAL VARIABLES ****/
#define LED_PIN 13
#define BUT_PIN1 2
#define BUT_PIN2 3

// char readBuffer[128];
// char newMessage = 0;
unsigned long int blink_speed = 1000;
int global_state_for_blink = HIGH;
unsigned long int timer = 0;
int last = 0;
/**** GLOBAL VARIABLES ****/

//Ovewrite this value to allow the usage of more ports
#define PORT_AMOUNT 2
#define DEBUG

/***** Event Driven API ****/
//////CALLBACKS //////////////
void button_changed(int pin, int v);
void timer_expired(void);
void user_init(void);
//////CALLBACKS //////////////
char ports[PORT_AMOUNT] = {0};
char ports_state[PORT_AMOUNT] = {LOW} ;
char ports_counter=0;
unsigned long time_elapsed = 0;
unsigned long time_started = 0;

void EventDrivenAPI_setup(void){
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  user_init();
}

void EvenDriveAPI_start(void){
  int count = 0;
  while(1){
    if(time_elapsed){
      if((millis() - time_started) > time_elapsed){
        time_elapsed = 0;
        timer_expired();
      }
    }

    if(count == PORT_AMOUNT)
      count = 0;

    if(ports[count]!=0 
       && digitalRead(ports[count]) != ports_state[count]){
      ports_state[count] = !ports_state[count];
      button_changed(ports[count], ports_state[count]);
      #ifdef DEBUG
        Serial.println("Called button_changed");
      #endif
    }
    count++;
  }
}
///////REGISTERS /////////////
void button_listen(int pin){
  for(int i=0; i<ports_counter; i++){
    if(ports[i] == pin)
      return;
  }
  pinMode(pin, INPUT);
  ports[ports_counter] = pin;
  ports_state[ports_counter] = LOW;
  ports_counter++;
  #ifdef DEBUG
    Serial.print("Button Registered: ");
    Serial.println(pin);
  #endif
}

void timer_set(int ms){
  time_elapsed = ms;
  time_started = millis();
  #ifdef DEBUG
    Serial.print("Timer Set: ");
    Serial.println(ms);
  #endif
}

///////REGISTERS /////////////
/***** Event Driven API ****/

void setup() {
  EventDrivenAPI_setup();
}

void loop() {
  EvenDriveAPI_start();
}
/******* USER CODE  Tarefa02*********/

void user_init(void){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  button_listen(BUT_PIN1);
  button_listen(BUT_PIN2);
  timer_set(blink_speed);
}
void button_changed(int pin, int v){
  if(timer == 0 && last ==0){
    timer = millis();
    last = pin;
  }
  if(pin != last && (millis() - timer) > 500){
    blink_speed = 0;
    last = pin;
    return;
  }
  last = pin;
  timer = millis();
  if(pin == BUT_PIN1 && v == HIGH){
    blink_speed +=100;
  }
  else if (pin == BUT_PIN2 && v == HIGH){
    blink_speed -=100; 
  }
  if(blink_speed < 0)
    blink_speed = 0;
  Serial.print("blink :"); Serial.println(blink_speed);
}
void timer_expired(void){
  // static int state = LOW;
  global_state_for_blink = !global_state_for_blink;
  digitalWrite(LED_PIN, global_state_for_blink);
  timer_set(blink_speed);
}

/******* USER CODE  Tarefa02*********/

/******* USER CODE  Hello World*********/
// void user_init(void){
//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, HIGH);
//   button_listen(BUT_PIN1);
// }
// void button_changed(int pin, int v){
//   //Serial.println("Changed")
//   digitalWrite(LED_PIN, v);
// }
// void timer_expired(void){

// }
/******* USER CODE  Hello World*********/

