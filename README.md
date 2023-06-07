# Avoid-Obstacles

The objective of the game is to navigate through a series of obstacles by controlling a LED using the buttons as controls. The LED of your character can avoid the obstacles by moving in the opposite direction of the obstacle when it appears. The player wins the game by staying alive for more than 15 seconds, and they lose if they collide with an obstacle. A sound will play to indicate the player's win or loss.

Rules:

1. At the start of the game, the character will be positioned at the bottom center of the CPX board.
2. The obstacles will appear at random positions and move towards the character from the top of the CPX board's LED grid.
3. The player can control the character's movement by pressing a button on the CPX board. Pressing the button will make the character move in the opposite direction of the approaching obstacle.
4. The character's movement is limited to the boundaries of the LED grid, and it cannot move beyond them.
5. The character's position and the obstacles' positions will be updated continuously based on user inputs and game logic.
6. If the character collides with an obstacle, the game ends, and a sound indicating loss will play.
7. If the player successfully avoids the obstacles and stays alive for more than 10 seconds, the game ends, and a sound indicating victory will play.

Inputs:

Buttons:
Function: Detects the button press.
0 (not pressed) or 1 (pressed)
Assigned Control: Left Button moves the LED to the left and Right Button moves the character to the right
Outputs:

LEDs:
Function: Display the character and obstacles on the CPX board.
Assigned Control: Visual representation of the game elements
Sound:
Function: Play sounds indicating victory or loss.
Assigned Control: Play tune for the player's win or loss

