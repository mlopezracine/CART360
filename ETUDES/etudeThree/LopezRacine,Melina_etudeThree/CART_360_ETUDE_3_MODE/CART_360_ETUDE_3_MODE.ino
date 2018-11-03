/**********************ETUDE 2 CART 360 2017*******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (5 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  looper   ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_R 9 // R PIN
#define LED_PIN_G 6 // G PIN
#define LED_PIN_B 5 // B PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// a constant for duration
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 11 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
  // Initiate digitalRead to pin 2, to a button pressed
  int BUTTON_PRESSED = digitalRead(BUTTON_MODE_PIN);
  if(BUTTON_PRESSED == HIGH){  // If the button is pressed, 
    mode ++;                   // then add + 1 to the mode counter
    //Serial.println(mode);
    delay(500);

    // Reset the counter to 0, if it is higher than 4
    if(mode > 4){
      mode = 0;
    }
  }
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
  switch (mode) {
    //if the mode is 1 - RGB LED IS BLUE
    case 1:
    digitalWrite(LED_PIN_B, HIGH); // blue is on
    digitalWrite(LED_PIN_R, LOW);  // red is off
    digitalWrite(LED_PIN_G, LOW);  // green is off
    delay(100);                    // Delays were added to have time seeing each color of the LED
    break;

    // if the mode is 2 - RGB LED IS RED
    case 2:
    digitalWrite(LED_PIN_R, HIGH); // red is on
    digitalWrite(LED_PIN_B, LOW);  // blue is off
    digitalWrite(LED_PIN_G, LOW);  // green is off
    delay(100);
    break;

    // if the mode is 3 - RGB LED IS GREEN
    case 3:
    digitalWrite(LED_PIN_G, HIGH); // green is on
    digitalWrite(LED_PIN_R, LOW);  // red is off
    digitalWrite(LED_PIN_B, LOW);  // blue is off
    delay(100);
    break;

    // if the mode is 4 - RGB LED IS PURPLE
    case 4:                        // To obtain the color purple, both red and blue LED needs to be HIGH
    digitalWrite(LED_PIN_B, HIGH); // blue is on
    digitalWrite(LED_PIN_R, HIGH); // red is on
    digitalWrite(LED_PIN_G, LOW);  // green is off
    delay(100);
    break;

    // if the mode is 0 - RGB LED IS OFF
    default:
    digitalWrite(LED_PIN_R, LOW);  // red is off
    digitalWrite(LED_PIN_B, LOW);  // blue is off
    digitalWrite(LED_PIN_G, LOW);  // green is off
    break;
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode == 0) { 
    reset();
  }
  else if(mode == 1) {
    live();
  }
  else if(mode == 2) {
    record();
  }
  
  else if(mode == 3) {
    play();
  }
   
   else if(mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // Reset the program from the beginning
  // asm volatile ("jmp 0"); 
    /* Altough it is a "cheap" solution to the problem (lign above),
     * if no value are stored or used at different "reset" of the program,  
     * it does work and reset the program from the beginning.
     * It will automatically erase all values in arrays, 
     * since it forces the Arduino to restart the program. 
     * Another way would have to press the reset button directly attached to the Arduino.
     */

  // Erase values in arrays
  for( int i = 0; i < countNotes;  ++i ){
    notes[i] = 0;
    }
    // Reset the counter to 0
    countNotes = 0;
  
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
    if(analogRead(NOTE_IN_PIN) == 7){      // If the input from the analog is equal to 7
      tone(BUZZER_PIN, 10, duration); 
      }
    
    if(analogRead(NOTE_IN_PIN) == 82){     // If the input from the analog is equal to 82
      tone(BUZZER_PIN, 50, duration);
      }
      
    if(analogRead(NOTE_IN_PIN) == 484){     // If the input from the analog is equal to 484
      tone(BUZZER_PIN, 90, duration);
      }
      
    if(analogRead(NOTE_IN_PIN) == 930){     // If the input from the analog is equal to 930
      tone(BUZZER_PIN, 130, duration);
      }
      
    if(analogRead(NOTE_IN_PIN) == 1023){    // If the input from the analog is equal to 1023
      tone(BUZZER_PIN, 170, duration);
      }
}
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  /* Record mode reuse the same code (analogRead(NOTES_IN_PIN) from the live function
   * The main difference is that if the countNotes is less than the predefined constant for max number of notes in array,
   * then the exact note that was just played is stored in the array.
   * The countNotes goes 1 higher.
   * If the constant countNotes reachs the max number of notes in array, then the recording stops.
   */
  if(countNotes < MAX_NOTES){              // If the MAX_NOTES isn't yet reach, continue recording.
   if(analogRead(NOTE_IN_PIN) == 7){       // If the input from the analog is equal to 7
      tone(BUZZER_PIN, 10, duration);
      // Store the  note (at value 10) in the array
      notes[countNotes] = 10;
      // Add + 1 to the counter 
      countNotes++;
      }
    
    if(analogRead(NOTE_IN_PIN) == 82){      // If the input from the analog is equal to 82
      tone(BUZZER_PIN, 50, duration);
      // Store the  note (at value 50) in the array
      notes[countNotes] = 50;
      // Add + 1 to the counter 
      countNotes++;
      }
      
    if(analogRead(NOTE_IN_PIN) == 484){     // If the input from the analog is equal to 484
      tone(BUZZER_PIN, 90, duration);
      // Store the note (at value 90) in the array
      notes[countNotes] = 90;
      // Add + 1 to the counter 
      countNotes++;
      }
      
    if(analogRead(NOTE_IN_PIN) == 930){     // If the input from the analog is equal to 930
      tone(BUZZER_PIN, 130, duration);
      // Store the note (at value 130) in the array
      notes[countNotes] = 130;
      // Add + 1 to the counter 
      countNotes++;
      }
      
    if(analogRead(NOTE_IN_PIN) == 1023){     // If the input from the analog is equal to 1023
      tone(BUZZER_PIN, 170, duration);
      // Store the note (at value 170) in the array
      notes[countNotes] = 170;
      // Add + 1 to the counter 
      countNotes++;
      }
  }
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  for(int i = 0; i < countNotes; i++) {
    tone(BUZZER_PIN, notes[i], duration);
    delay(500);
    }
}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper()
{
  for(int i = 0; i < countNotes; i++) {           
    // Play a note from the array from a pseudo-random sequence
    tone(BUZZER_PIN, notes[random(i)], duration);  // For each note in the array, the function looper() plays them accordingly to the random function
    delay(500);
    }
}

