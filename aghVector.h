/**
* \file aghVector.h
* \author Maciej Rajs
* \brief Zawiera szablon klasy aghVectror dziedziczacej po aghContainer
*/

#ifndef AGHVECTOR_H
#define AGHVECTOR_H

#include <iostream>
#include "aghContainer.h"
#include "aghException.h"

/**
* \class aghVector
* \author Maciej Rajs
* \brief szablon klasy wektora dziedziczacy po aghContainer
*/

template<typename T> class aghVector : public aghContainer<T>
{
  private:
    int length;
    T* tab;

  public:
    /// \brief Konstruktor domyslny
    aghVector( void );

    /// \brief Konstruktor
    aghVector( const aghContainer<T> & container );

    /// \brief Konstruktor kopiujacy
    aghVector( const aghVector<T> & container );

    /// \brief Destruktor
    ~aghVector( void );

    /// \brief Operator przypisania
    aghVector<T> & operator=( aghVector<T> const & right );

    /// \brief Wstawia element podany w 2 argumencie w okreslone w pierwszym argumencie miejsce
    bool insert( int index, T const & element );

    /// \brief Zwraca element o podanym indeksie
    T & at( int index ) const;

    /// \brief Zwraca rozmiar wektora
    int size( void ) const;

    /// \brief Usuwa element o podanym indeksie
    bool remove( int index );

  private:
    void rewriteElements( aghContainer<T> const & element );
    bool removeLastElement();
};

template <typename T> aghVector<T>::aghVector( void )
{
    length = 0;
    tab = NULL;
}

template <typename T> aghVector<T>::aghVector( aghContainer<T> const & container )
{
    if ( ( length = element.size() ) == 0 )
        tab = NULL;
    else
        rewriteElements( element );
}

template <typename T> void aghVector<T>::rewriteElements( aghContainer<T> const & container )
{
    tab = new T[ length ];

    for( int i = 0 ; i < length ; i++ )
        tab[ i ] = element[ i ];
}

template <typename T> aghVector<T>::aghVector( aghVector<T> const & element )
{
    if( tab != NULL )
        delete [] tab;

    if( ( length = element.size() ) == 0 )
        tab = NULL;
    else
        rewriteElements( element );
}

template <typename T> aghVector<T>::~aghVector( void )
{
    this -> clear();
}

template <typename T> aghVector<T> & aghVector<T>::operator=( aghVector<T> const & right )
{
    if( this != &right )
    {
        T* tmp = new T[ right.length ];

        for( int i = 0 ; i < right.length ; i++ )
            tmp[ i ] = right.tab[ i ];

        if( tab != NULL )
            delete [] tab;

        tab = tmp;
        length = right.length;
    }
    return *this;
}

template <typename T> bool aghVector<T>::insert( int index, T const & element )
{
    if( index > length || index < 0 )
        return false;

    T* tmp = new T[ length + 1 ];
    tmp[ index ] = element;           //wpisuje element w odpowiednim miejscu

    int i = 0, j = 0;
    while( i != length )                        //dopoki nie przejdziemy wszystkich elementow z tab przepisuje je
    {                                           //do nowej tablicy z wylaczeniem elementu do ktorego wpisujemy
        while( i != length && j != index )      // (pomija iteracje gdy j == index)
        {
            tmp[ j ] = tab[ i ];
            i++;
            j++;
        }
        j++;
    }

    if( tab != NULL )
        delete [] tab;
    tab = tmp;
    length++;

    return true;
}

template <typename T> T& aghVector<T>::at( int index ) const
{
    if( index >= length || index < 0 )
        throw aghException( -1, "Out of range" );
    else
        return tab[ index ];
}

template <typename T> int aghVector<T>::size( void ) const
{
    return length;
}

template <typename T> bool aghVector<T>::remove( int index )
{
    if( index >= length || index < 0)
        return false;

    if( index == 0 && length == 1 )
        return removeLastElement();

    T* tmp = new T[ length - 1 ];

    int i = 0, j = 0;
    while( i != length + 1 )                // jak w insert przepisujemy wszystkie elementy, ale pomijajac usuwany
    {                                       // warunek length+1, bo inkrementujemy i na koncu petli
        while( i != length && i != index )
        {
            tmp[ j ] = tab[ i ];
            i++;
            j++;
        }
        i++;
    }

    if( tab != NULL )
        delete [] tab;
    tab = tmp;
    length--;

    return true;
}

template <typename T> bool aghVector<T>::removeLastElement( void )
{
    length = 0;
    delete [] tab;
    tab = NULL;
    return true;
}

#endif // AGHVECTOR_H
