#pragma once
#include "Scene.h"
class DevScene :
    public Scene
{
public:
	DevScene();
	virtual ~DevScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	Pos _playerPos = { 300,300 };
	float _speed = 1000;
};

