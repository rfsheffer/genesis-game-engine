//
//  file_smd.h
//  Purpose: A container class which holds elements in sequential memory and will
//  resize to accommodate all elements.
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef CONTAINER_VECTOR_H
#define CONTAINER_VECTOR_H

#ifdef _WIN32
#pragma once
#endif

namespace Container
{

//------------------------------------------------------------
// Purpose: Memory Management functions, Copy and Destructor.
//------------------------------------------------------------
template <typename T>
inline void MemoryCopyConstruct( T *pMemory, const T &src )
{
	::new( pMemory ) T(src);
}

template <typename T>
inline void MemoryDestruct( T* pMemory )
{
	pMemory->~T();
}

//------------------------------------------------------------
// Purpose: Growable Array of elements.
//------------------------------------------------------------
template<typename T>
class Vector
{
public:

	// Constructor: Pass in an element and a number of memory slots you want created.
	Vector();
	Vector( T* elem, unsigned int numelements = 0 );
	~Vector();

	// Operators for element access via array style.
	T& operator[]( int i ){ return p_elements[ i ]; }
	const T& operator[]( int i ) const { return p_elements[ i ]; }

	// Removes all elements, but does not resize memory.
	void RemoveAllElements();

	// Gets an element by array index.
	T& Element( unsigned int i ){ return p_elements[i]; }

	// Gets the very first element.
	T* Base();

	// Adds a new element to position.
	unsigned int AddElement( unsigned int pos, const T& elem );

	// Add to position 0 in the array. Shift other elements over.
	unsigned int AddElementToFront( const T& elem );

	// Add to position m_iNumElements in the array.
	unsigned int AddElementToBack( const T& elem );

	// Gets the number of valid elements.
	unsigned int Count() const { return m_iNumElements; }

private:

	// Shifts all elements after pos to the right by one.
	void ShiftElementsRight( unsigned int elem, unsigned int num = 1 );

	// Grows the vector by the variable amount.
	void GrowVector( unsigned int num = 1 );

	// Checks and makes sure the number of slots will be free.
	void EnsureSize( unsigned int num );

	// Number of valid elements.
	unsigned int m_iNumElements;

	// Number of T size Memory slots allocated.
	unsigned int m_iNumMemoryElements;

	// Elements Array, All allocated memory is placed here.
	T *p_elements;

};

//------------------------------------------------------------
// Construction / Deconstruction
//------------------------------------------------------------
template <typename T>
Vector<T>::Vector() : p_elements( 0 ), m_iNumElements( 0 ), m_iNumMemoryElements( 0 )
{

}

template <typename T>
Vector<T>::Vector( T* elem, unsigned int numelements ) : p_elements( 0 ), m_iNumElements( 0 ), m_iNumMemoryElements( 0 )
{
	// Allocate a bunch of new elements if asked.
	if ( numelements > 0 )
	{
		p_elements = (T *)malloc( numelements * sizeof(T) );
		m_iNumMemoryElements = numelements;
	}
}

template <typename T>
Vector<T>::~Vector()
{
	// First get rid of all the element.
	for (int i = m_iNumElements; i >= 0; --i )
	{
		MemoryDestruct(&Element(i));
	}

	m_iNumElements = 0;

	// Get rid of the allocated memory.
	if ( p_elements )
	{
		free( (void*)p_elements );
		p_elements = 0;
	}

	m_iNumMemoryElements = 0;
}

//------------------------------------------------------------
// Purpose: Removes all elements, but does not resize memory.
//------------------------------------------------------------
template <typename T>
void Vector<T>::RemoveAllElements()
{
	// First get rid of all the element.
	for (int i = m_iNumElements; i >= 0; --i )
	{
		MemoryDestruct(&Element(i));
	}

	m_iNumElements = 0;
}

//------------------------------------------------------------
// Purpose: Grows Vector
//------------------------------------------------------------
template <typename T>
void Vector<T>::GrowVector( unsigned int num )
{
	// First time grow or not?
	if( m_iNumMemoryElements )
	{
		unsigned int newsize = (m_iNumMemoryElements + num) * sizeof(T);
		p_elements = (T *)realloc( p_elements, newsize );
		m_iNumMemoryElements += num;
	}
	else
	{
		unsigned int newsize = (m_iNumMemoryElements + num) * sizeof(T);
		p_elements = (T *)malloc( newsize );
		m_iNumMemoryElements += num;
	}
}

//------------------------------------------------------------
// Purpose: Returns first element.
//------------------------------------------------------------
template <typename T>
T* Vector<T>::Base()
{
	return p_elements;
}

//------------------------------------------------------------
// Purpose: Returns first element.
//------------------------------------------------------------
template <typename T>
void Vector<T>::ShiftElementsRight( unsigned int elem, unsigned int num )
{
	// Num elements greater than 0, pos isn't out of bounds.
    // If element is being placed at m_iNumElements, no need to shift.
	if ( (m_iNumElements > 0) && (elem < m_iNumElements) )
	{
		// Determine the number of elements to move.

		unsigned int num_to_move = m_iNumElements - elem - num + 1; // + 1 to account for object zero.

		memmove( &Element( elem+num ), &Element( elem ), num_to_move * sizeof(T) );
	}
}

//------------------------------------------------------------
// Purpose: Adds new element.
//------------------------------------------------------------
template <typename T>
unsigned int Vector<T>::AddElement( unsigned int pos, const T& elem )
{
	// Clamp this down, cant go higher than m_iNumElements.
	if ( pos > m_iNumElements )
	{
		pos = m_iNumElements;
	}

	// Grow the vector if needed, and shift everything over.
	GrowVector();
	ShiftElementsRight( pos );
	MemoryCopyConstruct( &Element(pos), elem );
	m_iNumElements++;
    
    return pos;
}

//------------------------------------------------------------
// Purpose: Add to position 0 in the array. Shift other elements over.
//------------------------------------------------------------
template <typename T>
unsigned int Vector<T>::AddElementToFront( const T& elem )
{
	return AddElement( 0, elem );
}

//------------------------------------------------------------
// Purpose: Add to position m_iNumElements in the array.
//------------------------------------------------------------
template <typename T>
unsigned int Vector<T>::AddElementToBack( const T& elem )
{
	return AddElement( m_iNumElements, elem );
}
    
}

#endif // CONTAINER_VECTOR_H