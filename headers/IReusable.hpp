#pragma once
class IReusable
{
public:
	virtual void release() = 0;
	virtual ~IReusable() {}
};

