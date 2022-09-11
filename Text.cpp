#include "Text.hpp"
#include "GameLogic.hpp"

Text::Text()
{
	score = 0;

	textFont = TTF_OpenFont("Assets/Verdana_Bold.ttf", 30);
	textFontColor = { 255, 255, 255, 255 };

	textTexture = TextureManager::LoadTextTexture(textFont, std::to_string(score).c_str(), &textFontColor, &destRect);

	destRect.x = 750;
	destRect.y = 100;
}

Text::~Text()
{
}

void Text::Update()
{
	score += totalScore;

	if (score / 10 == 0)
	{
		destRect.x = 750;
	}
	else if (score / 100 == 0)
	{
		destRect.x = 745;
	}
	else if (score / 1000 == 0)
	{
		destRect.x = 733;
	}
	else if (score / 10000 == 0)
	{
		destRect.x = 723;
	}
	else if (score / 100000 == 0)
	{
		destRect.x = 715;
	}

	textTexture = TextureManager::LoadTextTexture(textFont, std::to_string(score).c_str(), &textFontColor, &destRect);
}

void Text::Render()
{
	SDL_RenderCopy(WindowManager::renderer, textTexture, NULL, &destRect);
}
