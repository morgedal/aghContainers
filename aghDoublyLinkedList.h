/**
* \file aghDoublyLinkedList.h
* \author Maciej Rajs
* \brief Zawiera szablon klasy aghDlist - listy dwukierunkowej dziedziczacej po aghContainer
*/

#ifndef AGHDLIST_H
#define AGHDLIST_H

#include <iostream>
#include "aghContainer.h"
#include "aghException.h"

/**
* \class aghDlist
* \author Maciej Rajs
* \brief szablon klasy listy dwukierunkowej
*/

template<typename T> class aghDlist : public aghContainer<T>
{
  private:

    /// \class Node
    /// \brief Klasa pojedynczego elementu listy, uzywana jedynie przez metody aghDlist
    class Node
    {
      public:
        Node * next;
        Node * previous;
        T value;

        Node( T _value )
        {
            value = _value;
            next = NULL;
            previous = NULL;
        }
    };

    Node * first;               ///wskaznik na pierwszy element listy
    Node * last;                ///oraz na ostatni
    int length;					///przechowuje ilosc elementow w liscie

  public:
    /// \brief Konstruktor domyslny
    aghDlist() : first( NULL ), last( NULL ), length(0){}

    /// \brief Konstruktor
    aghDlist( const aghContainer<T> & container );

    /// \brief Konstruktor kopiujacy
    aghDlist( const aghDlist<T> & container );

    /// \brief Destruktor
    ~aghDlist( void );

    /// \brief Operator przypisania
    aghDlist<T>& operator=( aghDlist<T> const & right );

    /// \brief Wstawia element podany w 2 argumencie w okreslone w pierwszym argumencie miejsce
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
    void initFromContainer( aghContainer<T> const & container );
    void insertAtBeginning( Node * newNode );
    void insertAtEnd( Node * newNode );
    void insertAtMiddle( int index, Node * newNode );
    void removeLast( Node ** deleted );
    void removeFirst( Node ** deleted );
    void removeFromMiddle( int index, Node ** deleted );

    Node * iterateFromBeginning( int index )
    {
        Node * actual = first;
        for( int i = 0 ; i < index ; i++ )
            actual = actual -> next;
        return actual;
    }
    Node * iterateFromEnd( int index )
    {
        Node * actual = last;
        for( int i = length - 1 ; i > index ; i-- )
            actual = actual -> previous;
        return actual;
    }
    Node * iterateToIndex( int index )
    {
        if( index < length/2 )  //przechodzimy od tej strony listy od ktorej jest blizej
            return iterateFromBeginning(index);
        else
            return iterateFromEnd(index);
    }
};

template <typename T> aghDlist<T>::aghDlist( aghContainer<T> const & container )
{
    initFromContainer( container );
}

template <typename T> aghDlist<T>::aghDlist( const aghDlist<T> & container )
{
    initFromContainer( container );
}

template <typename T> void aghDlist<T>::initFromContainer( aghContainer<T> const & container )
{
    length = 0;
    first = NULL;
    last = NULL;
    for( int i = 0 ; i < container.size() ; i++ )
        insert( i, container.at( i ) );
}

template <typename T> aghDlist<T>::~aghDlist( void )
{
    this -> clear();
}

template <typename T> aghDlist<T> & aghDlist<T>::operator=( aghDlist<T> const & right )
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

template <typename T> bool aghDlist<T>::insert( int index , T const & element )
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

template <typename T> void aghDlist<T>::insertAtBeginning( Node * newNode )
{
    if( first == NULL )
        last = newNode;
    else
        first -> previous = newNode;

    newNode -> next = first;
    first = newNode;
}

template <typename T> void aghDlist<T>::insertAtEnd( Node * newNode )
{
    last -> next = newNode;
    newNode -> previous = last;
    last = newNode;
}

template <typename T> void aghDlist<T>::insertAtMiddle( int index, Node * newNode )
{
    Node * actual = iterateToIndex( index );
    actual = actual -> previous;

    newNode -> next = actual -> next;
    ( actual -> next ) -> previous = newNode;
    actual -> next = newNode;
    newNode -> previous = actual;
}

template <typename T> T & aghDlist<T>::at( int index ) const
{
    if( index > length || index < 0 )
        throw aghException( -1, "Index out of range!" );

    Node * actual = NULL;

    if( index < length/2 )  //przechodzimy od tej strony listy od ktorej jest blizej
    {
        actual = first;
        for( int i = 0 ; i < index ; i++ )
            actual = actual -> next;
    }
    else
    {
        actual = last;
        for( int i = length - 1 ; i > index ; i-- )
            actual = actual -> previous;
    }

    return actual -> value;
}

template <typename T> int aghDlist<T>::size() const
{
    return length;
}

template <typename T> bool aghDlist<T>::remove( int index )
{
    if( index >= length || index < 0 )
        return false;

    Node * deleted;

    if( index == length - 1 )     //usuwanie ostatniego elementu ( length-1, bo numeracja od zera )
        removeLast( &deleted );
    else if( index == 0 )
        removeFirst( &deleted );
    else
        removeFromMiddle( index , &deleted);

    delete deleted;
    length--;
    return true;
}

template <typename T> void aghDlist<T>::removeLast( Node ** deleted )
{
    *deleted = last;
    if( length > 1 )	//zabezpieczenie przed proba operacji na pustych wskaznikach w przypadku pojedynczego elementu w liscie
    {
        last = last -> previous;
        last -> next = NULL;
    }
    else	//wyczyszczenie do pustej listy
    {
        last = NULL;
        first = NULL;
    }
}

template <typename T> void aghDlist<T>::removeFirst( Node ** deleted )
{
    *deleted = first;
    first = first -> next;
    first -> previous = NULL;
}

template <typename T> void aghDlist<T>::removeFromMiddle( int index, Node ** deleted )
{
    Node * actual = iterateToIndex( index );

    *deleted = actual;
    ( ( *deleted ) -> previous ) -> next = ( *deleted ) -> next;
    ( ( *deleted ) -> next ) -> previous = ( *deleted ) -> previous;
}


#endif //AGHDLIST

