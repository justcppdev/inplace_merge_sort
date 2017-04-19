#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>

template <typename Iterator>
void merge_using_swap( Iterator first_begin, Iterator first_end, Iterator second_begin, Iterator second_end, Iterator output )
{
    auto first_iterator = first_begin;
    auto second_iterator = second_begin;

    while( first_iterator != first_end && second_iterator != second_end ) {
        if( *first_iterator < *second_iterator ) {
            std::swap( *first_iterator++, *output++ );
        }
        else {
            std::swap( *second_iterator++, *output++ );
        }
    }

    while( first_iterator != first_end ) {
        std::swap( *first_iterator++, *output++ );
    }

    while( second_iterator != second_end ) {
        std::swap( *second_iterator++, *output++ );
    }
}

template <typename Iterator>
void merge_sort_using_swap( Iterator begin, Iterator end, Iterator output )
{
    auto distance = std::distance(begin, end);

    merge_using_swap( begin, begin + distance / 2, begin + distance / 2, end, output );
}

template <typename Iterator>
void inplace_merge_sort( Iterator begin, Iterator end )
{
    auto distance = std::distance( begin, end );

    auto first_begin = begin;
    auto first_end = begin + distance / 2;

    auto second_begin = begin + distance / 2;
    auto second_end = end;

    merge_sort_using_swap( first_begin, first_end, second_begin );

    while( ( distance = std::distance( first_begin, first_end ) ) > 1 ) {
        auto third_begin = first_begin;
        auto third_end = first_begin + distance / 2;

        auto fourth_begin = first_begin + distance / 2;
        auto fourth_end = first_end;

        merge_sort_using_swap( fourth_begin, fourth_end, third_begin );
        merge_using_swap( third_begin, third_end, second_begin, second_end, fourth_begin );

        first_end = third_end;
        second_begin = fourth_begin;
    }

    for( auto first_iterator = first_begin, second_iterator = second_begin; second_iterator != second_end && *second_iterator < *first_iterator; ++first_iterator, ++second_iterator ) {
        std::swap( *first_iterator, *second_iterator );
    }
}

int main() {

    ssize_t numbers[]{ 3, 4, 5, 6, 7, 8, 1, 2 };

    inplace_merge_sort( std::begin( numbers ), std::end( numbers ) );

    std::copy( std::begin( numbers ), std::end( numbers ), std::ostream_iterator<ssize_t>{ std::cout, " " } );

    return 0;
}