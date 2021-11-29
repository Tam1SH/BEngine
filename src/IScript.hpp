#pragma once

class IScript {
public:
	virtual void init() = 0;
	virtual void run() = 0;
	virtual void destroy() = 0;
};
