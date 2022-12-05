#include "Text.hpp"
#include "GameLogic.hpp"
#include "BestScoreManager.hpp"
using namespace std;

// �����̰� ���� ��������� scoreText�� �о�ͼ� ������ ����� + ��,õ,�� �� ���� ��ġ ���
extern int cuBest;

Text::Text(int xPos, int yPos)
{
	scoreText = BestSc();

	textFont = TTF_OpenFont("Assets/Verdana_Bold.ttf", 30);
	textFontColor = { 255, 255, 255, 255 };

	textTexture = TextureManager::LoadTextTexture(textFont, std::to_string(scoreText).c_str(), &textFontColor, &destRect);

	destRect.x = xPos;
	destRect.y = yPos;
}

Text::Text(const char* endText)
{

	textFont = TTF_OpenFont("Assets/Verdana_Bold.ttf", 30);
	textFontColor = { 255, 255, 255, 255 };

	textTexture = TextureManager::LoadTextTexture(textFont, endText, &textFontColor, &destRect);

	destRect.x = 550;
	destRect.y = 360;
}

Text::Text(const char* tutorText, bool directFlag) {

	

	//false: ���� ������� ��� / true: ������ ������� ���
	if (directFlag == false) {
		textFont = TTF_OpenFont("Assets/Verdana_Bold.ttf", 30); 
		textFontColor = { 187, 173, 160, 255 };

		textTexture = TextureManager::LoadTextTexture(textFont, tutorText, &textFontColor, &destRect);

		destRect.x = 15;
		destRect.y = 150;
	}
	else{
		textFont = TTF_OpenFont("Assets/Verdana_Bold.ttf", 30);
		textFontColor = { 187, 173, 160, 255 };

		textTexture = TextureManager::LoadTextTexture(textFont, tutorText, &textFontColor, &destRect);
		
		destRect.x = 900;
		destRect.y = 150;
	}
	

}
Text::~Text()
{
}

void Text::Update()
{
	scoreText = totalScore;

	if (scoreText / 10 == 0)
	{
		destRect.x = 750;
	}
	else if (scoreText / 100 == 0)
	{
		destRect.x = 745;
	}
	else if (scoreText / 1000 == 0)
	{
		destRect.x = 733;
	}
	else if (scoreText / 10000 == 0)
	{
		destRect.x = 723;
	}
	else if (scoreText / 100000 == 0)
	{
		destRect.x = 715;
	}
	else if (scoreText / 1000000 == 0)
	{
		destRect.x = 700;
	}

	textTexture = TextureManager::LoadTextTexture(textFont, std::to_string(scoreText).c_str(), &textFontColor, &destRect);
}

void Text::Render()
{
	SDL_RenderCopy(WindowManager::renderer, textTexture, NULL, &destRect);

	
	
}
