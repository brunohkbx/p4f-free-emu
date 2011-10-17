// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------

// GS-N 0.99.60T Status : Completed
// GS-N 1.00.18	0x0049EC20	JPN - Completed
// GS-CS 1.00.18	0x0049EC20	JPN - Completed

#include "..\Header\stdafx.h"
#include "..\Header\CLoginCount.h"



CLoginCount::CLoginCount()
{
	this->Init();
}

//------------------------------------------------------------

void CLoginCount::Init()
{
	this->m_count=0;
}

CLoginCount::~CLoginCount()
{
	return;
}

//------------------------------------------------------------

void CLoginCount::Add()
{
	this->m_count++;
}

//------------------------------------------------------------

void CLoginCount::Delete()
{
	this->m_count--;

	if ( this->m_count < 0 )
	{
		this->m_count = 0;
	}
}

//------------------------------------------------------------

int CLoginCount::Get()
{
	return this->m_count;
}

//------------------------------------------------------------

