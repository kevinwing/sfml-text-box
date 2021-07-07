/**
 * @file textbox.cpp
 * @author Kevin Wing (kevinrwing@gmail.com)
 * @brief Textbox class defintion file
 * @version 0.1
 * @date 2021-05-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "textbox.hpp"

/**
 * @brief Construct a new TextBox::TextBox object and initialize member objects
 *
 * @param fontSize int height in pixels to set the text font to (default: 14.f)
 * @param width float width to set textbox to (default: 400.f)
 */
TextBox::TextBox(const int fontSize, const float width)
{
    // set private vars
    mFontSize = fontSize;
    mWidth = width;
    mHeight = fontSize + (TEXTBOX_PADDING * 2.f);
    mLimit = MAX_TEXT_WIDTH;
    mIsSelected = false;
    mTextString = "";
    mCursorString = "";

    // update mFrame properties
    mFrame.setSize(sf::Vector2f(mWidth, mHeight));
    mFrame.setPosition(sf::Vector2f(0.f, 0.f));
    mFrame.setFillColor(TEXTBOX_FILL_COLOR);
    mFrame.setOutlineColor(TEXTBOX_BORDER_INACTIVE);
    mFrame.setOutlineThickness(-TEXTBOX_BORDER_THICKNESS);

    // load font from file
    if(!mFont.loadFromFile(FONT_PATH))
    {
        std::cout << "unable to load font\n";
    }

    sf::Vector2f position(sf::Vector2f((mFrame.getPosition().x + TEXTBOX_PADDING), (mFrame.getPosition().y + TEXTBOX_PADDING)));
    // set mText properties
    mText.setFont(mFont);
    mText.setCharacterSize(mFontSize);
    mText.setFillColor(TEXTBOX_FONT_COLOR);
    mText.setPosition(sf::Vector2f((mFrame.getPosition().x + TEXTBOX_PADDING), (mFrame.getPosition().y + TEXTBOX_PADDING) - 2.f));
    mText.setString(mTextString);

    mCursor.setFont(mFont);
    mCursor.setCharacterSize(mFontSize);
    mCursor.setFillColor(TEXTBOX_FONT_COLOR);
    mCursor.setPosition(sf::Vector2f((mFrame.getPosition().x + TEXTBOX_PADDING), (mFrame.getPosition().y + TEXTBOX_PADDING)));
    mCursor.setString(mCursorString);
}

/**
 * @brief main function to update the Textbox contents
 * 
 * @param ch int unicode character of key press
 */
void TextBox::update(sf::Event &event)
{
    // if an ascii character is entered, evaluete and perform correct action.
    if (event.type == sf::Event::TextEntered)
    {
        // save unicode value for ease of use.
        int ch = event.text.unicode;

        // end if limit is reached and not backspace
        if (mText.getLocalBounds().width >= mLimit && ch != BACKSPC_CHAR && ch != DELETE_CHAR)
        {
            return;
        }

        // if backspace is pressed
        else if (ch == BACKSPC_CHAR)
        {
            if (mCursorString.length() == 0)
            {
                return;
            }

            // if string is not empty, remove last char
            if (mCursorString.length() == mTextString.length())
            {
                mTextString = mTextString.substr(0, mTextString.length() - 1);
                mCursorString = mCursorString.substr(0, mCursorString.length() - 1);
            }
            else if (mCursorString.length() < mTextString.length())
            {
                std::string pre = mTextString.substr(0, mCursorString.length() - 1);
                std::string post = mTextString.substr(mCursorString.length(), mTextString.length());
                mTextString = pre + post;
                mCursorString = mCursorString.substr(0, mCursorString.length() - 1);
            }
        }
   
        // if delete key is pressed
        else if (ch == DELETE_CHAR)
        {
            // std::cout << "Key: " << key << '\n';
            if (mCursorString.length() < mTextString.length())
            {
                std::string preString, postString;
                preString = mTextString.substr(0, mCursorString.length());
                postString = mTextString.substr(mCursorString.length() + 1, mTextString.length());
                // std::cout << "pre: " << preString << '\n';
                // std::cout << "post: " << postString << '\n';
                mTextString = preString + postString;
            }
        }

        // if ch is within bounds
        else if (ch >= CHAR_LOWER_BOUND && ch <= CHAR_UPPER_BOUND)
        {
            int ch = event.text.unicode;
            // convert to ascii and add to mTextString
            if (mTextString.length() == mCursorString.length())
            {
                mTextString.append(1, static_cast<char>(ch));
                mCursorString.append(1, ' ');
            }
            else
            {
                // string newStr = "";
                std::string tempStr = "";
                tempStr.append(mTextString.substr(0, mCursorString.length()));
                tempStr.append(1, static_cast<char>(ch));
                tempStr.append(mTextString.substr(mCursorString.length(), mTextString.length()));
                mCursorString.append(1, ' ');
                mTextString = tempStr;
            }
        }
    }

    // if not ascii character, check for left and right arrows. move cursor if arrow pressed
    else if (event.type == sf::Event::KeyPressed)
    {
        // store keyboard code for ease of use
        int key = event.key.code;

        // if left or right arrow, move
        if (key == sf::Keyboard::Left || key == sf::Keyboard::Right)
        {
            moveCursor(key);
        }
    }
}

/**
 * @brief draw Textbox to current window.
 * 
 * @param window reference to current window to draw textbox to.
 */
