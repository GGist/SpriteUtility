#include "CommandInfo.h"

using namespace std;

CommandInfo::CommandInfo() : command(NONE), clearFlag(false), commFileName(),
    saveFileName(), params(), aMask(sf::Color::Transparent),
    gMask(sf::Color::Transparent)
{
    for (int i = 0; i < MAX_TAGS; ++i)
        params[i] = EMPTY;
}

CommandInfo::~CommandInfo()
{

}

bool CommandInfo::setStart(External command, std::string fileName, sf::Color mask)
{
    if (this->command == GENERATE || this->command == LOAD)
        return false;

    this->command = command;
    if (command == SAVE)
        saveFileName = fileName;
    else
        commFileName = fileName;

    if (command == GENERATE)
        gMask = mask;

    return true;
}

bool CommandInfo::setTag(Tag param, sf::Color mask)
{
    int index = 0;

    while (index < MAX_TAGS && params[index] != EMPTY)
        ++index;

    if (index >= MAX_TAGS)
        return false;
    else
        params[index] = param;

    if (param == ALPHA)
        aMask = mask;

    return true;
}

bool CommandInfo::setClear()
{
    if (command != NONE)
        return false;

    clearFlag = true;

    return true;
}

void CommandInfo::reset()
{
    for (int i = 0; i < MAX_TAGS; ++i)
        params[i] = EMPTY;

    command = NONE;
    aMask = sf::Color::Transparent;
    gMask = sf::Color::Transparent;
    clearFlag = false;
    commFileName.clear();
    saveFileName.clear();
}

bool CommandInfo::executeCommands(SpriteModifier& sMod)
{
    if (clearFlag) {
        sMod.clearSprites();
        clearFlag = false;
        return true;
    }

    switch (command)
    {
    case GENERATE:
        if (!sMod.generateSprites(commFileName, gMask))
	  return false;
        break;
    case LOAD:
        if (!sMod.loadSprites(commFileName))
	  return false;
        break;
    case SAVE:
        if (!sMod.saveSprites(saveFileName))
	  return false;
        break;
    case NONE:
        break;
    }

    for (int i = 0; i < MAX_TAGS; ++i) {
        switch (params[i])
        {
        case FLIP_HORIZ:
            sMod.flipHorizontally();
        break;
        case FLIP_VERT:
            sMod.flipVertically();
            break;
        case ALPHA:
            sMod.creatAlphaMask(aMask);
            break;
        case EMPTY:
            break;
        }
    }

    return true;
}
