#include "mbed.h"
#include "stdlib.h"
#include "iostream"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include <math.h>


// LCD 
uLCD_4DGL uLCD(p13,p14,p12);

// BOOLEAN VALUES TO CONTROL WHICH GAME IS PLAYED && GAME OVER
bool ledGame = false;
bool binGame = false;
bool distanceGame = false;
bool patternGame = false;
bool Game_Over = false;


// index value to refernce game array called 'GAMES'
int gameIndex = 0;
int prev = -1;

// lives && points
int lives = 5;
int score = 0;
int highscore = 0;

// game array called 'GAMES' where each bool tells us if the game is active
bool GAMES [4] = {ledGame,binGame,distanceGame,patternGame};

// Submission button
PinDetect submit(p5);


// VARIABLES NEEDED FOR LED GAME

// USER INPUTED RGB VALUES
AnalogIn redPot(p18);
AnalogIn greenPot(p19);
AnalogIn bluePot(p20);
PwmOut red(p26);
PwmOut green(p25);
PwmOut blue(p24);

// RGB VALUES THAT ARE RANDOMLY ASSIGNED

PwmOut red2(p23);
PwmOut green2(p22);
PwmOut blue2(p21);

// Push Buttons
PinDetect pb1(p6);
PinDetect pb2(p7);
PinDetect pb3(p8);
PinDetect pb4(p9);

// VARIABLES FOR DISTANCE GAME
DigitalOut trigger(p29);
DigitalIn  echo(p30);
int dist = 0;
int correction = 0;
int target_dist = 0;
Timer sonar;

// VARIABLES FOR PATTERN
bool redP = false;
bool blueP = false;
bool greenP = false;
bool yellowP = false;
bool colors [4] = {redP,blueP,greenP,yellowP};

// FUNCTIONS FOR PATTERN

void drawRed(){
    uLCD.filled_circle(30 , 30 , 20, 0xFF0000);
}

void drawBlue(){
    uLCD.filled_circle(96 , 30 , 20, 0x0000FF);
}

void drawGreen(){
    uLCD.filled_circle(30 , 96 , 20, 0x00FF00);
}

void drawYellow(){
    uLCD.filled_circle(96 , 96 , 20, 0xFFFF00);
}
void checkTrue(){
    if(colors[0] == true){
        drawRed(); 
        colors[0] = false; 
        wait(1); 
        uLCD.cls();
        wait(0.5);
    }
    if(colors[1] == true){
        drawBlue(); 
        colors[1] = false; 
        wait(1); 
        uLCD.cls();
        wait(0.5);
    }
    if(colors[2] == true){
        drawGreen(); 
        colors[2] = false; 
        wait(1); 
        uLCD.cls();
        wait(0.5);
    }
    if(colors[3] == true){
        drawYellow(); 
        colors[3] = false; 
        wait(1); 
        uLCD.cls();
        wait(0.5);
    }
}