void TextBox::draw(sf::RenderWindow& window)
{
    if (mIsSelected)
    {
        setBorderColor(sf::Color::Blue);
        mCursor.setString(mCursorString + TEXTBOX_CURSOR_CHAR);
    }
    else
    {
        setBorderColor(sf::Color::Black);
        mCursor.setString(mTextString);
    }

    mText.setString(mTextString);
    window.draw(mFrame);
    window.draw(mText);
    window.draw(mCursor);
}

/**
 * @brief Set width of Textbox
 * 
 * @param width float width in pixels of textbox
 */
void TextBox::setWidth(const float width)
{
    mWidth = width;
    mFrame.setSize(sf::Vector2f(mWidth, mHeight));
}

/**
 * @brief set font size of Textbox and resize surrounding RectangleShape
 * 
 * @param fontSize int new font size
 */
void TextBox::setFontSize(const int fontSize)
{
    // set size of text
    mText.setCharacterSize(fontSize);

    // set height of frame relative to fontSize
    mHeight = fontSize + (TEXTBOX_PADDING * 2.f);
    mFrame.setSize(sf::Vector2f(mWidth, mHeight));
}

/**
 * @brief set position of Textbox
 * 
 * @param xPos float horizontal coordinate
 * @param yPos float vertical coordinate
 */
void TextBox::setPosition(const float xPos, const float yPos)
{
    // set positon of mFrame
    mFrame.setPosition(sf::Vector2f(xPos, yPos));

    // set positon of mText relative to mFrame
    mText.setPosition(sf::Vector2f(xPos + TEXTBOX_PADDING, (yPos + TEXTBOX_PADDING)  - 2.f));
    mCursor.setPosition(sf::Vector2f(xPos + TEXTBOX_PADDING, (yPos + TEXTBOX_PADDING)));
}

/**
 * @brief Set thickness/size of Textbox border
 * 
 * @param width float of border thickness
 */
void TextBox::setBorder(const float width)
{
    // set border thickness of frame
    mFrame.setOutlineThickness(-width);
}

/**
 * @brief Set Textbox border color
 * 
 * @param color Color object representing new color value
 */
void TextBox::setBorderColor(const sf::Color color)
{
    // set border color of frame
    mFrame.setOutlineColor(color);
}

/**
 * @brief Set max width of Text object
 * 
 * @param limit 
 */
void TextBox::setLimit(const int limit)
{
    // set max characters that can be typed
    mLimit = limit;
}

/**
 * @brief Change current selected state of Textbox
 * 
 * @param selected bool value to set selected state to. true/false.
 */
void TextBox::setSelect(const bool selected)
{
    // set if textbox is selected
    mIsSelected = selected;
}

/**
 * @brief return current size of Textbox object as a Vector2f object
 * 
 * @return sf::Vector2f current Textbox size
 */
sf::Vector2f TextBox::getSize() const
{
    return mFrame.getSize();
}

/**
 * @brief Return current position of Textbox
 * 
 * @return sf::Vector2f  of current postion relative to the RenderWindow object
 */
sf::Vector2f TextBox::getPosition() const
{
    return mFrame.getPosition();
}

/**
 * @brief return current thickness of border as a float
 * 
 * @return float current value of border thickness
 */
float TextBox::getBorder() const
{
    return mFrame.getOutlineThickness();
}

/**
 * @brief return current color value
 * 
 * @return sf::Color current color value as a SFML Color object
 */
sf::Color TextBox::getColor() const
{
    return mFrame.getOutlineColor();
}

/**
 * @brief get current max width of Text object.
 * 
 * @return int max width of Text object
 */
int TextBox::getLimit() const
{
    return mLimit;
}

/**
 * @brief return boolean value stating if textbox is currently selected. true if selecte, false
 *        if not selected 
 * 
 * @return true if Textbox object is selected
 * @return false if Textbox object is not selected
 */
bool TextBox::isSelected() const
{
    return mIsSelected;
}

/**
 * @brief helper function to move cursor left <=> right
 * 
 * @param ch int unicode character input from keyboard.
 */
void TextBox::moveCursor(const int ch)
{
    // std::cout << ch << '\n';
    // std::cout << "Right: " << sf::Keyboard::Right << '\n';
    // std::cout << "Left: " << sf::Keyboard::Left << '\n';
    if (ch == sf::Keyboard::Right)
    {
        if (mCursorString.length() < mTextString.length())
        {
            mCursorString.append(1, ' ');
        }
    }

    if (ch == sf::Keyboard::Left)
    {
        if (mCursorString.length() > 0)
        {
            mCursorString = mCursorString.substr(0, mCursorString.length() - 1);
        }
    }
    // mCursor.setString(mCursorString);
}

/**
 * @brief function to handle input from keyboard while textbox is active.
 * 
 * @param key 
 */
// void TextBox::keyPress(const int key)
// {
//     if (key == sf::Keyboard::Left || key == sf::Keyboard::Right)
//     {
//         moveCursor(key);
//     }
//     else if (key == sf::Keyboard::Delete)
//     {
//         // std::cout << "Key: " << key << '\n';
//         if (mCursorString.length() < mTextString.length())
//         {
//             std::string preString, postString;
//             preString = mTextString.substr(0, mCursorString.length());
//             postString = mTextString.substr(mCursorString.length() + 1, mTextString.length());
//             // std::cout << "pre: " << preString << '\n';
//             // std::cout << "post: " << postString << '\n';
//             mTextString = preString + postString;
//         }
//     }
// }