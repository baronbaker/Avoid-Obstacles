#include <Adafruit_CircuitPlayground.h>

// Game states
enum GameState {
  START,
  GAME_RUNNING,
  GAME_OVER
};

// Constants
const int CHARACTER_SPEED = 1; // Adjust character movement speed as desired
const int VICTORY_DURATION = 10000; // Duration to stay alive for victory (in milliseconds)
const int OBSTACLE_INTERVAL = 3000; // Interval for obstacle position update (in milliseconds)

// Variables
int characterPosition;
int obstaclePosition;
unsigned long gameTimer;
unsigned long victoryTimer;
unsigned long obstacleTimer;
float midi[128];
int A_four = 440;
GameState gameState;
volatile bool ending;

// MIDI notes for winning and losing tunes
int victoryTune[8][2] = {
  {60, 100},
  {61, 100},
  {62, 100},
  {63, 100},
  {65, 100},
  {67, 100},
  {69, 100},
  {71, 300},
};

int lossTune[4][2] = {
  {60, 100},
  {58, 100},
  {57, 100},
  {54, 300},
};

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  gameState = START;
  generateMIDI();
}

void loop() {
  switch (gameState) {
    case START:
      startGame();
      break;
    case GAME_RUNNING:
      updateGame();
      break;
    case GAME_OVER:
      endGame();
      break;
  }
}

void startGame() {
  characterPosition = 4; // Start in the middle of the LED grid
  obstaclePosition = random(10); // Spawn the obstacle at a random position
  gameTimer = millis();
  victoryTimer = 0;
  obstacleTimer = millis();

  CircuitPlayground.clearPixels();
  CircuitPlayground.setPixelColor(characterPosition, 0, 255, 0);
  CircuitPlayground.setPixelColor(obstaclePosition, 255, 0, 0);

  gameState = GAME_RUNNING;
}

void updateGame() {
  unsigned long currentMillis = millis();

  // Move character based on button input
  if (CircuitPlayground.leftButton() && characterPosition > 0) {
    CircuitPlayground.setPixelColor(characterPosition, 0);
    characterPosition -= CHARACTER_SPEED;
    delay(200);
  }
  else if (CircuitPlayground.leftButton() && characterPosition == 0) {
    CircuitPlayground.setPixelColor(characterPosition, 0);
    characterPosition = 9;
    delay(200);
  }
  if (CircuitPlayground.rightButton() && characterPosition < 9) {
    CircuitPlayground.setPixelColor(characterPosition, 0);
    characterPosition += CHARACTER_SPEED;
    delay(200);
  }
  else if (CircuitPlayground.rightButton() && characterPosition == 9) {
    CircuitPlayground.setPixelColor(characterPosition, 0);
    characterPosition = 0;
    delay(200);
  }

  // Update obstacle position periodically
  if (currentMillis - obstacleTimer >= OBSTACLE_INTERVAL) {
    CircuitPlayground.setPixelColor(obstaclePosition, 0);
    obstaclePosition = random(10);
    obstacleTimer = currentMillis;
  }

  // Check for collision
  if (characterPosition == obstaclePosition) {
    gameState = GAME_OVER; // Collision with obstacle, game over
    ending = false;
  }

  if (currentMillis - gameTimer >= VICTORY_DURATION) {
    victoryTimer = currentMillis;
    ending = true;
  }

  CircuitPlayground.setPixelColor(characterPosition, 0, 255, 0);
  CircuitPlayground.setPixelColor(obstaclePosition, 255, 0, 0);
}

void endGame() {
  CircuitPlayground.clearPixels();

  // Play sound based on game outcome
  if (ending) {
      for(int i = 0; i < sizeof(victoryTune) / sizeof(victoryTune[0]); i++) {
        CircuitPlayground.playTone(midi[victoryTune[i][0]], victoryTune[i][1]);
        delay(1);
      } // Victory sound
  } else {
    for(int i = 0; i < sizeof(lossTune) / sizeof(lossTune[0]); i++) {
        CircuitPlayground.playTone(midi[lossTune[i][0]], lossTune[i][1]);
        delay(1);
      } // Loss sound
  }

  // Wait for a short duration before restarting the game
  delay(500);

  gameState = START;
}

void generateMIDI() {
  for (int x = 0; x < 128; ++x) {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
