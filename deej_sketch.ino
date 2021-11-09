const int NUM_SLIDERS = 5;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};

/*button and led pins*/
const int ledPin = 2;
const int buttonPin = 3;

int analogSliderValues[NUM_SLIDERS+1];//add 1 for the mic
int buttonState = 0;
int muteState = 0;

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }
  
  /* add button and led information */
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //read the state of the pushbutton value;
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {
    toggleMuteState();
  }
  
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug

  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
  if(muteState) {
      analogSliderValues[NUM_SLIDERS] = 0;
  } else {
    analogSliderValues[NUM_SLIDERS] = 1024; //1024 is apparently the max?
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS+1; i++) {//add 1 for mic
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS) { //removed the -1 since we are adding a mic 
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogSliderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void toggleMuteState() {
    muteState = !muteState;

    //if muted the light is on.
    if (muteState) {
      
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    //delay or it will input a shit ton of values
    delay(200);
}

