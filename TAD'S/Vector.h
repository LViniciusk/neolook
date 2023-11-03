/**
 * @file Vector.h
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @brief
 * @version 0.1
 * @date 02-11-2023
 *
 *
 */
#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template <typename Type>
class iteratorVector {
   private:
    Type* m_ptr;

   public:
    iteratorVector(Type* ptr) { m_ptr = ptr; }
    iteratorVector& operator++() {
        m_ptr++;
        return *this;
    }
    iteratorVector operator++(int) {
        iteratorVector temp = *this;
        m_ptr++;
        return temp;
    }
    Type& operator*() { return *m_ptr; }
    Type* operator->() { return m_ptr; }
    bool operator==(const iteratorVector& other) {
        return m_ptr == other.m_ptr;
    }
    bool operator!=(const iteratorVector& other) {
        return m_ptr != other.m_ptr;
    }
};

template <typename Type>
class Vector {
   private:
    unsigned int m_size{};      // numero de elementos atualmente na lista
    unsigned int m_capacity{};  // capacidade atual do vetor
    Type* m_vet{};              // ponteiro para o vetor

   public:
    /**
     * @brief Construtor da classe Vector
     * Complexidade: O(1)
     *
     */
    Vector() {
        m_size = 0;
        m_capacity = 1;
        m_vet = new Type[m_capacity];
    }

    Vector(unsigned int size) {
        m_size = size;
        m_capacity = size;
        m_vet = new Type[m_capacity];
    }

    Vector(unsigned int size, const Type& value) {
        m_size = size;
        m_capacity = size;
        m_vet = new Type[m_capacity];
        for (unsigned int i = 0; i < m_size; i++) {
            m_vet[i] = value;
        }
    }

    ~Vector() { delete[] m_vet; }

    /**
     * @brief Retorna o tamanho do vetor
     * Complexidade: O(1)
     *
     * @return unsigned int
     */
    unsigned int size() const { return m_size; }

    /**
     * @brief Retorna a capacidade do vetor
     * Complexidade: O(1)
     *
     * @return unsigned int
     */
    unsigned int capacity() const { return m_capacity; }

    /**
     * @brief Verifica se o vetor está vazio
     * Complexidade: O(1)
     *
     * @return true se o vetor está vazio
     * @return false caso contrário
     */
    bool empty() const { return m_size == 0; }

    /**
     * @brief Retorna uma referência para o elemento na posição index
     * Complexidade: O(1)
     *
     * @param index posição do elemento
     * @return Type&
     */
    Type& at(unsigned int index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_vet[index];
    }

    const Type& at(unsigned int index) const {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_vet[index];
    }

    /**
     * @brief Retorna uma referência para o elemento na posição index
     * Complexidade: O(1)
     *
     * @param index posição do elemento
     * @return Type&
     */
    Type& operator[](unsigned int index) { return at(index); }

    /**
     * @brief Retorna uma referência para o primeiro elemento do vetor
     * Complexidade: O(1)
     *
     * @return Type&
     */
    Type& front() { return at(0); }

    const Type& front() const { return at(0); }

    /**
     * @brief Retorna uma referência para o último elemento do vetor
     * Complexidade: O(1)
     *
     * @return Type&
     */
    Type& back() { return at(m_size - 1); }

    const Type& back() const { return at(m_size - 1); }

    void reserve(unsigned int new_capacity) {
        if (new_capacity <= m_capacity) return;
        Type* new_vet = new Type[new_capacity];
        for (unsigned int i = 0; i < m_size; i++) {
            new_vet[i] = m_vet[i];
        }
        delete[] m_vet;
        m_vet = new_vet;
        m_capacity = new_capacity;
    }

    /**
     * @brief Insere um elemento no final do vetor
     * Complexidade: O(1)
     *
     * @param value valor a ser inserido
     */
    void push_back(const Type& value) {
        if (m_size == m_capacity) {
            reserve((m_capacity * 2) + 1);
        }
        m_vet[m_size] = value;
        m_size++;
    }

    /**
     * @brief Remove o último elemento do vetor
     * Complexidade: O(1)
     *
     */
    void pop_back() {
        if (m_size == 0) throw std::runtime_error("empty vector");
        m_size--;
    }

    /**
     * @brief Insere um elemento na posição index
     * Complexidade: O(n)
     *
     * @param index posição do elemento
     * @param value valor a ser inserido
     */
    void insert(unsigned int index, const Type& value) {
        if (index > m_size) throw std::out_of_range("Index out of range");
        if (m_size == m_capacity) {
            reserve((m_capacity * 2) + 1);
        }
        for (unsigned int i = m_size; i > index; i--) {
            m_vet[i] = m_vet[i - 1];
        }
        m_vet[index] = value;
        m_size++;
    }

    /**
     * @brief Remove o elemento na posição index
     * Complexidade: O(n)
     *
     * @param index posição do elemento
     */
    void erase(unsigned int index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        for (unsigned int i = index; i < m_size - 1; i++) {
            m_vet[i] = m_vet[i + 1];
        }
        m_size--;
    }

    /**
     * @brief Remove todos os elementos do vetor
     * Complexidade: O(1)
     *
     */
    void clear() { m_size = 0; }

    /**
     * @brief Imprime o vetor
     * Complexidade: O(n)
     *
     */
    void print() {
        std::cout << "[";
        for (unsigned int i = 0; i < m_size; i++) {
            std::cout << m_vet[i];
            if (i < m_size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    /**
     * @brief Sobrecarga do operador de atribuição
     * Complexidade: O(n)
     *
     * @param other vetor a ser copiado
     * @return Vector&
     */
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_vet;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_vet = new Type[m_capacity];
            for (unsigned int i = 0; i < m_size; i++) {
                m_vet[i] = other.m_vet[i];
            }
        }
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de igualdade
     * Complexidade: O(n)
     *
     * @param other vetor a ser comparado
     * @return true se os vetores são iguais
     * @return false caso contrário
     */
    bool operator==(const Vector& other) {
        if (m_size != other.m_size) return false;
        for (unsigned int i = 0; i < m_size; i++) {
            if (m_vet[i] != other.m_vet[i]) return false;
        }
        return true;
    }

    /**
     * @brief Sobrecarga do operador de desigualdade
     * Complexidade: O(n)
     *
     * @param other vetor a ser comparado
     * @return true se os vetores são diferentes
     * @return false caso contrário
     */
    bool operator!=(const Vector& other) { return !(*this == other); }

    /**
     * @brief Sobrecarga do operador de inserção
     * Complexidade: O(n)
     *
     * @param os stream de saída
     * @param v vetor a ser impresso
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "[";
        for (unsigned int i = 0; i < v.m_size; i++) {
            os << v.m_vet[i];
            if (i < v.m_size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    using iterator = iteratorVector<Type>;

    /**
     * @brief Retorna um iterador para o primeiro elemento do vetor
     * Complexidade: O(1)
     *
     * @return iterator
     */
    iterator begin() { return iterator(m_vet); }

    /**
     * @brief Retorna um iterador para o último elemento do vetor
     * Complexidade: O(1)
     *
     * @return iterator
     */
    iterator end() { return iterator(m_vet + m_size); }
};

#endif  // VECTOR_H