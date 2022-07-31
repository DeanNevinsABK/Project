#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberOfLives = 3;

Player::Player(ActorColor color)
	: PlacableActor(0, 0, color)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)
{

}

bool Player::HasKey()
{
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return true;// HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{
	if (m_pCurrentKey)
	{
		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);

	std::cout << "@";
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}
