#include "SpriteModifier.h"

using namespace std;

const sf::Vector2u SpriteModifier::spriteTolerance(5, 5);
const string SpriteModifier::SAVE_FORMAT(".png");

SpriteModifier::SpriteModifier() : spriteBuffer(), spriteBounds()
{

}

SpriteModifier::~SpriteModifier()
{

}

bool SpriteModifier::loadSprites(std::string textFile)
{
    ifstream spriteNames;
    string tempName, path;
    sf::Image tempImage;

    spriteNames.open(textFile.c_str());

    if (!spriteNames.is_open())
        return false;

    //Find path substring
    int slashIndex = -1;
    for (int i = textFile.size() - 1; i >= 0; --i) {
        if (textFile[i] == '/' || textFile[i] == '\\')
            slashIndex = i;
    }
    if (slashIndex < 0)
        return false;
    else
        path = textFile.substr(0, slashIndex + 1);

    //Grab the sprite filenames
    while (!spriteNames.eof()) {
        getline(spriteNames, tempName);
        if (!tempImage.loadFromFile(path + tempName + SAVE_FORMAT)) {
            clearSprites();
            return false;
        }
        spriteBuffer.push_back(tempImage);
    }

    return true;
}

bool SpriteModifier::generateSprites(string filePath, sf::Color boundsColor)
{
    static int test = 0;
    sf::Image spriteSheet;
    if (!spriteSheet.loadFromFile(filePath))
        return false;

    queue<Pixel_Info> tempPixels;
    sf::Vector2u currPixel;
    sf::Image currImage;

    while (currPixel.y < spriteSheet.getSize().y) {
        while (currPixel.x < spriteSheet.getSize().x) {
            if (spriteSheet.getPixel(currPixel.x, currPixel.y) != boundsColor) {
                tempPixels = floodFind(spriteSheet, boundsColor, currPixel);
                currImage = generateImage(tempPixels);
                //Ignore sprites below the tolerance threshold
                if (!(currImage.getSize().x < spriteTolerance.x) && !(currImage.getSize().y < spriteTolerance.y))
                    spriteBuffer.push_back(currImage);
            }
            ++currPixel.x;
        }
        ++currPixel.y;
        currPixel.x = 0;
    }

    return true;
}

queue<SpriteModifier::Pixel_Info> SpriteModifier::floodFind(sf::Image& spriteSheet, sf::Color& boundsColor, sf::Vector2u starting)
{
    unsigned int minX = UINT_MAX, minY = UINT_MAX, maxX = 0, maxY = 0;
    queue<Pixel_Info> currPixels;
    queue<sf::Vector2u> currVectors;
    sf::Vector2u temp;

    currVectors.push(starting);

    while (!currVectors.empty()) {
        temp = currVectors.front();
        currVectors.pop();

        if (spriteSheet.getPixel(temp.x, temp.y) != boundsColor) {
            minX = (temp.x < minX) ? temp.x : minX;
            minY = (temp.y < minY) ? temp.y : minY;
            maxX = (temp.x > maxX) ? temp.x : maxX;
            maxY = (temp.y > maxY) ? temp.y : maxY;

            //Grab pixel info
            currPixels.push(Pixel_Info(spriteSheet.getPixel(temp.x, temp.y), temp));
            //Mark the pixel
            spriteSheet.setPixel(temp.x, temp.y, boundsColor);

            currVectors.push(sf::Vector2u(temp.x - 1, temp.y));
            currVectors.push(sf::Vector2u(temp.x + 1, temp.y));
            currVectors.push(sf::Vector2u(temp.x, temp.y - 1));
            currVectors.push(sf::Vector2u(temp.x, temp.y + 1));
        }
    }

    //Used to determine dimensions when re-creating image with the pixels
    spriteBounds.push_back(sf::IntRect(minX, minY, (maxX - minX + 1), (maxY - minY + 1)));

    return currPixels;
}

sf::Image SpriteModifier::generateImage(queue<Pixel_Info>& pixels)
{
    //This function currently looks at the last bounds that was pushed
    //to determine the height and width of the generated image
    Pixel_Info tempPixel;
    sf::IntRect currBounds = spriteBounds.back();
    sf::Image newImage;
    newImage.create(currBounds.width, currBounds.height, sf::Color::Transparent);

    while (!pixels.empty()) {
        tempPixel = pixels.front();
        newImage.setPixel(tempPixel.pPosition.x - currBounds.left,
                          tempPixel.pPosition.y - currBounds.top,
                          tempPixel.pColor);
        pixels.pop();
    }

    return newImage;
}

bool SpriteModifier::flipHorizontally()
{
    if (spriteBuffer.empty())
        return false;

    for (int i = 0; i < spriteBuffer.size(); ++i)
        spriteBuffer[i].flipHorizontally();

    return true;
}

bool SpriteModifier::flipVertically()
{
    if (spriteBuffer.empty())
        return false;

    for (int i = 0; i < spriteBuffer.size(); ++i)
        spriteBuffer[i].flipVertically();

    return true;
}

bool SpriteModifier::creatAlphaMask(sf::Color purgedColor)
{
    if (spriteBuffer.empty())
        return false;

    for (int i = 0; i < spriteBuffer.size(); ++i)
        spriteBuffer[i].createMaskFromColor(purgedColor);

    return true;
}

bool SpriteModifier::saveSprites(string filePath)
{
    string temp;

    for (int i = 0; i < spriteBuffer.size(); ++i) {
        if (!spriteBuffer[i].saveToFile(filePath + "_" + to_string(i) + SAVE_FORMAT))
            return false;
    }

    return true;
}

void SpriteModifier::clearSprites()
{
    spriteBuffer.clear();
    spriteBounds.clear();
}

vector<sf::Image> SpriteModifier::getSprites()
{
    return spriteBuffer;
}
