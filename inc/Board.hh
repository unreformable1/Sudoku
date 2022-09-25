#pragma once

#include <iomanip>
#include <iostream>


/**
 * @brief Board class definition
 * 
 * @tparam N number of rows
 * @tparam M number of columns
 * @tparam T data stored in each cell
 */
template <int N, int M, typename T>
class Board
{
public:
    /**
     * @brief Returns the number of rows of the board
     * 
     * @return constexpr int number of rows
     */
    constexpr int rows() const { return N; }

    
    /**
     * @brief Returns the number of columns of the board
     * 
     * @return constexpr int number of columns
     */
    constexpr int cols() const { return M; }

    /**
     * @brief Returns the number of cells of the board
     * 
     * @return constexpr int number of cells
     */
    constexpr int size() const { return N*M; }


    /**
     * @brief Returns the data of the specified cell
     * 
     * @param row row number
     * @param col column number
     * @return const T& constant reference to data
     */
    const T& get(const int& row, const int& col) const;

    /**
     * @brief Returns the data of the specified cell
     * 
     * @param index index number
     * @return const T& constant reference to data
     */
    const T& get(const int& index) const;

    /**
     * @brief Returns the data of the specified cell
     * 
     * @param row row number
     * @param col column number
     * @return T& reference to data
     */
    T& get(const int& row, const int& col);

    /**
     * @brief Returns the data of the specified cell
     * 
     * @param index index number
     * @return T& reference to data
     */
    T& get(const int& index);


    /**
     * @brief Returns the board data as a 1D array
     * 
     * @return const T* constant pointer to data
     */
    const T* get() const;

    /**
     * @brief Returns the board data as a 1D array
     * 
     * @return T* pointer to data
     */
    T* get();


    /**
     * @brief Sets the value of a board cell to the specified value
     * 
     * @param row row number
     * @param col column number
     * @param value specified value
     */
    void set(const int& row, const int& col, const T& value);

    /**
     * @brief Sets the value of a board cell to the specified value
     * 
     * @param index index number
     * @param value specified value
     */
    void set(const int& index, const T& value);


    /**
     * @brief Sets the cell's value to the default value
     * 
     * @param row row number
     * @param col column number
     */
    void remove(const int& row, const int& col);

    /**
     * @brief Sets the cell's value to the default value
     * 
     * @param index index number
     */
    void remove(const int& index);


    /**
     * @brief Sets the value of all cells to the specified value or, if no value
     * is specified, to the default value
     * 
     * @param value specified value
     */
    void clear(const T& value = T{});


    /**
     * @brief Overloading the operator () to return a value under a specified cell
     * 
     * @param row row number
     * @param col column number
     * @return const T& constant reference to data
     */
    const T& operator()(const int& row, const int& col) const;

    /**
     * @brief Overloading the operator () to return a value under a specified cell
     * 
     * @param index index number
     * @return const T& constant reference to data
     */
    const T& operator()(const int& index) const;

    /**
     * @brief Overloading the operator () to return a value under a specified cell
     * 
     * @param row row number
     * @param col column number
     * @return T& reference to data
     */
    T& operator()(const int& row, const int& col);

    /**
     * @brief Overloading the operator () to return a value under a specified cell
     * 
     * @param index index number
     * @return T& reference to data
     */
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