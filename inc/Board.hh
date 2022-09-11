#pragma once

#include <iomanip>
#include <iostream>


/**
 * @brief Board class definition
 * 
 * @tparam N number of rows
 * @tparam M number of columns
 * @tparam T data stored inside each board's cell
 */
template <int N, int M, typename T>
class Board
{
public:
    // Returns number of rows
    constexpr int rows() const { return N; }

    // Return number of columns
    constexpr int cols() const { return M; }

    // Returns number of cells
    constexpr int size() const { return N*M; }


    // Returns cell value by const reference
    const T& get(int row, int col) const;

    // Returns cell value by const reference
    const T& get(int index) const;

    // Returns cell value by reference
    T& get(int row, int col);

    // Returns cell value by reference
    T& get(int index);


    // Returns cells as 1D const array
    const T* get() const;

    // Returns cells as 1D array
    T* get();


    // Sets cell to given value
    void set(int row, int col, int value);

    // Sets cell to given value
    void set(int index, int value);


    // Sets cell value to default-initalized
    void remove(int row, int col);

    // Sets cell value to default-initalized
    void remove(int index);


    // Sets all cells value to given value
    void clear(const T& value = T{});


    // Prints board
    void print() const;


protected:
    T m_cells[N * M]{};
};

template <int N, int M, typename T>
const T& Board<N,M,T>::get(int row, int col) const
{
    return m_cells[N*row + col];
}

template <int N, int M, typename T>
const T& Board<N,M,T>::get(int index) const
{
    return m_cells[index];
}

template <int N, int M, typename T>
T& Board<N,M,T>::get(int row, int col)
{
    return m_cells[N*row + col];
}

template <int N, int M, typename T>
T& Board<N,M,T>::get(int index)
{
    return m_cells[index];
}

template <int N, int M, typename T>
const T* Board<N,M,T>::get() const
{
    return m_cells;
}

template <int N, int M, typename T>
T* Board<N,M,T>::get()
{
    return m_cells;
}

template <int N, int M, typename T>
void Board<N,M,T>::set(int row, int col, int value)
{
    m_cells[N*row + col] = value;
}

template <int N, int M, typename T>
void Board<N,M,T>::set(int index, int value)
{
    m_cells[index] = value;
}

template <int N, int M, typename T>
void Board<N,M,T>::remove(int row, int col)
{
    m_cells[N*row + col] = T{};
}

template <int N, int M, typename T>
void Board<N,M,T>::remove(int index)
{
    m_cells[index] = T{};
}

template <int N, int M, typename T>
void Board<N,M,T>::clear(const T& value)
{
    for(int row = 0; row < N; ++row)
    {
        for(int col = 0; col < M; ++col)
        {
            m_cells[N*row + col] = value;
        }
    }
}

template <int N, int M, typename T>
void Board<N,M,T>::print() const
{
    for(int row = 0; row < N; ++row)
    {
        for(int col = 0; col < M; ++col)
        {
            std::cout << std::setw(2) << m_cells[N*row + col];
        }
        std::cout << std::endl;
    }
}