/**************************************************************************/


/******************PART THREE: SHORT ANSWER*******************************
 * Selon la formation en "escalier" du circuit, les boutons sont reliés à une série de résistances (resistors) 
 * qui agissent en tant que diviseur de tension résistif (voltage divider).
 * Ainsi, chaque bouton reçoit une fraction du courant (voltage) passant.
 * Un circuit en escalier permet de mesurer la "quantité" que chaque bouton reçoit. 
 * L'ensemble du circuit (avec les boutons) se partage une seule pin.
 * De cette manière, en fractionnant le courant, une valeur pour chaque élément permet d'être quantifié. 
 * Chaque note peut être enregistrer selon la valeur de courant passant à travers la pin.
 * C'est pour cette raison que (analogRead(NOTE_IN_PIN) == (valeur int)) est utilisé pour ensuite assigner une tonalité.
 * La tonalité est assignée selon la fonction tone(BUZZER_PIN, NOTE_(numéro de note), duration). BUZZER_PIN étant la constante pour le buzzer, un output, 
 * tandis que duration est une constante prédéfinie en milliseconde pour le temps de la duration de la tonalité.
 * Les notes ont été predéfinies dans le fichier supplémentaire pitches.h
 * 
 * Un buzzer a été intégré dans le circuit pour entendre les tonalités effectuées à chaque interaction.
 * Selon la platform web Arduino.cc (https://www.arduino.cc/), la fonction tone() génère une onde carrée d'une certaine fréquence sur une pin.
 * Ainsi, avec l'addition du ficher supplémentaire pitches.h (PART TWO), le pitch est modifié pour obtenir des notes distintes. 
 * La fréquence est modifiée, affectant par le fait-même l'onde créée par la fonction.
 * 
 * Pour sélectionner un mode, l'utilisateur doit appuyer sur le bouton désigné. 
 * Ainsi, la constante "mode" augmente sa valeur de + 1 à chaque interaction. 
 * La valeur de la constante varie selon l'interaction, jusqu'à un maximum de 5 soit le nombre de modes disponibles à l'utilisateur.
 * J'ai spécifié 5 modes, puisque le mode 0 permet de "reset" les valeurs de l'array. 
 * Dans la fonction selectMode(), chaque mode a été associé à une valeur.
 * De ce manière, le mode 0 permet d'accéder à la fonction reset(), le mode 1 permet d'accéder à la fonction live(), le mode 2 permet d'accéder à la fonction record(),
 * le mode 3 permet d'accéder à la fonction play(), et le mode 4 permet d'accéder à la fonction looper().
 * Chaque function accomplit une tâche particulière dans le programme.
 * Selon les variables de la constante "mode", un switch case construct permet d'actionner un LED. 
 * Chaque mode a été associé à une couleur, permettant par le fait-même d''aviser l'utilisateur de la fonction sélectionner à chaque interaction avec le bouton.
 * 
 *******************DISCLAMER*********************************************
 * Je me suis référée aux matériels accesibles sur https://www.arduino.cc/ , plus particulièrement ce tutoriel (https://www.arduino.cc/en/Tutorial/toneMelody) pour la fonction tone() 
 * et le fichier supplémentaire pitches.h,
 * ainsi que le texte de référence Arduino sur la fonction tone()(https://www.arduino.cc/reference/en/language/functions/advanced-io/tone/).
 * De plus, j'ai cherché de l'information supplémentaire sur Wikipédie (Resistor ladder, https://en.wikipedia.org/wiki/Resistor_ladder) pour mieux comprendre le fonctionnement du circuit.
 * Pour m'aider à résoudre les parties de codes manquants, j'ai fait appel à Sabine pour obtenir des explications et de l'aide, ce qui m'a permis de réaliser ce programme.
*/
