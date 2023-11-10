/**
 * @file Vector.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Implementação de um vetor dinâmico
 * @version 0.1
 * @date 30-10-2023
 *
 *
 */

#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

/**
 * @brief Classe que representa um iterador para o vetor
 *
 * @tparam Type
 */
template <typename Type>
class iteratorVector {
   private:
    Type* m_ptr;  // ponteiro para o elemento atual

   public:
    /**
     * @brief Construtor da classe iteratorVector.
     * Complexidade: O(1)
     *
     * @param ptr Ponteiro para o elemento atual
     */
    iteratorVector(Type* ptr) : m_ptr(ptr) {}

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Complexidade: O(1)
     *
     * @return Referência para elemento atual
     */
    iteratorVector& operator++() {
        m_ptr++;
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de pós-incremento.
     * Complexidade: O(1)
     *
     * @return Cópia do elemento antes de ser incrementado
     */
    iteratorVector operator++(int) {
        iteratorVector temp = *this;
        m_ptr++;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de indireção.
     * Complexidade: O(1)
     *
     * @return Referência para o elemento atual
     */
    Type& operator*() { return *m_ptr; }

    /**
     * @brief Sobrecarga do operador de seta.
     * Complexidade: O(1)
     *
     * @return Ponteiro para o elemento atual
     */
    Type* operator->() { return m_ptr; }

    /**
     * @brief Sobrecarga do operador de igualdade.
     * Complexidade: O(1)
     *
     * @param other iterador a ser comparado
     * @return True se os iteradores apontam para o mesmo elemento, False caso contrário.
     */
    bool operator==(const iteratorVector& other) {
        return m_ptr == other.m_ptr;
    }

    /**
     * @brief Sobrecarga do operador de desigualdade.
     * Complexidade: O(1)
     *
     * @param other iterador a ser comparado
     * @return True se os iteradores apontam para elementos diferentes, False caso contrário.
     */
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
     * @brief Construtor padrão da classe Vector.
     * Um vetor vazio de tamanho 1 é criado.
     * Complexidade: O(1)
     *
     */
    Vector() {
        m_size = 0;
        m_capacity = 1;
        m_vet = new Type[m_capacity];
    }

    /**
     * @brief Construtor parametrizado da classe Vector.
     * Um vetor vazio de tamanho size é criado.
     * Complexidade: O(1)
     *
     * @param size
     */
    Vector(unsigned int size) {
        m_size = size;
        m_capacity = size;
        m_vet = new Type[m_capacity];
    }

    /**
     * @brief Construtor parametrizado da classe Vector.
     * Um vetor de tamanho size é criado, e todos os elementos são inicializados com o valor value.
     * Complexidade: O(n)
     *
     * @param size
     * @param value
     */
    Vector(unsigned int size, const Type& value) {
        m_size = size;
        m_capacity = size;
        m_vet = new Type[m_capacity];
        for (unsigned int i = 0; i < m_size; i++) {
            m_vet[i] = value;
        }
    }

    /**
     * @brief Destrutor da classe Vector
     * Libera a memória alocada para o vetor
     * Complexidade: O(1)
     *
     */
    ~Vector() {
        if (m_vet != nullptr) {
            delete[] m_vet;
        }
    }

    /**
     * @brief Retorna o tamanho do vetor
     * Complexidade: O(1)
     *
     * @return Quantidade de elementos no vetor
     */
    unsigned int size() const { return m_size; }

    /**
     * @brief Retorna a capacidade do vetor
     * Complexidade: O(1)
     *
     * @return Capacidade do vetor
     */
    unsigned int capacity() const { return m_capacity; }

    /**
     * @brief Verifica se o vetor está vazio
     * Complexidade: O(1)
     *
     * @return True se o vetor está vazio, False caso contrário.
     */
    bool empty() const { return m_size == 0; }

    /**
     * @brief Retorna uma referência para o elemento na posição index
     * Complexidade: O(1)
     *
     * @param index posição do elemento
     * @return Referência para o elemento na posição index
     */
    Type& at(unsigned int index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_vet[index];
    }

    /**
     * @brief Função constante que retorna uma referência para o elemento na posição index
     * Complexidade: O(1)
     *
     * @param index posição do elemento
     * @return Referência constante para o elemento na posição index
     */
    const Type& at(unsigned int index) const {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_vet[index];
    }

    /**
     * @brief Sobrecarga do operador []. Retorna uma referência para o elemento na posição index.
     * Complexidade: O(1)
     *
     * @param index posição do elemento
     * @return Referência para o elemento na posição index
     */
    Type& operator[](unsigned int index) { return at(index); }

    /**
     * @brief Retorna uma referência para o primeiro elemento do vetor.
     * Complexidade: O(1)
     *
     * @return Referência para o primeiro elemento do vetor
     */
    Type& front() { return at(0); }

    /**
     * @brief Função constante que retorna uma referência para o primeiro elemento do vetor.
     * Complexidade: O(1)
     *
     * @return Referência constante para o primeiro elemento do vetor
     */
    const Type& front() const { return at(0); }

    /**
     * @brief Retorna uma referência para o último elemento do vetor.
     * Complexidade: O(1)
     *
     * @return Referência para o último elemento do vetor
     */
    Type& back() { return at(m_size - 1); }

    /**
     * @brief Função constante que retorna uma referência para o último elemento do vetor.
     * Complexidade: O(1)
     *
     * @return Referência constante para o último elemento do vetor
     */
    const Type& back() const { return at(m_size - 1); }

    /**
     * @brief Função que aumenta a capacidade do vetor para new_capacity.
     * Complexidade: O(n)
     *
     * @param new_capacity nova capacidade do vetor
     */
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
     * @brief Função que insere um elemento no final do vetor
     * Complexidade: O(1) melhor caso, O(n) pior caso.
     *
     * @param value
     */
    void push_back(const Type& value) {
        if (m_size == m_capacity) {
            reserve((m_capacity * 2) + 1);
        }
        m_vet[m_size] = value;
        m_size++;
    }

    /**
     * @brief Função que remove o último elemento do vetor.
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
     * @brief Sobrecarga do operador de atribuição
     * Complexidade: O(n)
     *
     * @param other vetor a ser copiado
     * @return referência para o vetor copiado
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
     * @return True se os vetores são iguais, False caso contrário.
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
     * @return True se os vetores são diferentes, False caso contrário.
     */
    bool operator!=(const Vector& other) { return !(*this == other); }

    /**
     * @brief Sobrecarga do operador de inserção
     * Complexidade: O(n)
     *
     * @param os stream de saída
     * @param v vetor a ser impresso
     * @return referência para a stream de saída
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
