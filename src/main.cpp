#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 9        // leds quantity
#define PIN 8             // ws2812 pin
#define MIN_SPD 30        // line speed min
#define MAX_SPD 200       // line speed max
#define SPD_RESOLUTION 10 // line speed resolution
// #define ROUND_TIMEOUT 3000 // round timeout
#define BLINK_COUNTS 3  // count of blinks
#define BLINK_DELAY 100 // delay between blinks

#define RedColor CRGB::Green
#define GreenColor CRGB::Red
#define BlueColor CRGB::Blue
#define YellowColor CRGB::Yellow
#define WhiteColor CRGB::White
#define OffColor CRGB::Black

CRGB leds[NUM_LEDS];

int pos = 0, posOld = 0;
bool dir = false, enabled = true;
uint32_t timer = millis() + MAX_SPD, switchSpeed = MAX_SPD, scoreAI = 0, scoreUSR = 0;
uint8_t part = 0, usrPos = 0;

void SetLed(uint8_t lenNo, uint32_t color);
void SetAllColor(uint32_t p);

void setup()
{
    Serial.begin(115200);

    randomSeed(analogRead(0));

    FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(50); // led brightness

    SetAllColor(OffColor);
}

void loop()
{
    // Run lights line---------------------------------------------------------------------
    if (millis() - timer > switchSpeed)
    {
        if (!dir)
        {
            enabled = true;

            if (pos != 0)
                SetLed(posOld, OffColor);

            SetLed(pos, WhiteColor);

            posOld = pos;
            pos++;

            if (pos == NUM_LEDS)
            {
                pos = NUM_LEDS - 1;
                dir = !dir;
                enabled = false;
                timer = millis() + switchSpeed;
            }
        }
        else
        {
            enabled = true;

            if (pos != NUM_LEDS - 1)
                SetLed(posOld, OffColor);

            SetLed(pos, WhiteColor);

            posOld = pos;
            pos--;

            if (pos < 0)
            {
                pos = 0;
                dir = !dir;
                enabled = false;
                timer = millis() + switchSpeed;
            }
        }

        if (enabled)
            timer = millis();
    }
    //-------------------------------------------------------------------------------------

    // check user input and process result-------------------------------------------------
    switch (part)
    {
    case 0: // generate new user position
        usrPos = random(0, NUM_LEDS);
        part++;

        break;
    case 1:
        SetLed(usrPos, BlueColor);

        if (Serial.available())
        {
            Serial.read();

            if (usrPos == pos)
            {
                Serial.print("You win. Score User/AI: ");

                switchSpeed += SPD_RESOLUTION;

                if (switchSpeed > MAX_SPD)
                    switchSpeed = MAX_SPD;

                Serial.println((String)++scoreUSR + "/" + (String)scoreAI + " Speed: " + (String)switchSpeed);

                for (size_t i = 0; i < BLINK_COUNTS * 2; i++)
                {
                    i % 2 ? SetAllColor(GreenColor) : SetAllColor(OffColor);

                    delay(BLINK_DELAY);
                }
            }
            else
            {
                Serial.print("You lose. Score User/AI: ");

                switchSpeed -= SPD_RESOLUTION;

                if (switchSpeed < MIN_SPD)
                    switchSpeed = MIN_SPD;

                Serial.println((String)scoreUSR + "/" + (String)++scoreAI + " Speed: " + (String)switchSpeed);

                for (size_t i = 0; i < BLINK_COUNTS * 2; i++)
                {
                    i % 2 ? SetAllColor(RedColor) : SetAllColor(OffColor);

                    delay(BLINK_DELAY);
                }
            }

            SetAllColor(OffColor);

            part = 0;
        }
        break;
        // case 2:
        //     break;
        // case 3:
        //     break;
        // case 4:
        //     break;
    }
    //-------------------------------------------------------------------------------------
}

void SetLed(uint8_t lenNo, uint32_t color)
{
    leds[lenNo] = color;
    FastLED.show();
}

void SetAllColor(uint32_t col)
{
    for (size_t i = 0; i < NUM_LEDS; i++)
    {
        SetLed(i, col);
        delay(1);
    }
}