#pragma once

#include <rpc.h>

template<class T>
class Asset
{
public:
	void a()
	{
		CoCreateGuid(guid);
	}
private:
	GUID guid;
};