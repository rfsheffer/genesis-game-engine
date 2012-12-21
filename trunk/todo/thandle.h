//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: Works in conjunction with the memory pool. A pointer which uses operator overloads
//			to determine if the memory pointed to is still valid, and will return NULL memory
//			no longer exists.
//
//==========================================================================//

#ifndef T_HANDLE_H
#define T_HANDLE_H

#include "mem_pool.h"

//-----------------------------------------------------------------------------
// Type handler Class
//-----------------------------------------------------------------------------
template<typename T>
class T_Handle
{
public:

	T_Handle();
	T_Handle(T *pVal);

	T*		Get() const;
	void	Set(T* pVal);

	T_Handle<T>& operator=(const T *val);
	T_Handle<T>& operator=(const T_Handle &val);

	bool	operator!() const;
	bool	operator !=(const T *val) const;
	bool	operator !=(const T_Handle &other) const;
	bool	operator ==(const T *val) const;
	bool	operator ==(const T_Handle &other) const;
	bool	operator <(const T_Handle &other) const;

	T*		operator->() const;
	operator T*();
	operator T*() const;

private:

	T	*pData;
};

//-----------------------------------------------------------------------------
// Purpose: Construction
//-----------------------------------------------------------------------------
template<typename T>
T_Handle<T>::T_Handle()
{
	pData = NULL;
}

template<typename T>
T_Handle<T>::T_Handle(T *pVal)
{
	Set(pVal);
}

//-----------------------------------------------------------------------------
// Purpose: Gets the memory, checking if the memory is available
//-----------------------------------------------------------------------------
template<typename T>
T* T_Handle<T>::Get() const
{
	if(pData == NULL || !MemPool::IS_POOL_MEMORY(pData))
		return NULL;

	return pData;
}

//-----------------------------------------------------------------------------
// Purpose: Sets what the smart pointer is pointing to
//-----------------------------------------------------------------------------
template<typename T>
void T_Handle<T>::Set(T* pVal)
{
	if(pVal == NULL || !MemPool::IS_POOL_MEMORY(pVal))
	{
		pData = NULL;
		return;
	}

	pData = pVal;
}

//-----------------------------------------------------------------------------
// Purpose: Class Smart Pointer operators
//-----------------------------------------------------------------------------
template<typename T>
inline T_Handle<T>::operator T *() 
{ 
	return Get(); 
}

template<typename T>
inline T_Handle<T>::operator T *() const
{ 
	return Get(); 
}

template<typename T>
T_Handle<T>& T_Handle<T>::operator=(const T *val)
{
	Set(val);
	return *this;
}

template<typename T>
T_Handle<T>& T_Handle<T>::operator=(const T_Handle &val)
{
	Set(val.Get());
	return *this;
}

template<typename T>
inline bool T_Handle<T>::operator!() const
{
	return !Get();
}

template<typename T>
inline bool T_Handle<T>::operator!=(const T *val) const
{
	return Get() != val;
}

template<typename T>
bool T_Handle<T>::operator!=(const T_Handle &other) const
{
	return pData != other.Get();
}

template<typename T>
inline bool T_Handle<T>::operator==(const T *val) const
{
	return Get() == val;
}

template<typename T>
bool T_Handle<T>::operator==(const T_Handle &other) const
{
	return pData == other.Get();
}

template<typename T>
bool T_Handle<T>::operator<(const T_Handle &other) const
{
	return pData < other.Get();
}

template<typename T>
T* T_Handle<T>::operator->() const
{
	return Get();
}

#endif // T_HANDLE_H