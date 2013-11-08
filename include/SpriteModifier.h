/***********************************************************************************
*This class is used to load, manipulate, and save sprites. It uses the graphics,   *
*window, and system modules of SFML 2.0 or later. Documentation can be found       *
*inlined below each function. Full code at https://github.com/GGist/Sprite_Utility *
*This code is licensed under the MIT License.                                      *
***********************************************************************************/

#ifndef SPRTIEMODIFIER_H
#define SPRTIEMODIFIER_H

#include <climits>
#include <fstream>
#include <queue>
#include <string>
#include <SFML/Graphics.hpp>

class SpriteModifier
{
    public:
        SpriteModifier();
        //Constructor
        virtual ~SpriteModifier();
        //Destructor
        bool loadSprites(std::string textFile);
        //Loads individual sprites in the textFile directory using the names
        //specified in the textFile as the filenames for the sprites
        //Returns false if the textFile was not found or a sprite specified in
        //the file was not found
        bool generateSprites(std::string filePath, sf::Color fillColor);
        //Generates sprites starting from the top left of the file going row
        //by row using the fillColor to determine where a sprites bounds are
        //Passing in sf::Color::Transparent for the fillColor will enable auto
        //detect background color which uses a pixel from the top left as the fillColor
        //Returns false if the file could not be found
        bool flipHorizontally();
        //Flips the sprites in the sprite buffer horizontally
        //Returns false if the sprite buffer is empty
        bool flipVertically();
        //Flips the sprites in the sprite buffer vertically
        //Returns false if the sprite buffer is empty
        bool creatAlphaMask(sf::Color purgedColor);
        //Creates an alpha mask for the specified color and applies it to the
        //sprites currently in the buffer
        //Returns false if the sprite buffer is empty
        bool saveSprites(std::string filePath);
        //Saves the sprites that are in the sprite buffer to the specified filepath
        //Returns false if the sprite buffer is empty or the filePath is invalid
        void clearSprites();
        //Clears the sprites that are in the sprite buffer
        std::vector<sf::Image> getSprites();
        //Returns a copy of the vector that contains the sprites in the current sprite buffer

    private:
        static const sf::Vector2u spriteTolerance;
        static const std::string SAVE_FORMAT;

        //Container Class
        struct Pixel_Info {
            Pixel_Info() {}
            Pixel_Info(sf::Color color, sf::Vector2u position) :
                pColor(color), pPosition(position) {}
            sf::Color pColor;
            sf::Vector2u pPosition;
        };

        std::queue<Pixel_Info> floodFind(sf::Image& spriteSheet, sf::Color& boundsColor, sf::Vector2u starting);
        //Finds and logs all of the pixels of the sprite at starting in spriteSheet and also pushes a bound
        //to the back of spriteBounds containing the width and height of the sprite that was analyzed
        //Returns a copy of the queue of pixels that were logged
        sf::Image generateImage(std::queue<Pixel_Info>& pixels);
        //The queue of pixels will be empty when this function is finished, this is inteded behavior
        //Returns an image consisting of the provided pixels

        std::vector<sf::Image> spriteBuffer;
        std::vector<sf::IntRect> spriteBounds;
};

#endif // SPRITEMODIFIER_H
