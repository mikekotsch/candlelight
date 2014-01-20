// input & output pins
int r_pin = 11;
int g_pin = 9;
int b_pin = 10;

int lighter_pin = 2;

// global variable
boolean candlelight = false;

void flicker(int r1, int g1, int b1, int r2, int g2, int b2, int t);

void setup() {

  Serial.begin(9600);

  // set button pin
  pinMode(lighter_pin, INPUT_PULLUP);
}

void loop() {

  if(!candlelight) {
    checkButton(); 
  } else {
   
   int r1 = random(254,255);
   int g1 = random(120,140);
   int b1 = random(10,40);
   int r2 = random(254,255);
   int g2 = random(120,140);
   int b2 = random(10,40);

   int t = random(1000,3000);
  
   //Example sequence one: Rainbow fade over 15 seconds:
   flicker(r1,g1,b1,r2,g2,b2,t); //fade from red to green over 5 seconds 
  }
}

void flicker(int r1, int g1, int b1, int r2, int g2, int b2, int t) {

  Serial.println("Flicker aufgerufen");

  float r_float1, g_float1, b_float1;
  float r_float2, g_float2, b_float2;
  float grad_r, grad_g, grad_b;
  float output_r, output_g, output_b;

  //declare integer RGB values as float values
  r_float1 = (float) r1;
  g_float1 = (float) g1;
  b_float1 = (float) b1;
  r_float2 = (float) r2;
  g_float2 = (float) g2;
  b_float2 = (float) b2;

  //calculate rates of change of R, G, and B values
  grad_r = (r_float2-r_float1)/t;
  grad_g = (g_float2-g_float1)/t;
  grad_b = (b_float2-b_float1)/t;

  //loop round, incrementing time value "i"
  for ( float i=0; i<=t; i++ )
  {

    output_r = r_float1 + grad_r*i;
    output_g = g_float1 + grad_g*i;
    output_b = b_float1 + grad_b*i;

    //map values - arduino is sinking current, not sourcing it
    output_r = map (output_r,0,255,255,0);
    output_g = map (output_g,0,255,255,0);
    output_b = map (output_b,0,255,255,0);

    //output
    analogWrite(r_pin, (int)output_r);
    analogWrite(g_pin, (int)output_g);
    analogWrite(b_pin, (int)output_b);

    //hold at this colour set for 1ms
    delay(1);

  }
}

void checkButton() {

  int lighter = digitalRead(2);
  if(!lighter) {
    Serial.println("Light up");
    lightup();
  } 
}

void lightup() {

  Serial.println("Lightup aufgerufen");  
  candlelight = true;
}

void blowout() {

  Serial.println("Blowout aufgerufen");

  int output_r = 0;
  int output_g = 0;
  int output_b = 0;

  //map values - arduino is sinking current, not sourcing it
  output_r = map (output_r,0,255,255,0);
  output_g = map (output_g,0,255,255,0);
  output_b = map (output_b,0,255,255,0);

  //output
  analogWrite(r_pin, (int)output_r);
  analogWrite(g_pin, (int)output_g);
  analogWrite(b_pin, (int)output_b);

  candlelight = false;
}

