#include "GUI.h"


void GUI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	std::vector<sf::Text> texts;

	for (short i = 0; i < m_respawns.size(); ++i)
	{
		sf::Text tempText;
		tempText.setFont(*m_font);
		tempText.setCharacterSize(m_textSize);
		tempText.setPosition(0, 0);
		tempText.setString("Player " + std::to_string(i+1) + std::string(" respawns:") + std::to_string(m_respawns[i]));

		if (i == 1)
		{
			tempText.setPosition(tempText.getPosition().x + m_screenWidth - tempText.getGlobalBounds().width-10, tempText.getPosition().y);
			tempText.setColor(sf::Color::Green);
		}

		texts.push_back(tempText);
		target.draw(texts[i], states);
	}

	if (m_whoWin.second)
	{
		sf::Text winText;
		sf::RectangleShape thing;
		thing.setSize(sf::Vector2f(m_screenWidth, m_screenHeight));
		thing.setFillColor(sf::Color(255, 255, 255, 200));

		winText.setFont(*m_font);
		winText.setCharacterSize(m_textSize);
		winText.setColor(sf::Color::Black);
		winText.setString("Player " + std::to_string(m_whoWin.first + 1) + " wins!");
		winText.setPosition(m_screenWidth / 2 - winText.getGlobalBounds().width, m_screenHeight / 2 - winText.getGlobalBounds().height);

		target.draw(thing, states);
		target.draw(winText, states);
		if (m_optionPlayAgain != nullptr)
		{
			target.draw(*m_optionPlayAgain, states);
			target.draw(*m_optionExit, states);
			target.draw(*m_optionReturnMenu, states);
		}
	}
}

GUI::GUI()
{
	m_optionPlayAgain = nullptr;
	m_optionReturnMenu = nullptr;
	m_optionExit = nullptr;
}

GUI::~GUI()
{
	if (m_optionPlayAgain != nullptr)
	{
		delete m_optionPlayAgain;
		delete m_optionExit;
		delete m_optionReturnMenu;
	}
}

void GUI::Init(sf::Font * font, short textSize, int screenWidth, int screenHeight)
{
	m_font = font;
	m_textSize = textSize;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void GUI::UpdateStats(std::vector<Player*>* players, short mouseX, short mouseY)
{
	m_respawns.resize(players->size());

	for (short i = 0; i < players->size(); ++i)
	{
		m_respawns[i] = (*players)[i]->GetRespawnsCount();
		if ((*players)[i]->GetWin())
		{
			m_whoWin.first = i;
			m_whoWin.second = true;
			if (m_optionPlayAgain == nullptr)
			{
				m_optionPlayAgain = new Option(m_font, "Play Again ", 30, m_screenWidth / 2 + 25, m_screenHeight / 2 - 60, sf::Color::Blue, sf::Color::White);
				m_optionExit = new Option(m_font, "     Exit    ", 30, m_screenWidth / 2 + 25, m_screenHeight / 2, sf::Color::Blue, sf::Color::White);
				m_optionReturnMenu = new Option(m_font, "Return Menu", 30, m_screenWidth / 2 + 25, m_screenHeight / 2 - 120, sf::Color::Blue, sf::Color::White);
			}
			
			break;
		}
		else
		{
			m_whoWin.second = false;
			if (m_optionPlayAgain != nullptr)
			{
				delete m_optionPlayAgain;
				delete m_optionExit;
				delete m_optionReturnMenu;
				m_optionPlayAgain = nullptr;
				m_optionReturnMenu = nullptr;
				m_optionExit = nullptr;
			}
		}
	}

	if (m_optionPlayAgain != nullptr)
	{
		m_optionPlayAgain->Update(mouseX, mouseY);
		m_optionExit->Update(mouseX, mouseY);
		m_optionReturnMenu->Update(mouseX, mouseY);
	}
}

void GUI::UpdateStats(std::vector<Player*>* players, short mouseX, short mouseY, bool & playAgain, bool & exit, bool & enterMenu)
{
	UpdateStats(players, mouseX, mouseY);

	if (m_optionPlayAgain == nullptr)
	{
		return;
	}

	playAgain = m_optionPlayAgain->IsClicked();
	exit = m_optionExit->IsClicked();
	if (m_optionReturnMenu->IsClicked())
	{
		enterMenu = true;
		exit = true;
	}
}

