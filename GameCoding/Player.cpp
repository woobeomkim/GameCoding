#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Missile.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "LineMesh.h"

Player::Player() : Object(ObjectType::Plaer)
{
}

Player::~Player()
{
}

void Player::Init()
{
	// TODO : Data
	// �����ͽ�Ʈ ���� ���̼�
	// �����ͺ��̽� ����Ŭ ���̿���ť��
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;

}

void Player::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	// �Ÿ� = �ð� * �ӵ�

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= _stat.speed * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += _stat.speed * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= _stat.speed * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += _stat.speed * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		_barrelAngle += 10 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		_barrelAngle -= 10 * deltaTime;
	}
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());
		missile->SetAngle(_barrelAngle);

		GET_SINGLE(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	//Utils::DrawCircle(hdc, _pos, 50);
	const LineMesh* mesh = GET_SINGLE(ResourceManager)->GetLineMesh(L"Player");
	if (mesh)
		mesh->Render(hdc , _pos);
	
	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	Utils::DrawLine(hdc, _pos, GetFirePos());

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

Pos Player::GetFirePos()
{
	Pos firePos = _pos;

	firePos.x += _barrelLength * ::cos(_barrelAngle);
	firePos.y -= _barrelLength * ::sin(_barrelAngle);
	return firePos;
}
