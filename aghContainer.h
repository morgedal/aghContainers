/**
* \file aghContainer.h
* \author Maciej Rajs
* \brief Zawiera szablon klasy aghContainer
*/
#ifndef AGHCONTAINER_H
#define AGHCONTAINER_H

#include <iostream>
using namespace std;

/**
* \class aghContainer
* \author Maciej Rajs
* \brief szablon klasy kontenera do dziedziczenia dla poszczegolnych typow kontenerow
*/
template <typename T>
class aghContainer
{
  public:
    /// \brief destruktor wirtualny
    virtual ~aghContainer( void ){}

    /// \brief Dopisuje podany w argumencie element na koniec kontenera
    void append( T const & element );

    /// \brief Wstawia element podany w 2 argumencie w okreslone w pierwszym argumencie miejsce
    virtual bool insert( int index, T const & element ){}

    /// \brief Zamienia element z okreslonego w 1 arg indeksu na ten podany w 2 argumencie
    bool replace( int index, T const & replacement );

    /// \brief Zwraca element o podanym indeksie
    virtual T & at( int index ) const{}

    /// \brief Zwraca rozmiar kontenera
    virtual int size( void ) const{}

    /// \brief Usuwa element o podanym indeksie
    virtual bool remove( int index ){}

    /// \brief Usuwa wszystkie elementy
    void clear( void );

    /// \brief Sprawdza czy konrtener jest pusty i zwraca odpowiedniego boola
    bool isEmpty( void );

    /// \brief Przeszukuje kontener od podanego w 2 arg indeksie(nominalnie 0) w poszukiwaniu wzorca z 1 arg
    /// \return Jesli znajdzie zwraca indeks, jesli nie -1
    int indexOf( T const & _value, int _from = 0 ) const;

    /// \brief Przeszukuje kontener od podanego w 2 arg indeksie(nominalnie 0) w poszukiwaniu wzorca z 1 arg
    /// \return Jesli znajdzie zwraca prawde, jesli nie falsz
    bool contains( T const & _value, int _from = 0 ) const;

    /// \brief Operator przypisania
    virtual aghContainer<T> & operator=( aghContainer<T> const & right );

    /// \brief Operator porownania
    bool operator==( aghContainer<T> const & right );

    /// \brief Operator porownania zwracajacy przeciwna wartosc
    bool operator!=( aghContainer<T> const & right );

    /// \brief Dziala jak dla tablicy, zwraca element o podanym w [] indeksie
    T& operator[]( int index ) const;

    /// \brief Operator dopisujacy na koncu podanego po lewej stronie kontenera ten podany z prawej
    aghContainer<T> & operator+=( aghContainer<T> const & right );

    /// \brief Operator dopisujacy do konca kontenera element
    aghContainer<T> & operator+=( T const & element );

    /// \brief Operator dopisujacy do konca kontenera element
    aghContainer<T> & operator<<( T const & element );

    /// \brief Operator dopisujacy na koncu podanego po lewej stronie kontenera ten podany z prawej
    aghContainer<T> & operator<<( aghContainer<T> const & right );

    /// \brief Wypisuje zawartosc pojemnika na strumien
    template <typename TT> friend ostream & operator<<( ostream &, aghContainer<T> const & right );

};

template <typename T> void aghContainer<T>::append( T const & element )
{
    insert( size(), element );
}

template <typename T> bool aghContainer<T>::replace( int index, T const & replacement )
{
    if( remove( index ) && insert( index, replacement ) )
        return true;
    else
        return false;
}

template <typename T> void aghContainer<T>::clear( void )
{
    while( !isEmpty() )
        remove( size() - 1 );
}

template <typename T> bool aghContainer<T>::isEmpty( void )
{
    return size() == 0;
}

template <typename T> int aghContainer<T>::indexOf( T const& _value, int _from ) const
{
    if ( _from >= size() || _from < 0 )
        return -1;
    else
    {
        for( int i = _from ; i < size() ; i++ )
            if( at( i ) == _value )
                return i;

        return -1;
    }
}

template <typename T> bool aghContainer<T>::contains( T const& _value, int _from ) const
{
    if( indexOf( _value, _from ) == -1 )
        return false;
    else
        return true;
}

template <typename T> aghContainer<T> & aghContainer<T>::operator=( aghContainer<T> const& right )
{
    if( this != &right )
    {
        clear();
        for( int i=0 ; i < right.size() ; i++ )
            append( right.at( i ) );
    }
    return *this;
}

template <typename T> bool aghContainer<T>::operator==( aghContainer<T> const& right )
{
    if( size() != right.size() )
        return false;
    else
    {
        for( int i=0 ; i < size() ; i++ )
            if( at( i ) != right.at( i ) )
                return false;

        return true;
    }
}

template <typename T> bool aghContainer<T>::operator!=( aghContainer<T> const & right )
{
    return !( *this == right );
}

template <typename T> T & aghContainer<T>::operator[] ( int index ) const
{
    return at( index );
}

template <typename T> aghContainer<T> & aghContainer<T>::operator+=( aghContainer<T> const & right )
{
    for( int i = 0 ; i < right.size() ; i++ )
        append( right.at( i ) );

    return *this;
}

template <typename T> aghContainer<T> & aghContainer<T>::operator+=( T const& element )
{
    append( element );
    return *this;
}

template <typename T> aghContainer<T> & aghContainer<T>::operator<<( T const & element )
{
    append( element );
    return *this;
}

template <typename T> aghContainer<T> & aghContainer<T>::operator<<( aghContainer<T> const & right )
{
    for( int i = 0 ; i < right.size() ; i++ )
        append( right.at( i ) );

    return *this;
}

template<typename TT> ostream & operator<<( ostream & out, aghContainer<TT> const & right )
{
    for( int i = 0 ; i < right.size() ; i++ )
    {
        out << right.at( i );
        out << ",";
    }

    return out;
}

#endif // AGHCONTAINER_H
