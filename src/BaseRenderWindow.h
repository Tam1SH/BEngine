#pragma once
class BaseRenderWindow
{
public:
	virtual void ResizeCallback() = 0;

	virtual void CreateSurface() = 0;

};

