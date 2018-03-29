//
//  UIButton.hpp
//  Xcode
//
//  Created by Valentin Dufois on 25/01/2018.
//  Copyright © 2018 Valentin Dufois. All rights reserved.
//

#ifndef UIButton_hpp
#define UIButton_hpp

//////////////////////
//Forward declarations
class Mesh;
class Font;

#include "../UIElement.hpp"

enum UIButtonType
{
	UI_BUTTON_TEXT,
	UI_BUTTON_GRAPHIC
};

enum UIButtonTextAlign
{
	UI_TEXT_LEFT,
	UI_TEXT_CENTER,
	UI_TEXT_RIGHT
};

class UIButton: public UIElement
{
public:
	UIButton(const UIButtonType &type, const uint &posX, const uint &posY, const uint &width, const uint &height);

	/**
	 Set the font and font size for the button
	 This will be ignored if the button type is not set to TEXT

	 @param font The font to use
	 @param fontSize The font size to use
	 */
	void setFont(Font * font, const float &fontSize);

	/**
	 Set text alignement.
	 Default is centered

	 @param alignment Alignments
	 */
	void setCaptionAlign(const UIButtonTextAlign &alignment);

	/**
	 Set the text color
	 Text background is transparent when idle, and idleColored when selected

	 @param idleColor Text idle color
	 @param selectedColor Text selected color
	 */
	void setTextColors(const glm::vec4 &idleColor, const glm::vec4 &selectedColor);

	void setBackColors(const glm::vec4 &idleColor, const glm::vec4 &selectedColor);

	/**
	 Set the caption to display on the button

	 @param caption text to display
	 */
	void setCaption(const std::u16string &caption);

	/**
	 Set the textures used by the item

	 @param idleTexture Texture GL ID
	 @param activeTexture Texture GL ID
	 */
	void setTextures(const GLuint &idleTexture, const GLuint &activeTexture);

	/**
	 Set the textures used by the item using their rId

	 @param idleTexture RessourceEngine Image ID
	 @param activeTexture RessourceEngine Image ID
	 */
	void setTextures(const rId &idleTexture, const rId &activeTexture);

	/**
	 Update dimensions of the item

	 @param width New width
	 @param height new height
	 */
	void setDimensions(const float &width, const float &height);

	/**
	 Update position of the item

	 @param posX New posX of the item
	 @param posY New posY of the item
	 */
	void setPosition(const float &posX, const float &posY);

	/**
	 Mark the item as selected
	 */
	void select();

	/**
	 Mark the item as deselected
	 */
	void deSelect();

	/**
	 Display the button on the screen
	 */
	void print();

	~UIButton();

private:
	UIButtonType m_type;

	void refreshGeometry();
	void refreshTextColor();
	void setTextPosition();

	//The tile
	Mesh * m_tile = nullptr;
	Mesh * m_backTile = nullptr;

	//The textures
	GLuint m_idleTexture;
	GLuint m_activeTexture;

	//The colors
	glm::vec4 m_idleColor = glm::vec4(0, 0, 0, 1);
	glm::vec4 m_selectedColor = glm::vec4(1, 1, 1, 1);
	glm::vec4 m_backIdleColor = glm::vec4(0, 0, 0, 0.0);
	glm::vec4 m_backSelectedColor = glm::vec4(0, 0, 0, 1.0);

	//The text
	Font * m_font;
	float m_fontSize;
	UIButtonTextAlign m_textAlign;
	std::u16string m_caption;
};

#endif /* UIButton_hpp */
