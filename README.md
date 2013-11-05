Sprite Utility
==============
About:
------
This utility was created to aid me in the process of getting individual sprites from sprite sheets
so that they could be used as animations in the game I was developing. I realized that this tool
was so useful to me that I cleaned up the UI a little bit and decided to post it for anyone to use
or modify. This game utilizes the system, window, and graphics modules of SFML 2.0 or later. For more
documentation see the header files or main.cpp.<br \><br \>

This code is licensed under the MIT License so you can do quite a bit with it. The license
has been included in the root directory of this project if you would like to view it.<br \>
Commands:
--------
**start** accepts any of the tags below that let you generater/load in and or modify sprites<br \>
**save "path/base_name"** saves the currently loaded sprites out to path/base_name_i.format<br \>
**clear** clears the buffer that the currently loaded sprites are being stored in<br \>

Tags:
------
***These can only be used with the start command***<br \>
**-l "path/manifest.txt"** loads the sprite names contained in manifest.txt from the path/ directory<br \>
**-g "path/spritesheet.format" (r, g, b)** generates sprites from spritesheet.format using (r, g, b) as the bounding
color<br \>
**-fv** flips the currently loaded sprites vertically<br \>
**-fh** flips the currently loaded sprites horizontally<br \>
**-a (r, g, b)** replaces the color (r, g, b) of the currently loaded sprites with an alpha mask<br \>

Example:
-------
Say you want to generate sprites from a sprite sheed you have

![alt text](https://github.com/GGist/Sprite_Utility/tut/Robot_Black.png "Sprite Sheet")

then all you have to do is startup Sprite_Utility and enter the **start** command followed by
the **-g** tag with the **path to the sprite sheet** and the **r, g, and b** values of the background
color (these can be found by loading up your favorite paint program, using the eye dropper, and
viewing the color properties)

![alt text](https://raw.github.com/GGist/Sprite_Utility/tut/Step1.png "Step 1")
![alt text](https://raw.github.com/GGist/Sprite_Utility/tut/Step1Dir.png "Step 1 Directory")

after entering this command the program will cut out our sprites and keep them stored in memory.
If we wish to apply any other commands we can do so by typing start again and specify what else we
want done. When we are satisfied we can use the **save** command and specify a **path/base_name**

![alt text](https://raw.github.com/GGist/Sprite_Utility/tut/Step2.png "Step 2")
![alt text](https://raw.github.com/GGist/Sprite_Utility/tut/Step2Dir.png "Step 2 Directory")

after pressing enter we can go in to where we told it to save our sprites and see the finished product

![alt text](https://raw.github.com/GGist/Sprite_Utility/tut/Step2Dir.png "Step 2 Directory")