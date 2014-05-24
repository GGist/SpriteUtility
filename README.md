Sprite Utility
==============
This utility was created to aid me in the process of getting individual sprites from sprite sheets
so that they could be used as animations in the game I was developing. I realized that this tool
was so useful to me that I cleaned up the UI a little bit and decided to post it for anyone to use
or modify. For implementation specific documentation, check out the source code comments.<br \><br \>

This code is licensed under the MIT License so you can do quite a bit with it. The license
has been included in the root directory of this project if you would like to view it.

Building:
---------
The only dependencies this program has are the SFML system, window, and graphics libraries. I 
have included the pre-compiled 64-bit static libraries for Windows users. If you are on Windows 
64-bit, have a 64-bit compiler, and have either mingw-make or make available then all you have to 
do is run the following commands:
```
git clone https://github.com/GGist/SpriteUtility SpriteUtility
cd SpriteUtility && <make or mingw-make>
```
For all other environments, you will have to get the static libraries yourself, put them in the 
depend\lib\SFML directory, and then run make. If you wish to use SFML shared libraries, put it
in the same directory, but make sure to update the Makefile.

Commands:
--------
**start** accepts any of the tags below that let you generater/load in and or modify sprites<br \>
**save \<path/base_name\>** saves the currently loaded sprites out to *path/base_name_i.format*<br \>
**clear** clears the buffer that the currently loaded sprites are being stored in<br \>

Tags:
------
***These can only be used with the start command***<br \>
**-l \<path/manifest.txt\>** loads the sprite names contained in *manifest.txt* from the *path/directory*<br \>
**-g \<path/spritesheet.format\> [(r, g, b)]** generates sprites from *spritesheet.format* and if *(r, g, b)*
is not specified auto detect will be used which uses the top left pixel's color as the bounding color<br \>
**-fv** flips the currently loaded sprites vertically<br \>
**-fh** flips the currently loaded sprites horizontally<br \>
**-a \<(r, g, b)\>** replaces the color *(r, g, b)* of the currently loaded sprites with an alpha mask<br \>

Example:
-------
Lets go ahead and take the below image as the sprite sheet that we want to extract individual sprites from.

![alt text](https://raw.github.com/GGist/SpriteUtility/master/example/Robot_Black.png "Sprite Sheet")

In order to use this sprite sheet with the program, put it in the directory of your choice. I have put mine
in the data folder that the Makefile creates. Start the program and enter the **start** command followed by
the **-g** tag with the **path/spritesheet.format**. An optional parameter allows you to specify the
**(r, g, b)** components of the background color.

![alt text](https://raw.github.com/GGist/SpriteUtility/master/example/Step1.png "Step 1")

After entering this command the program will cut out our sprites and keep them stored in memory.
At this point, we can load in other spritesheets and they will be stored alongside our current sprites
in memory. Any flipping or alpha masks we specify will be applied to all of the sprites currently loaded.
Once we are done, we can type the **save** command followed by the **path/base_name** parameter.

![alt text](https://raw.github.com/GGist/SpriteUtility/master/example/Step2.png "Step 2")

After entering this command, the program will start saving our images and will be available for us in an instant.

![alt text](https://raw.github.com/GGist/SpriteUtility/master/example/Finished.png "Sprite Directory")
