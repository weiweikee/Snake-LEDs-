const byte dim_curve[] = {
  0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
  4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
  6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
  8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
  11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
  15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
  20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
  27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
  36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
  48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
  63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
  83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
  110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
  146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
  193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};


#include <Adafruit_NeoPixel.h>
#include "Keyboard.h"

int NUM_LEDS = 32; // Height = 4, Width = 8
int LED_PIN = 6;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int rgb_colors[3]; // recieves the results from hsb conversion


unsigned long lastTime = 0;
unsigned long moveTime = 0;
unsigned long nameTime = 0;

int a = 1;
int b = 7;

int offset = 0;

int state = 0;

char serialStuff = 's';

int eat = 0;

int numSnake = 31;

unsigned long currentTime = 0;

int s;

byte matrix[4][8] =
{
  { 0,  1,  2,  3,  4,  5,  6,  7},
  { 8,  9, 10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23},
  {24, 25, 26, 27, 28, 29, 30, 31}
};



unsigned int SnakeGrid1[3][10] = {
  // Y (Rows) // 0-3
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  // X (Cols) // 0-7
  {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  // Boolean (on or off)
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};


bool W[4][35] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0}
};

bool L[4][51] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
  { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0}
};


void setup() {
  pixels.begin();
  Serial.begin(9600);
  Keyboard.begin();

}

void loop()  {
  currentTime = millis();
  pixels.clear();
  switch (state) {
    case 0:
      snake();
      food();
      break;
    case 1:
      gameOver();
      break;
    case 2:
      youWin();
      break;
    default:
      break;
  }

  if (Serial.available() > 0) {
    serialStuff = char(Serial.read());
    Serial.println(serialStuff);
  }


  if (currentTime - lastTime >= 10000) {
    if (state == 1 || state == 2) {
      state = 0;
      eat = 0;
      SnakeGrid1[0][0] = 1;
      SnakeGrid1[1][0] = 3;
      for (int n = 1; n < 32; n++) {
        SnakeGrid1[0][n] = 0;
        SnakeGrid1[1][n] = 0;
      }
    }
  }



  if (eat == 6 && state == 0) {
    s = int(random(1, 3));
    lastTime = currentTime;
    if (s = 1) {
      state = s;
    }
    else if (s = 2) {
      state = s;
    }
  }
  pixels.show();
}

void snake() {

  for (int j = 0; j < 9; j++) {

    int x = SnakeGrid1[0][j];
    int y = SnakeGrid1[1][j];


    if (SnakeGrid1[2][j] == 1) {
      pixels.setPixelColor(matrix[x][y], pixels.Color(255, 0, 0));
    }

    // food random
    if (a == x && b == y) {
      a = int(random(0, 4));
      b = int(random(0, 8));
      eat++;
    }
  }
  Serial.print(eat);

  if (currentTime - moveTime > 500) {
    for (int n = 9; n >= 1; n--) {
      SnakeGrid1[0][n] = SnakeGrid1[0][n - 1];
      SnakeGrid1[1][n] = SnakeGrid1[1][n - 1];
    }
  }

  SnakeGrid1[2][eat] = 1;


  // move
  if (serialStuff == 's') { // down
    if (currentTime - moveTime > 500) {
      SnakeGrid1[0][0] = SnakeGrid1[0][0] + 1;
      SnakeGrid1[0][0] = SnakeGrid1[0][0] % 4;
      moveTime = currentTime;
    }
  }

  if (serialStuff == 'w') { // up
    if (currentTime - moveTime > 500) {
      SnakeGrid1[0][0] = SnakeGrid1[0][0] - 1;
      SnakeGrid1[0][0] = abs(SnakeGrid1[0][0] % 4);
      moveTime = currentTime;
    }
  }

  if (serialStuff == 'a') { // left
    if (currentTime - moveTime > 500) {
      SnakeGrid1[1][0] = SnakeGrid1[1][0] - 1;
      SnakeGrid1[1][0] = abs(SnakeGrid1[1][0] % 8);
      moveTime = currentTime;
    }
  }

  if (serialStuff == 'd') { // right
    if (currentTime - moveTime > 500) {
      SnakeGrid1[1][0] = SnakeGrid1[1][0] + 1;
      SnakeGrid1[1][0] = SnakeGrid1[1][0] % 8;
      moveTime = currentTime;
    }
  }
}
void gameOver() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      if (L[j][(i + offset) % 51]) { // modulo to not get out of bound in array. // check boolean too.
        pixels.setPixelColor(matrix[j][i], pixels.Color(255, 0, 0));
      }
    }
    if (currentTime - nameTime > 200) {
      offset++;
      if (offset > 51) offset = 0;
      nameTime = currentTime;
    }
  }
}

void youWin() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      if (W[j][(i + offset) % 35]) { // modulo to not get out of bound in array. // check boolean too.
        pixels.setPixelColor(matrix[j][i], pixels.Color(0, 255, 0));
      }
    }
    if (currentTime - nameTime > 200) {
      offset++;
      if (offset > 35) offset = 0;
      nameTime = currentTime;
    }
  }
}

void food() {
  pixels.setPixelColor(matrix[a][b], pixels.Color(0, 255, 0));
}

