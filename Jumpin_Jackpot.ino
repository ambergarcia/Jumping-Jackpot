// Jumpin Jackpot
// Amber Garcia
// October 23rd 2018

/*
A simple arcade jumprope game that relies on pressing the button in accordance with the looping lights.
The speed increases every level, and sounds are played for each.
*/

#include <Adafruit_CircuitPlayground.h>
#include "pitches.h" //Necessary to play sounds on the Adafruit
#include <Adafruit_NeoPixel.h>
int num_pixels = 10;
int ring_pin = 8;
Adafruit_NeoPixel ring = Adafruit_NeoPixel(num_pixels, ring_pin);

// List of colors for the program
int red = 0xFF0000;
int green = 0x00FF00;
int blue = 0x0000FF;
int yellow = 0xFFFF00;
int purple = 0xFF00FF;

int color_index = 0;
int colors[]= { blue, purple };
int num_colors = sizeof(colors)/sizeof(int);

// List of sounds by note and tempo for the program
int winner[] = {NOTE_B5, NOTE_A5, NOTE_C6, NOTE_G6, NOTE_C6, NOTE_E6};
int winner_tempo[] = {4,8,8,8,4,4};
int loser[] = {NOTE_C5, NOTE_B4, NOTE_A4, NOTE_C4, NOTE_B3};
int loser_tempo[] = {4,8,8,8,4};
int opening_theme[] = {NOTE_C4, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, NOTE_A5};
int open_tempo[] = { 4, 4, 8, 4, 8, 8, 8};
int levelup[] = {NOTE_C4,NOTE_A4,NOTE_B4,NOTE_C5};
int level_tempo[] = {4,8,8,4};

uint8_t openNotes = sizeof(opening_theme)/sizeof(int);
uint8_t levelNotes = sizeof(levelup)/sizeof(int);
uint8_t loserNotes = sizeof(loser)/sizeof(int);
uint8_t winnerNotes = sizeof(winner)/sizeof(int);

boolean game_over = false;
boolean win_lose = true;

void setup() {
  ring.begin();
  CircuitPlayground.begin();
}

void loop() {
  if(win_lose == true){
    Opening_Theme();
    start();
    win_lose = false;
  }
 // FIX ME: Move this so that it doesnt constantly repeat at the end
  while(game_over == false){

    jumpRope();

  }
}

int game_mode = 1;
int delayed = 500;

void jumpRope(){
      for (int which_color = 0; which_color < num_colors; which_color++){
          for(int which_pixel = 0; which_pixel < num_pixels; which_pixel++){

              ring.setPixelColor(which_pixel,colors[which_color]);
              ring.show();
              delay(delayed);
              if(CircuitPlayground.leftButton() == true){

                check(which_pixel);
                if(game_over == true){
                  ring.clear();
                  ring.show();
                  break;

                }
              }
              ring.clear();
       }
       if(game_over == true){
          ring.clear();
          ring.show();
          break;

       }
    }
}


void check(int pixel){
  // if the pixel is not at 9, then we need to create a game over scenario
  if(pixel == 9){

    for(int i = 0; i < num_pixels;i++){

       ring.setPixelColor(i,green);

    }
    ring.show();
    Level_Up();
    delay(2000);
    game_mode++;
    delayed = delayed - 100;

    if(delayed == 0){

      game_over = true;
      victory();

    }

    //lose

  }else{

    for(int i = 0; i < num_pixels;i++){

       ring.setPixelColor(i,red);

    }

    ring.show();
    Loser_Theme();
    delay(2000);
    game_mode = 1;
    delayed = 500;

    game_over = true;

  }

}
void Winner_Theme(){
    for (int n=0; n<winnerNotes; n++) {
      int noteDuration = 1000 / winner_tempo[n];
      CircuitPlayground.playTone(winner[n], noteDuration);
      delay(0.3*noteDuration);
    }
  }

void victory(){

  for(int i = 0; i < num_pixels;i++){

       ring.setPixelColor(i,yellow);
       ring.show();
       delay(200);
       ring.clear();

    }

   for(int i = 0; i < num_pixels;i++){

       ring.setPixelColor(i,yellow);

    }

    ring.show();
    Winner_Theme();
    delay(1000);
    ring.clear();

}

void start(){

  for(int i = 0; i < num_pixels;i++){

       ring.setPixelColor(i,blue);
       if( i + 1 < num_pixels ){

         ring.setPixelColor(i + 1,purple);

       }

       ring.show();
       delay(200);
       ring.clear();

    }

}

void Opening_Theme(){
    for (int n=0; n<openNotes; n++) {
      int noteDuration = 1000 / open_tempo[n];
      CircuitPlayground.playTone(opening_theme[n], noteDuration);
      delay(0.3*noteDuration);
    }
  }
void Level_Up(){
    for (int n=0; n<levelNotes; n++) {
      int noteDuration = 1000 / level_tempo[n];
      CircuitPlayground.playTone(levelup[n], noteDuration);
      delay(0.3*noteDuration);
    }
  }

void Loser_Theme(){
    for (int n=0; n<loserNotes; n++) {
      int noteDuration = 1000 / loser_tempo[n];
      CircuitPlayground.playTone(loser[n], noteDuration);
      delay(0.3*noteDuration);
    }
  }
