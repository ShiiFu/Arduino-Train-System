// Constante to declare usage of each pin
const int startingDetector = 2;
const int endingDetector = 3;
const int output = 10;

int buttonState;

// Variable to save last state of each detector
int startingDetectorState = HIGH;
int endingDetectorState = HIGH;

// Init pin to input or output
void setup()
{
	pinMode(startingDetector, INPUT);
	pinMode(endingDetector, INPUT);
	pinMode(output, OUTPUT);
}

void loop()
{
	buttonState = digitalRead(startingDetector);
	if((buttonState != startingDetectorState) && (buttonState == LOW))
	{
		// Activate output
		digitalWrite(output, LOW);
	}
	
	buttonState = digitalRead(endingDetector);
	if((buttonState != endingDetectorState) && (buttonState == LOW))
	{
		// Desactivate output
		digitalWrite(output, HIGH);
	}
}