int main() {
    srand (time(NULL));
    
    // push buttons pull up
    submit.mode(PullUp);
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    pb3.mode(PullUp);
    pb4.mode(PullUp);
    
    ////// SONAR SETUP //////
    //check if the values from the distance sensor match valu randomly chosen
    //if correct set GAMES[3] = false;
    sonar.reset();
    // measure actual software polling timer delays
    // delay used later in time correction
    // start timer
    sonar.start();
    // min software polling delay to read echo pin
    while (echo==2) {};
    // stop timer
    sonar.stop();
    // read timer
    correction = sonar.read_us();
    /////// END SONAR SETUP //////
    
    //// INTRO SCREEN /////
    while(1){
        uLCD.text_string("  ECE 4180  ", '\x03', '\x04', FONT_7X8, 0xFF0000);
        uLCD.text_string("THE GAME BOX", '\x03', '\x06', FONT_7X8, 0xFF0000);
        uLCD.text_string("Press Submit", '\x03', '\x08', FONT_7X8, 0xFF0000);
        uLCD.text_string("To Start", '\x05', '\x09', FONT_7X8, 0xFF0000);
        if(!submit){break;}
    }    
    uLCD.cls();
    uLCD.locate(0,0);
    uLCD.color(GREEN);
    
    // This is the large GAME while loop. Essentially, this while loop checks which game has been randomly chosen to begin. 
    while(1) {
        //game is randomly chosen
        int game;
        if (!Game_Over){
            while(1){
                game = rand() % 4;
                if(game != prev){break;}
            }
            gameIndex = game;
            prev = game;
            GAMES[gameIndex] = true; //now only one game in our GAMES array is true. This means only one of the minigame while loops below run.*/
        }
        
        //RGB VALUES RANDOMLY CHOSEN AND SEND TO THE GAME'S LED
        float CPURED = (rand()% 11)/10.0;
        float CPUBLUE = (rand()% 11)/10.0;
        float CPUGREEN = (rand()% 11)/10.0;
        
        
        //BINGAME
        int bin2 = rand() % 16;
        int userBin [4] = {0,0,0,0};
        int convertedInput = 0;
        
        //DISTANCE RANDOMLY CHOSEN
        while(1){
        target_dist = rand() % 21;
        if (target_dist > 5){break;}
        }
        
        //PATTERN GAME VARIABLES
        int inputPattern [6] = {0,0,0,0,0,0};
        int pattern [6] = {0,0,0,0,0,0};
        int i = 0;
        int num;
        while(i<6){
            num = rand() % 4;
            pattern[i] = num;
            i++;
        }
        
        // this is the while loop for the minigame ledgame
        while(GAMES[0] && !Game_Over)
        {
            // score screen
            uLCD.printf("You have %d lives! \n\r",lives);
            uLCD.printf("\nScore: %d \n\r",score);
            uLCD.printf("\nHighscore: %d \n\r",highscore);
            wait(2);
            uLCD.cls();
            // game presentation screen
            uLCD.locate(4,2);
            uLCD.color(0xF74BFE);
            uLCD.printf("COLOR GAME");
            uLCD.locate(2,6);
            uLCD.color(GREEN);
            uLCD.printf("Match the Color!");
            uLCD.color(GREEN);
            uLCD.locate(0,0);
            red2 = CPURED;
            blue2 = CPUBLUE;
            green2 = CPUGREEN;
            while(1){
                // assign pot values to RGB
                red = redPot; 
                green = greenPot;
                blue = bluePot;
                
                float USERRED = red;
            
                float USERBLUE = blue;
            
                float USERGREEN = green;
                // check if input within range
                if ( !submit && USERRED < CPURED + .4 && USERRED > CPURED - .4 
                && USERBLUE < CPUBLUE + .4 && USERBLUE > CPUBLUE - .4
                && USERGREEN < CPUGREEN + .4 && USERGREEN > CPUGREEN - .4) {
                
                    uLCD.cls();
                    uLCD.locate(5,6);
                    uLCD.printf("Correct!");
                    red = 0.0; 
                    green = 0.0;
                    blue = 0.0;
                    red2 = 0.0; 
                    green2 = 0.0;
                    blue2 = 0.0;
                    GAMES[0] = false; 
                    score++;
                    break;
                } 
                else if ( !submit ) 
                {
                    uLCD.cls();
                    uLCD.locate(6,6);
                    uLCD.printf("Wrong!");
                    lives--;
                    break;
                 }
            }
            wait(2);
            uLCD.cls();
            uLCD.locate(0,0);
            // check if game over
            if (lives == 0){
                Game_Over = true; 
                GAMES[0] = false;
                red = 0.0; 
                green = 0.0;
                blue = 0.0;
                red2 = 0.0; 
                green2 = 0.0;
                blue2 = 0.0;
            }
        }
        
        // this is the while loop for the bin minigame
        while(GAMES[1] && !Game_Over) { 
            // score screen
            uLCD.printf("You have %d lives! \n\r",lives);
            uLCD.printf("\nScore: %d \n\r",score);
            uLCD.printf("\nHighscore: %d \n\r",highscore);
            wait(2);
            uLCD.cls();
            while(1) {
                // game intro screen
                uLCD.cls();
                uLCD.locate(3,2);
                uLCD.color(0xF74BFE);
                uLCD.printf("BINARY GAME");
                uLCD.locate(4,6);
                uLCD.color(GREEN);
                uLCD.printf("BASE 10: %d",bin2);
                uLCD.printf("\n\n    BINARY: ");
                uLCD.color(0xFFFF00);
                uLCD.printf("\n\n    %d  ",userBin[3]);
                uLCD.color(GREEN);
                uLCD.printf("%d  ",userBin[2]);
                uLCD.color(BLUE);
                uLCD.printf("%d  ",userBin[1]);
                uLCD.color(RED);
                uLCD.printf("%d  ",userBin[0]);
                uLCD.color(GREEN);
                uLCD.locate(0,0);
                wait(.5);
                // check push buttons to switch between zero and one at each location
                if (!pb1) 
                {
                    if (userBin[0] == 0) {
                        userBin[0] = 1;
                        
                    } 
                    else
                    {
                        userBin[0] = 0;
                    } 
                }
                
                
                if (!pb2) 
                {
                    if (userBin[1] == 0) {
                        userBin[1] = 1;
                        
                    } 
                    else
                    {
                        userBin[1] = 0;
                    } 
                }
                
                
                
                if (!pb3) 
                {
                    if (userBin[2] == 0) {
                        userBin[2] = 1;
                        
                    } 
                    else
                    {
                        userBin[2] = 0;
                    } 
                }
                
                if (!pb4) 
                {
                    if (userBin[3] == 0) {
                        userBin[3] = 1;
                        
                    } 
                    else
                    {
                        userBin[3] = 0;
                    } 
                }
                
                // check if correct
                if (!submit) {
                    for (int i = 0; i < 4; i++) 
                    {
                        convertedInput += userBin[i] * pow(2.0,(double)i);
                    }    
                    printf("%d",convertedInput);
                    if (convertedInput == bin2) {
                        uLCD.cls();
                        uLCD.locate(5,6);
                        uLCD.printf("Correct!");
                        wait(2);
                        GAMES[1] = false;
                        score++;
                        break;
                    }
                    else { 
                        convertedInput = 0;
                        uLCD.cls();
                        uLCD.locate(6,6);
                        uLCD.printf("Wrong!");
                        wait(2);
                        lives--;
                        break;
                    }
                   
                }
            }
                uLCD.cls();
                uLCD.locate(0,0);
                // check game over
                if (lives == 0){Game_Over = true; GAMES[1] = false;}
        
        }
        
        // this is the while loop for the distance game
        while(GAMES[2] && !Game_Over) 
        {
            // score screen
            uLCD.printf("You have %d lives! \n\r",lives);
            uLCD.printf("\nScore: %d \n\r",score);
            uLCD.printf("\nHighscore: %d \n\r",highscore);
            wait(2);
            uLCD.cls();
            // game intro screen
            uLCD.locate(2,2);
            uLCD.color(0xF74BFE);
            uLCD.printf("DISTANCE GAME");
            uLCD.locate(2,6);
            uLCD.color(GREEN);
            uLCD.printf("Match Distance");
            uLCD.locate(2,8);
            uLCD.printf("Target: %d cm \n\r",target_dist);
            uLCD.color(GREEN);
            uLCD.locate(0,0);
            while(1) {
                // trigger sonar to send a ping
                trigger = 1;
                sonar.reset();
                wait_us(10.0);
                trigger = 0;
                //wait for echo high
                while (echo==0) {};
                //echo high, so start timer
                sonar.start();
                //wait for echo low
                while (echo==1) {};
                //stop timer and read value
                sonar.stop();
                //subtract software overhead timer delay and scale to cm
                dist = (sonar.read_us()-correction)/58.0;
                // check if distance is within range
                if (!submit && dist < target_dist + 3 && dist > target_dist - 3){
                    uLCD.cls();
                    uLCD.locate(5,6);
                    uLCD.printf("Correct!");
                    wait(2);
                    GAMES[2] = false;
                    score++;
                    break;
                }
                else if(!submit){
                    uLCD.cls();
                    uLCD.locate(6,6);
                    uLCD.printf("Wrong!");
                    uLCD.printf("\n\nYour input: %d cm \n\r",dist);
                    wait(2);
                    lives--;
                    break;
                }
                //wait so that any echo(s) return before sending another ping
                wait(0.2);
            }
            uLCD.cls();
            uLCD.locate(0,0);
            // check game over
            if (lives == 0){Game_Over = true; GAMES[2] = false;}
        }
        
        // this is the while loop for the color pattern matching game
        while(GAMES[3] && !Game_Over)
        {
            // score intro screen
            uLCD.printf("You have %d lives! \n\r",lives);
            uLCD.printf("\nScore: %d \n\r",score);
            uLCD.printf("\nHighscore: %d \n\r",highscore);
            wait(2);
            uLCD.cls();
            // game intro screen
            bool wrongPat = false;
            uLCD.cls();
            uLCD.locate(3,2);
            uLCD.color(0xF74BFE);
            uLCD.printf("PATTERN GAME");
            uLCD.locate(0,6);
            uLCD.color(GREEN);
            uLCD.printf("Match the Pattern");
            uLCD.color(GREEN);
            uLCD.locate(0,0);
            wait(2);
            uLCD.cls();
            // PLAY THE PATTERN
            colors[pattern[0]] = true; //activate the color
            checkTrue(); // find what color is activated and draw it
            colors[pattern[1]] = true;
            checkTrue();
            colors[pattern[2]] = true;
            checkTrue();
            colors[pattern[3]] = true;
            checkTrue();
            colors[pattern[4]] = true;
            checkTrue();
            colors[pattern[5]] = true;
            checkTrue();
            int index = 0;
            uLCD.locate(2,6);
            uLCD.printf("Input Pattern");
            wait(2);
            uLCD.cls();
            // store pattern input
            // show the color when push button pressed
            while(1){
                if(!pb1){
                    colors[0] = true;
                    checkTrue();
                    inputPattern[index] = 0;
                    index ++;
                    
                }
                if(!pb2){
                    colors[1] = true;
                    checkTrue();
                    inputPattern[index] = 1;
                    index ++;
                }
                if(!pb3){
                    colors[2] = true;
                    checkTrue();
                    inputPattern[index] = 2;
                    index ++;
                }
                if(!pb4){
                    colors[3] = true;
                    checkTrue();
                    inputPattern[index] = 3;
                    index ++;
                }
                
                if(index == 6){break;}
            }
            // check if patterns match
            while(1){ 
                for(int x = 0; x < 6; x++){
                    if(inputPattern[x] != pattern[x]){
                        uLCD.cls();
                        uLCD.locate(6,6);
                        uLCD.printf("Wrong!");
                        wait(2);
                        lives--;
                        wrongPat = true;
                        break;
                    }
                }
                if(!wrongPat){
                    uLCD.cls();
                    uLCD.locate(5,6);
                    uLCD.printf("Correct!");
                    wait(2);
                    GAMES[3] = false;
                    score++;
                    break;
                }
                else if(wrongPat){break;}
            }
            uLCD.cls();
            uLCD.locate(0,0);
            // check game over
            if (lives == 0){Game_Over = true; GAMES[3] = false;}
        }
        
        
        while(Game_Over){
            // game over screen
            uLCD.background_color(0x008000);
            uLCD.cls();
            uLCD.text_string("Game Over!", '\x04', '\x07', FONT_7X8, 0xFF0000);
            wait(2);
            uLCD.cls();
            uLCD.background_color(0x000000);
            // check for new high score
            if(score>highscore){
                highscore = score;
                uLCD.cls();
                uLCD.background_color(0x000000);
                uLCD.color(GREEN);
                uLCD.locate(2,6);
                uLCD.printf("New Highscore!:");
                uLCD.locate(9,8);
                uLCD.printf("%d \n\r",highscore);
                wait(2);
                uLCD.cls();
            }
            // wait on push button to start game again
            while(1){
                uLCD.cls();
                uLCD.locate(2,6);
                uLCD.color(GREEN);
                uLCD.printf("Hold Submit to");
                uLCD.locate(4,8);
                uLCD.printf("Play Again");
                wait(2);
                // reset all values
                if(!submit){
                    Game_Over = false;
                    lives = 5;
                    score = 0;
                    uLCD.cls();
                    uLCD.locate(0,0);
                    break;
                }
            }
        }
    }
}