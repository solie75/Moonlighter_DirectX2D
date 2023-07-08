#pragma once
#include "Header.h"

class CEntity
{
private:
	std::wstring mName;
	UINT64 mID;

public:
	CEntity();
	virtual ~CEntity();

	void SetName(const std::wstring& name) { mName = name; }
	std::wstring GetName() { return mName; }
	void SetID(UINT64 id) { mID = id; }
	UINT64 GetID() { return mID; }
};