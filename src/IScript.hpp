#pragma once

class IScript {
public:
	virtual void Initialization() = 0;
	virtual void Run() = 0;
	virtual void Destroy() = 0;
};
