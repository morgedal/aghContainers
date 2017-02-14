/**
* \file aghIterator.h
* \author Maciej Rajs
* \brief Zawiera szablon iteratora do kontenerow aghContainer
*/

#ifndef AGH_ITERATOR_H
#define AGH_ITERATOR_H

#include "aghException.h"
#include "aghVector.h"
#include "aghDoublyLinkedList.h"
#include "aghSinglyLinkedList.h"
#include "aghContainer.h"

/**
* \class aghIterator
* \author Maciej Rajs
* \brief szablon klasy iteratora do kontenerow aghContainer
*/
template<typename T> class aghIterator : public aghContainer<T>
{
  private:
    aghContainer<T> * cptr;	//wskaznik na aktualnie pokazywany kontener
    int index;				//przechowuje indeks aktualnie wskazywanego przez iterator elementu

  public:
    ///\brief Konstruktor przyjmujacy kontener ktory bedzie iterowany
    aghIterator( aghContainer<T> * container );

    ///\brief Zwraca iterator pokazujacy na zerowy element pojemnika
    aghIterator<T> first( void );

    ///\brief Zwraca iterator pokazujacy na ostatni element pojemnika
    aghIterator<T> last( void );

    ///\brief Przesuwa iterator na nastepny element pojemnika
    aghIterator<T> & next( void );

    ///\brief Przesuwa iterator na poprzedni element pojemnika
    aghIterator<T> & prev( void );

    ///\brief Zwraca element na ktory aktualnie pokazuje iterator
    T& current( void );

    ///\brief Ustawia iterator na zerowym elemencie
    aghIterator<T> & atFirst( void );

    ///\brief Ustawia iterator na ostatnim elemencie
    aghIterator<T> & atLast( void );

    ///\brief zwraca iloæ elementów od aktualnie pokazywanego do ostatniego elementu w pojemniku
    int size( void );


    ///\brief Operator przypisania kontenera do iteratora
    aghIterator<T> & operator=( aghContainer<T> * container );

    ///\brief Operator przypisania iteratora do iteratora
    aghIterator<T> & operator=( aghIterator<T> & right );

    ///\brief zwraca element znajduj¹cy siê o i pozycji dalej wzglêdem aktualnego elementu
    T& operator[]( int i );

    ///\brief zwraca iterator przesuniety o i elementów dalej
    aghIterator<T> operator+( int i );

    ///\brief zwraca iterator przesuniety o i elementów blizej
    aghIterator<T> operator-( int i );

    ///\brief przesuwa iterator o i elementów dalej
    void operator+=( int i );

    ///\brief przesuwa iterator o i elementów blizej
    void operator-=( int i );

    ///\brief zwraca iterator pokazuj¹cy na i-ty element a nastêpnie przesuwa iterator na i+1 element
    aghIterator<T> & operator++( int );

    ///\brief przesuwa iterator na i+1 element i zwraca iterator pokazuj¹cy na i+1 element
    aghIterator<T> & operator++( void );

    ///\brief zwraca iterator pokazuj¹cy na i-ty element a nastêpnie przesuwa iterator na i-1 element
    aghIterator<T> & operator--( int );

    ///\brief przesuwa iterator na i-1 element i zwraca iterator pokazuj¹cy na i-1 element
    aghIterator<T> & operator--( void );

    ///\brief operator porownania
    bool operator==( const aghIterator<T> & right );

    ///\brief operator nierownosci
    bool operator!=( const aghIterator<T> & right );

    ///\brief operator wyciagniecia tego co znajduje sie w elemencie wskazywanym przez iterator
    T& operator*( void );

    ///\brief operator rzutowania na typ int
    operator int( void );

};

template <typename T> aghIterator<T>::aghIterator( aghContainer<T> * container )
{
    cptr = container;
    atFirst();
}

template <typename T> aghIterator<T> aghIterator<T>::first( void )
{
    aghIterator<T> first_iterator( cptr );
    return first_iterator;
}

template <typename T> aghIterator<T> aghIterator<T>::last( void )
{
    aghIterator<T> last_iterator( cptr );
    last_iterator.atLast();
    return last_iterator;
}

template <typename T> aghIterator<T>& aghIterator<T>::next( void )
{
    index++;
    return *this;
}

template <typename T> aghIterator<T>& aghIterator<T>::prev( void )
{
    index--;
    return *this;
}

template <typename T> T& aghIterator<T>::current( void )
{
    if( index < 0 || index >= cptr->size() )
        throw aghException( -1, "Out of range" );
    return cptr -> at( index );
}

template <typename T> aghIterator<T> & aghIterator<T>::atFirst( void )
{
    index = 0;
    return *this;
}

template <typename T> aghIterator<T> & aghIterator<T>::atLast( void )
{
    index = cptr -> size() - 1;
    return *this;
}

template <typename T> int aghIterator<T>::size( void )
{
    return cptr -> size() - index;
}

template <typename T> aghIterator<T> & aghIterator<T>::operator=( aghContainer<T> * container )
{
    cptr = container;
    atFirst();
    return *this;
}

template <typename T> aghIterator<T> & aghIterator<T>::operator=( aghIterator<T> & right )
{
    cptr = right.cptr;
    index = right.index;
    return *this;
}

template <typename T> T& aghIterator<T>::operator[]( int i )
{
    return cptr -> at( index + i );
}

template <typename T> aghIterator<T> aghIterator<T>::operator+( int i )
{
    aghIterator tmp( this -> cptr );
    tmp.index = index;
    tmp.index += i;

    if( tmp.index >= tmp.cptr -> size() )
        throw aghException( -1, "Out of range" );

    return tmp;
}

template <typename T> aghIterator<T> aghIterator<T>::operator-( int i )
{
    aghIterator tmp( this -> cptr );
    tmp.index = index;
    tmp.index -= i;

    if( tmp.index < 0 )
        throw aghException( -1, "Out of range" );

    return tmp;
}

template <typename T> void aghIterator<T>::operator+=( int i )
{
    index += i;
}

template <typename T> void aghIterator<T>::operator-=( int i )
{
    index -= i;
}

template <typename T> aghIterator<T> & aghIterator<T>::operator++( int )
{
    aghIterator<T> tmp = *this;

    if( ++index > cptr -> size() )
        throw aghException( -1, "Out of range" );

    return tmp;
}

template <typename T> aghIterator<T> & aghIterator<T>::operator++( void )
{
    if( ++index > cptr -> size() )
        throw aghException( -1, "Out of range" );

    return *this;
}

template <typename T> aghIterator<T> & aghIterator<T>::operator--( int )
{
    aghIterator<T> tmp = *this;

    if( --index < 0 )
        throw aghException( -1, "Out of range" );

    return tmp;
}

template <typename T> aghIterator<T>& aghIterator<T>::operator--( void )
{
    if( --index < 0 )
        throw aghException( -1, "Out of range" );
    return *this;
}

template <typename T> bool aghIterator<T>::operator==( const aghIterator<T> & right )
{
    if( cptr == right.cptr && index == right.index )
        return true;
    else
        return false;
}

template <typename T> bool aghIterator<T>::operator!=( const aghIterator<T> & right )
{
    return !( *this == right );
}

template <typename T> T & aghIterator<T>::operator*( void )
{
    return cptr -> at( index );
}

template <typename T> aghIterator<T>::operator int( void )
{
    if( cptr == NULL || cptr -> size() == 0 || index < 0 || index >= cptr -> size() )
        return NULL;
    else
        return 1;
}

#endif //AGH_ITERATOR_H