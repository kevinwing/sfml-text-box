/**
 * @file textbox.hpp
 * @author Kevin Wing (kevinrwing@gmail.com)
 * @brief A Class for creating a textbox within the window
 * @version 0.1
 * @date 2021-05-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

// #include "settings.hpp"

// using std::string;

/* TextBox default settings */

// Font settings
const std::string   FONT_PATH                   = "assets/SourceCodePro-Regular.ttf";
const unsigned      FONT_SIZE                   = 16.f;

// Postion settings
const float         TEXTBOX_X                   = 100.f;
const float         TEXTBOX_Y                   = 50.f;

// Size settings
const float         TEXTBOX_WIDTH               = 400.f;
const float         TEXTBOX_BORDER_THICKNESS    = 2.f;
const float         TEXTBOX_PADDING             = 5.f + TEXTBOX_BORDER_THICKNESS;

// Color settings
const sf::Color     TEXTBOX_FILL_COLOR          = sf::Color::White;
const sf::Color     TEXTBOX_FONT_COLOR          = sf::Color::Black;
const sf::Color     TEXTBOX_BORDER_ACTIVE       = sf::Color::Blue;
const sf::Color     TEXTBOX_BORDER_INACTIVE     = sf::Color::Black;

// Cursor settings
const std::string   TEXTBOX_CURSOR_CHAR         = "_";


// character check values
const int           BACKSPC_CHAR                = 8;
const int           DELETE_CHAR                 = 127;
const int           ENTER_CHAR                  = 13;

// ASCII bounds checking values
const int           CHAR_UPPER_BOUND            = 126;
const int           CHAR_LOWER_BOUND            = 32;

// Max Text length settings
const unsigned      MAX_CHAR_LIMIT              = 62;
const float         MAX_TEXT_WIDTH              = TEXTBOX_WIDTH - (TEXTBOX_PADDING * 2);

/**
 * @brief A textbox module to create a customizable textbox entry in SFML.
 * 
 */
class TextBox
{
private:
    sf::RectangleShape mFrame;
    sf::Text mText;
    sf::Text mCursor;
    sf::Font mFont;
    int mFontSize;
    float mWidth;
    float mHeight;
    std::string mTextString;
    std::string mCursorString;
    bool mIsSelected;
    unsigned mLimit;

    void moveCursor(const int key);

public:
    TextBox(const int fontSize=FONT_SIZE, const float width=TEXTBOX_WIDTH);
    // ~Textbox();

    // void setSize(const int fontSize, const float width);
    void setFontSize(const int textSize);
    void setWidth(const float width);
    void setPosition(const float xPos, const float yPos);
    void setBorder(const float width);
    void setBorderColor(const sf::Color color);
    void setFillColor(const sf::Color color);
    void setCharacterColor(const sf::Color color);
    void setLimit(const int limit);
    void setSelect(const bool selected);
    bool isSelected() const;

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
    float getBorder() const;
    sf::Color getColor() const;
    int getLimit() const;

    void keyPress(const int key);
    
    void update(sf::Event &event);
    void draw(sf::RenderWindow& window);
};
