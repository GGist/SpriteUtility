/***********************************************************************************
*This is a utility program used to generate sprites from existing sprite sheets or *
*loading individual sprites in through a text file. Once the sprites have either   *
*been generated or loaded you can add alpha channels and flip sprites vertically   *
*and/or horizontally. Finally, you can save sprites out to a file. Saving and      *
*loading currently default to .png while generating requires you to specify a      *
*format. This class requires the graphics, window, and system modules of SFML 2.0  *
*or later. Supported image formats are bmp, png, tga, jpg, gif, psd, hdr and pic.  *
*                                                                                  *
*This code is licensed under the MIT License.                                      *
*Full code and use information at https://github.com/GGist/Sprite_Utility          *
***********************************************************************************/

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "SpriteModifier.h"
#include "CommandInfo.h"

using namespace std;

static const unsigned int MIN_COMMAND_LENGTH = 8, MAX_COLOR_LENGTH = 3, MAX_COLOR = 255;
static const string QUIT = "quit", FORMAT = ".png", SAVE = "save", CLEAR = "clear", START = "start";

void purgeWhite(string& input);
//Removes all of the white space from the argument input
bool parseCommand(string input, CommandInfo& cInfo);
//Returns false if the command is invalid
sf::Color parseColor(string text, unsigned int& index);
//Grabs the formatted r, g, b values from the text starting
//with the first value at index
//Throws a string error message if color is out of bounds
//Returns a copy of the color object

int main()
{
    string userInput;
    CommandInfo cInfo;
    SpriteModifier sMod;

    cout << "$ ";
    getline(cin, userInput);

    while (userInput != QUIT) {
        while (!parseCommand(userInput, cInfo) && userInput != QUIT) {
            cInfo.reset();
            cout << endl << "Invalid Command" << endl;
            cout << endl << "$ ";
            getline(cin, userInput);
        }

        cInfo.executeCommands(sMod);
        cInfo.reset();

        cout << endl << "$ ";
        getline(cin, userInput);
    }

    return 0;
}

void purgeWhite(string& input) {
    int count = 0;
    bool segmentDone = false;

    for (unsigned int i = 0; i < input.length(); ++i) {
        if (input[i] == ' ') {
            ++count;
            segmentDone = false;
        } else {
            segmentDone = true;
        }

        if (segmentDone && count != 0) {
            input.erase(i - count, count);
            i -= count;
            count = 0;
        }
    }
}

bool parseCommand(string input, CommandInfo& cInfo) {
    purgeWhite(input);
    //Used to preserve upper case characters for filenames
    string preservedInput = input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (input.find(CLEAR) == 0) {
        cInfo.reset();
        cInfo.setClear();
        return true;
    } else if (input.find(SAVE) == 0) {
        cInfo.setStart(CommandInfo::External::SAVE, preservedInput.substr(SAVE.size(), preservedInput.size() - SAVE.size()));
        return true;
    } else if (input.find(START + "-") != 0 || input.length() < MIN_COMMAND_LENGTH) {
        //8 is the minimum amount of characters required for the program
        return false;
    }

    string fileName = "";
    sf::Color color;
    unsigned int index = 6;

    while (index < input.length()) {
        switch(input[index])
        {
        case 'g':
            //Generate
            fileName.clear();

            //Grab file name
            while (index < input.length() && input[++index] != '.')
                fileName.push_back(preservedInput[index]);

            //Grab file format
            for (unsigned int i = 0; i < FORMAT.length(); ++i)
                fileName.push_back(preservedInput[index++]);

            //Optional Color Parameter
            if (input[index++] == '(') {
                //Grab Color, index will be modified by parseColor()
                try {
                    color = parseColor(input, index);
                } catch (string message) {
                    cout << endl << message << endl;
                    return false;
                }
            } else {
                //Since users cannot specify an alpha value, set color
                //to transparent to signify auto detect color to ignore
                color = sf::Color::Transparent;
            }

            //Check if command was already set
            if (!cInfo.setStart(CommandInfo::External::GENERATE, fileName, color))
                return false;

            //Check for another tag marker
            if (input[++index] == '-')
                ++index;
            break;
        case 'l':
            //Load
            fileName.clear();

            while (index < input.length() && input[++index] != '-')
                fileName.push_back(preservedInput[index]);

            //Check if command was already set
            if (!cInfo.setStart(CommandInfo::External::LOAD, fileName))
                return false;

            //Check for another tag marker
            if (input[++index] == '-')
                ++index;
            break;
        case 'f':
            //Flip
            ++index;
            if (input[index] == 'v')
                cInfo.setTag(CommandInfo::Tag::FLIP_VERT);
            else if (input[index] == 'h')
                cInfo.setTag(CommandInfo::Tag::FLIP_HORIZ);
            else
                return false;

            //Check for another tag marker
            if (input[++index] == '-')
                ++index;
            break;
        case 'a':
            //Alpha Channel

            //Increment One or Two (to skip parenthesis)
            if (input[++index] == '(')
                ++index;
            else
                return false;

            //Grab Color, index will be modified by parseColor()
            try {
                color = parseColor(input, index);
            } catch (string message) {
                cout << endl << message << endl;
                return false;
            }

            cInfo.setTag(CommandInfo::Tag::ALPHA, color);

            //Check for another tag marker
            if (input[++index] == '-')
                ++index;
            break;
        default:
            //Unrecognized Tag
            return false;
            break;
        }
    }

    return true;
}

sf::Color parseColor(string text, unsigned int& index)
{
    string convert = "";
    unsigned int digits = 0, r = 0, g = 0, b = 0;

    //Pull out first and second color codes
    for (int i = 0; i < 2; ++i) {
        while (text[index] != ',' && digits <= MAX_COLOR_LENGTH) {
            convert.push_back(text[index]);
            ++index;
            ++digits;
        }
        if (digits > MAX_COLOR_LENGTH) {
            throw string("Color Value(s) Out Of Bounds");
        } else {
            if (i == 0)
                r = atoi(convert.c_str());
            else
                g = atoi(convert.c_str());

            convert.clear();
            digits = 0;
        }
        ++index;
    }

    //Grab last color code
    while (text[index] != ')' && text[index] != '-' && digits <= MAX_COLOR_LENGTH) {
        convert.push_back(text[index]);
        ++index;
        ++digits;
    }
    if (digits > MAX_COLOR_LENGTH) {
        throw string("Color Value(s) Out Of Bounds");
    } else {
        b = atoi(convert.c_str());
    }

    //Check color codes are valid
    if (r > MAX_COLOR || g > MAX_COLOR || b > MAX_COLOR)
        throw string("Color Value(s) Out Of Bounds");

    return sf::Color(r, g, b);
}
