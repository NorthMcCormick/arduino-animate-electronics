#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define MOTOR_PIN   7
#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    50

CRGB leds[NUM_LEDS];


bool gReverseDirection = false;

CRGBPalette16 gPal;

#define BRIGHTNESS          150
#define FRAMES_PER_SECOND  40

CRGB colorWarning = CRGB( 255, 255, 0);
CRGB colorSuccess = CRGB( 0, 255, 0);
CRGB colorError = CRGB(2550, 0, 0);
CRGB colorInfo = CRGB( 0, 0, 255);
CRGB colorLightning = CRGB(210, 210, 255);
CRGB colorBlack = CRGB(0, 0, 0);
CRGB colorPurple = CRGB(150, 0, 190);

bool lightsGoing = false;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT); //Set pin 3 as an OUTPUT
  FastLED.clear();

  delay(1000); // 3 second delay for recovery

  analogWrite(MOTOR_PIN, 255  );  

  gPal = HeatColors_p;
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.clear();
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { drawAnimation, bpm, rainbow, rainbowWithGlitter, confetti, sinelon, juggle };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

// Status 0 = starting
int system_status = 0;


// animation A - Blue to black fast
int a_finished = 0;
int a_fade = 21;

bool b_finished = false; // To red

bool c_finished = false; // Fade to black after lightning
int c_fade = 30;

int b_1_finished = false;
int b_1b_finished = false;

int b_2_finished = false;
int b_2b_finished = false;

int d_finished = 0; // 1st lightning
int g_finished = 0; // 2nd lightning
int h_finished = 0; // 3rd lightning

int i_finished = 0; // 4th lightning
int j_finished = 0; // 5th lightning
int k_finished = 0; // 6th lightning

int o_finished = 0; // 1st lightning

int l_finished = 0; // green light

int n_finished = 0; // end red light

bool e_finished = false;

int f_finished = 0; // the next strobe

int m_finished = 0; // Red strobe

#define STAGE_LED_COUNT 22

int leds_stage[STAGE_LED_COUNT] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 };

#define BACKGROUND_LED_COUNT 7

int leds_background[BACKGROUND_LED_COUNT] = { 49, 48, 47, 46, 45, 44, 43 };

int a_beat = 561;
int startBeat = 3550;


unsigned long variableOffset = 0;

