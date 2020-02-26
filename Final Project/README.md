#                                                DANCING GLOVE

<img width="400" align = "center" alt="like" src="https://user-images.githubusercontent.com/46327732/75369588-69cf7e00-58cc-11ea-856f-7d7e777aff05.jpg">




## Game idea: 
            "Dancing Glove" where the projection of the palm on the matrix show you how "to dance with your fingers" (^^).
In other words, on a 8 by 8 matrix it will show you a palm and if some fingers are missing in the projection, that means you hve to flex that figer/fingers if you don't want to lose. Every level has a number from 1 to X and that number represents the difficulty of the level.
            
            The difficulty is measured like this: 
            -The number of moves you need to do si equal to the number of the level (lvl 2 = 2 arrows)  
            -The time-limit you have is inversely proportional with the level number (the higher the level the lower is the time-limit). 

## HW components: 
            -Arduino Nano
            -LCD Display
            -Joystick
            -8*8 Led Matrix
            -5 flex sensors
            -rezistors : 5 * 10k and 1 * 220

## Game brief introduction:
            - On the matrix there are 10 projection of a palm with different postion of the fingers
            - On the LCD Display we have the menu (Start game, Settings, HighScore) and for every choise it's characteristics
            - During the game the LCD dispaly the level, score and lives
   
## Video Demo:
            https://www.youtube.com/watch?v=kxpWqEBkEEs
            
## The game menu:
            -Start -> If selected, the game starts
            -HighScore -> It shows the highscore that the game has
            -Settings -> You can select the starting level from 1 to 5
            -Info -> It has 4 parts: Creator Name, Githug Link, Game Name, "made for"


## How to play:

   After you start the game, in 3 seconds it will show you a projection of a palm on the matrix, depending on the level selected in the settings. 
The projection of the palm on the matrix indicates what fingers you have to felx(it can be 0, 1 or all):

            - For this out-put on the matrix, you don't have to flex any finger
<img width="216" alt="full palm" src="https://user-images.githubusercontent.com/46327732/75365763-51f4fb80-58c6-11ea-9e51-b1261baa1db4.png">
            
            -For this out-puts on the matrix, you would have to flex the missing finger.
            (index finger for the first one and ring finger for the other one).
<img width="216" alt="missing index" src="https://user-images.githubusercontent.com/46327732/75365879-8668b780-58c6-11ea-8fe9-a45d43761389.png">

<img width="216" alt="missing ring" src="https://user-images.githubusercontent.com/46327732/75365883-87014e00-58c6-11ea-9e16-3bedd1fd2d3f.png">

 
            -For this kind of out-puts on the matrix, you would have to flex multiple fingers.
 <img width="223" alt="missing ring index middle" src="https://user-images.githubusercontent.com/46327732/75366027-c92a8f80-58c6-11ea-97af-2f7985abc8c2.png">
 
<img width="223" alt="like" src="https://user-images.githubusercontent.com/46327732/75366032-c9c32600-58c6-11ea-8195-6e0ed3493466.png">


            If you will do all the moves corectlly, then you will get an "O" on the matrix like this witch means that you finished the level
<img width="222" alt="O" src="https://user-images.githubusercontent.com/46327732/71313788-59bb9e00-2446-11ea-8a28-22ef64fda73a.png">
            
            If you will a mistake during the level, then you will get an "X" on the matrix like this
<img width="223" alt="X" src="https://user-images.githubusercontent.com/46327732/71313789-59bb9e00-2446-11ea-831a-29d64d80b85e.png">



## The whole assembled hardware:
<img width="400" alt="X" src="https://user-images.githubusercontent.com/46327732/75366488-7c938400-58c7-11ea-9900-f291d8db153f.jpeg">
<img width="400" alt="X" src="https://user-images.githubusercontent.com/46327732/75366497-7ef5de00-58c7-11ea-9c25-b09c108fc7a5.jpeg">
<img width="400" alt="X" src="https://user-images.githubusercontent.com/46327732/75366500-80270b00-58c7-11ea-8163-badb55520d8e.jpeg">
<img width="400" alt="X" src="https://user-images.githubusercontent.com/46327732/75366501-80bfa180-58c7-11ea-9f0a-245695921bbb.jpeg">
<img width="400" alt="X" src="https://user-images.githubusercontent.com/46327732/75366504-82896500-58c7-11ea-9dbd-2fb685745c21.jpeg">
<img width="400" alt="X" src="https://user-images.githubusercontent.com/46327732/75366505-83ba9200-58c7-11ea-980c-60bba54c2b18.jpeg">

### Inspired by the tutorial: https://www.instructables.com/id/Arduino-Flex-Sensor-Glove/ 
