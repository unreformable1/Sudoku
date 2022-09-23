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
    const T& get(const int& row, const int& col) const;

    // Returns cell value by const reference
    const T& get(const int& index) const;

    // Returns cell value by reference
    T& get(const int& row, const int& col);

    // Returns cell value by reference
    T& get(const int& index);


    // Returns cells as 1D const array
    const T* get() const;

    // Returns cells as 1D array
    T* get();


    // Sets cell to given value
    void set(const int& row, const int& col, const T& value);

    // Sets cell to given value
    void set(const int& index, const T& value);


    // Sets cell value to default-initalized
    void remove(const int& row, const int& col);

    // Sets cell value to default-initalized
    void remove(const int& index);


    // Sets all cells value to given value
    void clear(const T& value = T{});


    // Prints board
    void print() const;


    // Returns cell value by const reference
    const T& operator()(const int& row, const int& col) const;

    // Returns cell value by const reference
    const T& operator()(const int& index) const;

    // Returns cell value by reference
    T& operator()(const int& row, const int& col);

    // Returns cell value by reference
    T& operator()(const int& index);


protected:
    T m_cells[N * M]{};
};

template <int N, int M, typename T>
const T& Board<N,M,T>::get(const int& row, const int& col) const
{
    return m_cells[N*row + col];
}

template <int N, int M, typename T>
const T& Board<N,M,T>::get(const int& index) const
{
    return m_cells[index];
}

template <int N, int M, typename T>
T& Board<N,M,T>::get(const int& row, const int& col)
{
    return m_cells[N*row + col];
}

template <int N, int M, typename T>
T& Board<N,M,T>::get(const int& index)
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
void Board<N,M,T>::set(const int& row, const int& col, const T& value)
{
    m_cells[N*row + col] = value;
}

template <int N, int M, typename T>
void Board<N,M,T>::set(const int& index, const T& value)
{
    m_cells[index] = value;
}

template <int N, int M, typename T>
void Board<N,M,T>::remove(const int& row, const int& col)
{
    m_cells[N*row + col] = T{};
}

template <int N, int M, typename T>
void Board<N,M,T>::remove(const int& index)
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

template <int N, int M, typename T>
const T& Board<N,M,T>::operator()(const int& row, const int& col) const
{
    return m_cells[N*row + col];
}

template <int N, int M, typename T>
const T& Board<N,M,T>::operator()(const int& index) const
{
    return m_cells[index];
}

template <int N, int M, typename T>
T& Board<N,M,T>::operator()(const int& row, const int& col)
{
    return m_cells[N*row + col];
}

template <int N, int M, typename T>
T& Board<N,M,T>::operator()(const int& index)
{
    return m_cells[index];
}