void loop()
{
  random16_add_entropy(random());

  // Call the current pattern function once, updating the 'leds' array
  //gPatterns[gCurrentPatternNumber]();

  // do some periodic updates
  // EVERY_N_MILLISECONDS( 15 ) { 
    // gHue++;
  // } // slowly cycle the "base color" through the rainbow
  // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically

  // EVERY_N_MILLISECONDS( 15 ) { 
  //   analogWrite(MOTOR_PIN, 100);
  // }

  /*EVERY_N_MILLISECONDS(1000/FRAMES_PER_SECOND) {
    leds[0] = CRGB(0, gHue, 0);

    FastLED.show();  

    gHue++;
    // drawAnimation();
  }*/

  unsigned long ms = millis();
  
  /*if (leds[0].b == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b = 255;
    }
  }*/


  // Fire2012WithPalette(); 

  if (ms >= startBeat && a_finished == 0) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }

      a_finished++;
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 1) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 2) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 3) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 4) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 5) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 6) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 7) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 8) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 9) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 10) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 11) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 12) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 13) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 14) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + (a_beat * a_finished) && a_finished == 15) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      a_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  variableOffset = (a_beat * 15);

  // NEXT ALL RED
  if (ms >= startBeat + variableOffset && !b_finished) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 255;
      leds[leds_stage[i]].g = 0;
      leds[leds_stage[i]].b = 0;
    }
    
    b_finished = true;
  }

  // first Lightning
  variableOffset += 9700;

  // Background
  if (ms > startBeat + variableOffset && !b_1_finished) {
    for (int i = 0; i < BACKGROUND_LED_COUNT; i++) {
      leds[leds_background[i]] = colorPurple;
    }

    b_1_finished = true;
  }

  if (ms >= startBeat + variableOffset && d_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    d_finished++;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && d_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    d_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && d_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    d_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && d_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    d_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && d_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    d_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && d_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      d_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
        leds[leds_stage[i]].g = 0;
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  variableOffset += 6500;

  // Second lightning
  if (ms >= startBeat + variableOffset && g_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    g_finished++;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && g_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    g_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && g_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    g_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && g_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    g_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && g_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    g_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && g_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      g_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
        leds[leds_stage[i]].g = 0;
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  variableOffset += 8600;

  // Third lightning
  if (ms >= startBeat + variableOffset && h_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    h_finished++;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && h_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    h_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && h_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    h_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && h_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    h_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && h_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    h_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && h_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]] = colorBlack;
      }

      for (int i = 0; i < BACKGROUND_LED_COUNT; i++) {
        leds[leds_background[i]] = colorBlack;
      }
    }
  }

  // Background
  if (ms >= startBeat + variableOffset && !b_1b_finished) {
    for (int i = 0; i < BACKGROUND_LED_COUNT; i++) {
      leds[leds_background[i]] = colorBlack;
    }

    b_1b_finished = true;
  }


  variableOffset += 6000;

  // Orange candle glow
  if (ms >= startBeat + variableOffset && ms <= startBeat + variableOffset + 18900) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = random(160, 240);
      leds[leds_stage[i]].g = random(110, 145);
      leds[leds_stage[i]].b = 0;
    }
  }

  variableOffset += 19000;

  // Candle fade out
  if (ms >= startBeat + variableOffset && e_finished == false) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      e_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]] = colorBlack;
      }
    }
  }

  variableOffset += 13500;

  if (ms >= startBeat + variableOffset && f_finished == 0) {
    if (leds[0].b <= 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }

      f_finished++;
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 1) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 2) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 3) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 4) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 5) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 6) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 7) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 8) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 9) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 10) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 11) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 12) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 13) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 14) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * f_finished) && f_finished == 15) {
    if (leds[0].b == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].b -= a_fade;
    }

    if (leds[0].b <= a_fade) {
      f_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  variableOffset += (a_beat * f_finished);

  variableOffset += 4300;

  // Fourth lightning
  if (ms >= startBeat + variableOffset && i_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    i_finished++;
  }

  // Background
  if (ms > startBeat + variableOffset && !b_2_finished) {
    for (int i = 0; i < BACKGROUND_LED_COUNT; i++) {
      leds[leds_background[i]] = colorPurple;
    }

    b_2_finished = true;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && i_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    i_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && i_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    i_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && i_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    i_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && i_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    i_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && i_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      i_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
        leds[leds_stage[i]].g = 0;
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  variableOffset += 4400;

  // Fifth lightning
  if (ms >= startBeat + variableOffset && j_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    j_finished++;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && j_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    j_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && j_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    j_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && j_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    j_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && j_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    j_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && j_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      j_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
        leds[leds_stage[i]].g = 0;
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  variableOffset += 3500;

  // Sixth lightning
  if (ms >= startBeat + variableOffset && k_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    k_finished++;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && k_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    k_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && k_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    k_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && k_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    k_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && k_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    k_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && k_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      k_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
        leds[leds_stage[i]].g = 0;
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  // Background
  if (ms >= startBeat + variableOffset && !b_2b_finished) {
    for (int i = 0; i < BACKGROUND_LED_COUNT; i++) {
      leds[leds_background[i]] = colorBlack;
    }

    b_2b_finished = true;
  }

  variableOffset += 2500;

  // NEXT ALL green
  if (ms >= startBeat + variableOffset && l_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 0;
      leds[leds_stage[i]].g = 255;
      leds[leds_stage[i]].b = 0;
    }
    
    l_finished++;
  }

  variableOffset += 36000;

  // NEXT ALL green
  if (ms >= startBeat + variableOffset && l_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 0;
      leds[leds_stage[i]].g = 0;
      leds[leds_stage[i]].b = 0;
    }
    
    l_finished++;
  }

  variableOffset += 10000;

  // NEXT ALL red
  if (ms >= startBeat + variableOffset && l_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 255;
      leds[leds_stage[i]].g = 0;
      leds[leds_stage[i]].b = 0;
    }
    
    l_finished++;
  }

  variableOffset += 30000;

  // NEXT all black
  /*if (ms >= startBeat + variableOffset && l_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 0;
      leds[leds_stage[i]].g = 0;
      leds[leds_stage[i]].b = 0;
    }
    
    l_finished++;
  }*/

  // Next red pulse
  variableOffset += 14500;

  if (ms >= startBeat + variableOffset && h_finished == 0) {
    if (leds[0].r <= 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }

      h_finished++;
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 1) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 2) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 3) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 4) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 5) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 6) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 7) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 8) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 9) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 10) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 11) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 12) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 13) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 14) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  if (ms >= startBeat + variableOffset + (a_beat * h_finished) && h_finished == 15) {
    if (leds[0].r == 0) {
      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 255;
      }
    }

    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= a_fade;
    }

    if (leds[0].r <= a_fade) {
      h_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
      }
    }
  }

  variableOffset += (a_beat * h_finished);


  // NEXT ALL RED
  if (ms >= startBeat + variableOffset && n_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 255;
      leds[leds_stage[i]].g = 0;
      leds[leds_stage[i]].b = 0;
    }
    
    n_finished++;
  }

  // seventh Lightning
  variableOffset += 9700;

  if (ms >= startBeat + variableOffset && o_finished == 0) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    o_finished++;
  }

  variableOffset += 100;

  if (ms >= startBeat + variableOffset && o_finished == 1) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    o_finished++;
  }

  variableOffset += 120;

  if (ms >= startBeat + variableOffset && o_finished == 2) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    o_finished++;
  }

  variableOffset += 170;

  if (ms >= startBeat + variableOffset && o_finished == 3) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorBlack;
    }

    o_finished++;
  }

  variableOffset += 90;

  if (ms >= startBeat + variableOffset && o_finished == 4) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]] = colorLightning;
    }

    o_finished++;
  }

  variableOffset += 120;

  // Lightning fade out
  if (ms >= startBeat + variableOffset && o_finished == 5) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r -= c_fade;
      leds[leds_stage[i]].g -= c_fade;
      leds[leds_stage[i]].b -= c_fade;
    }

    if (leds[leds_stage[0]].b <= c_fade) {
      o_finished++;

      for (int i = 0; i < STAGE_LED_COUNT; i++) {
        leds[leds_stage[i]].r = 0;
        leds[leds_stage[i]].g = 0;
        leds[leds_stage[i]].b = 0;
      }
    }
  }

  // NEXT ALL WHITE
  /*if (ms >= startBeat + variableOffset && !c_finished) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 0;
      leds[leds_stage[i]].g = 0;
      leds[leds_stage[i]].b = 0;
    }
    
    c_finished = true;
  }

  variableOffset += 17000;

  // NEXT ALL WHITE
  if (ms >= startBeat + variableOffset && !d_finished) {
    for (int i = 0; i < STAGE_LED_COUNT; i++) {
      leds[leds_stage[i]].r = 10;
      leds[leds_stage[i]].g = 10;
      leds[leds_stage[i]].b = 10;
    }
    
    d_finished = true;
  }*/ 

  FastLED.show();  


  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void drawAnimation() {
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 1);
  
  for(int i = 0; i <= 15; i++) {
    leds[i] = CRGB::Black;
  }
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}


// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
#define COOLING  70

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 100

/*void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
  static byte heat[STAGE_LED_COUNT];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < STAGE_LED_COUNT; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / STAGE_LED_COUNT) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= STAGE_LED_COUNT - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 4;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < STAGE_LED_COUNT; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (STAGE_LED_COUNT-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[leds_stage[pixelnumber]] = color;
    }
}*/