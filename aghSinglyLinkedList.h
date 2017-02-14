/**
* \file aghSinglyLinkedList.h
* \author Maciej Rajs
* \brief Zawiera szablon klasy aghSlist - listy jednokierunkowej dziedziczacej po aghContainer
*/

#ifndef AGHSLIST_H
#define AGHSLIST_H

#include <iostream>
#include "aghContainer.h"
#include "aghException.h"

/**
* \class aghSlist
* \author Maciej Rajs
* \brief szablon klasy listy jednokierunkowej
*/
template<typename T> class aghSlist : public aghContainer<T>
{
  private:
    /// \class Node
    /// \brief Klasa pojedynczego elementu listy, uzywana jedynie przez metody aghSlist
    class Node
    {
      public:
        Node * next;
        T value;

        Node( T _value )
        {
            value = _value;
            next = NULL;
        }
    };

    Node * first;               //wskaznik na pierwszy element listy
    int length;					//przechowuje ilosc elementow w liscie

  public:

    /// \brief Konstruktor domyslny
    aghSlist() : first( NULL ), length( 0 ){};

    /// \brief Konstruktor
    aghSlist( const aghContainer<T> & container );

    /// \brief Konstruktor kopiujacy
    aghSlist( const aghSlist<T> & container );

    /// \brief Destruktor
    ~aghSlist( void );

    /// \brief Operator przypisania
    aghSlist<T> & operator=( aghSlist<T> const & right );

    /// \brief Wstawia element o indeksie podanym w 2 argumencie w okreslone w pierwszym argumencie miejsce
    /// \return Zwraca true w przypadku sukcesu, false w przypadku porazki
    bool insert( int index, T const & element );

    /// \brief Zwraca element o podanym indeksie
    T& at( int index ) const;

    /// \brief Zwraca rozmiar listy
    int size( void ) const;

    /// \brief Usuwa element o podanym indeksie
    /// \return Zwraca true w przypadku sukcesu, false w przypadku porazki
    bool remove( int index );

  private:
    void insertAtBeginning( Node * newNode );
    void insertAtEnd( Node * newNode );
    void insertAtMiddle( int index, Node * newNode );
    void removeLast( Node ** deleted );
    void removeFirst( Node ** deleted );
    void removeFromMiddle( int index, Node ** deleted );

    Node * iterateToIndex( int index )
    {
        Node * actual = first;
        for( int i = 0 ; i < index - 1 ; i++ )
            actual = actual -> next;
        return actual;
    }
};

template <typename T> aghSlist<T>::aghSlist( aghContainer<T> const & container )
{
    length = 0;
    first = NULL;
    for( int i = 0 ; i < container.size() ; i++ )
        insert( i, container.at( i ) );
}

template <typename T> aghSlist<T>::aghSlist( const aghSlist<T> & container )
{
    length = 0;
    first = NULL;
    for( int i = 0 ; i < container.size() ; i++ )
        insert( i, container.at( i ) );
}

template <typename T> aghSlist<T>::~aghSlist( void )
{
    this -> clear();
}

template <typename T> aghSlist<T> & aghSlist<T>::operator=( aghSlist<T> const & right )
{
    if( this != &right )
    {
        if( !( this -> isEmpty() ) )
            this -> clear();

        length = 0;

        for( int i = 0 ; i < right.size() ; i++ )
            insert( i, right.at( i ) );
    }
    return *this;
}

template <typename T> bool aghSlist<T>::insert( int index, T const& element )
{
    if( index > length || index < 0 )
        return false;

    Node * newNode = new Node( element );

    if( index == 0 )
        insertAtBeginning( newNode );
    else if( index == length )
        insertAtEnd( newNode );
    else
        insertAtMiddle( index, newNode );

    length++;
    return true;
}

template <typename T> void aghSlist<T>::insertAtBeginning( Node * newNode )
{
    newNode -> next = first;
    first = newNode;
}

template <typename T> void aghSlist<T>::insertAtEnd( Node * newNode )
{
    Node * actual = iterateToIndex( length );
    actual -> next = newNode;
}

template <typename T> void aghSlist<T>::insertAtMiddle( int index, Node * newNode )
{
    Node * actual = iterateToIndex( index );
    newNode -> next = actual -> next;
    actual -> next = newNode;
}

template <typename T> T& aghSlist<T>::at( int index ) const
{
    if( index > length || index < 0 )
        throw aghException( -1, "Index out of range!" );

    Node * actual = first;
    for( int i = 0 ; i < index ; i++ )
        actual = actual -> next;

    return actual -> value;
}

template <typename T> int aghSlist<T>::size( void ) const
{
    return length;
}

template <typename T> bool aghSlist<T>::remove( int index )
{
    if( index >= length || index < 0 )
        return false;

    Node * deleted;

    if( index == 0 )
        removeFirst( &deleted );
    else if( index == length - 1 )
        removeLast( &deleted );
    else
        removeFromMiddle( index, &deleted );


    delete deleted;
    length--;
    return true;
}

template <typename T> void aghSlist<T>::removeFirst( Node ** deleted )
{
    *deleted = first;
    first = first -> next;
}

template <typename T> void aghSlist<T>::removeLast( Node ** deleted )
{
    Node * actual = iterateToIndex( length );
    *deleted = actual -> next;
    actual -> next = NULL;
}

template <typename T> void aghSlist<T>::removeFromMiddle( int index, Node ** deleted )
{
    Node * actual = iterateToIndex( index );
    *deleted = actual -> next;
    actual -> next = ( *deleted ) -> next;
}

#endif //AGHSLIST

