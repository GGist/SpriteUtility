/***********************************************************************************
*This class is used to store information about what calls SpriteModifier should    *
*make as well as the information it requires for such calls. It uses the graphics, *
*window, and system modules of SFML 2.0 or later. Documentation can be found       *
*inlined below each function. Full code at https://github.com/GGist/Sprite_Utility *
*This code is licensed under the MIT License.                                      *
***********************************************************************************/

#ifndef COMMANDINFO_H
#define COMMANDINFO_H

#include<SFML/Graphics.hpp>
#include<SpriteModifier.h>

class CommandInfo
{
    public:
        enum External {
            GENERATE,
            LOAD,
            SAVE,
            NONE
        };
        enum Tag {
            FLIP_VERT,
            FLIP_HORIZ,
            ALPHA,
            EMPTY
        };

        CommandInfo();
        //Constructor
        virtual ~CommandInfo();
        //Destructor
        bool setStart(External command, std::string fileName, sf::Color mask = sf::Color::Transparent);
        //This will set the flag that the specified command should be executed
        //on the fileName which should be either a spriteSheet (if GENERATE) or
        //a text file with lists of fileNames (if LOAD)
        //Returns false if you tried to GENERATE or LOAD twice without reseting
        bool setTag(Tag param, sf::Color mask = sf::Color::Transparent);
        //This will set the specified flags
        //Returns false if a command was not set beforehand
        bool setClear();
        //THE CLEAR COMMAND SHOULD NOT BE AFFECTED BY ANY COMMANDS
        //This will set the clear flag that should clear any sprites that are
        //currently loaded
        //Returns false if any commands are flags were set beforehand
        void reset();
        //This resets the current commands/flags that have been set
        bool executeCommands(SpriteModifier& sMod);
        //Executes the commands and flags that have been specified

    private:
        static const int MAX_TAGS = 3;

        External command;
        bool clearFlag;
        std::string commFileName, saveFileName;
        Tag params[MAX_TAGS];
        sf::Color aMask, gMask;
};

#endif // COMMANDINFO_H
