#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

/**
 * @brief Struct que implementa um nó da fila de prioridade.
 * A prioridade é dada pelo valor do dado armazenado no nó.
 * Nesta implementação, quanto menor o valor do dado, maior a prioridade.
 *
 */
template <typename Type>
struct NodePQ {
    Type data;
    NodePQ* next;

    /**
     * @brief Construtor da classe NodePQ.
     *
     * @param data Valor a ser armazenado no nó
     * @param next Ponteiro para o próximo nó
     */
    NodePQ(Type data, NodePQ* next) {
        this->data = data;
        this->next = next;
    }

    /**
     * @brief Destrutor da classe NodePQ.
     *
     */
    ~NodePQ() { delete next; }
};

/**
 * @brief Class que implementa a lógica de uma fila de prioridade.
 * A prioridade é dada pelo valor do dado armazenado no nó.
 * Nesta implementação, quanto menor o valor do dado, maior a prioridade.
 *
 * @tparam Type
 */
template <typename Type>
class iterator_priorityQueue {
   private:
    NodePQ<Type>* m_ptr;  // ponteiro para o nó atual

   public:
    /**
     * @brief Construtor da classe iterator_priorityQueue
     *
     * @param ptr Ponteiro para o nó atual
     */
    iterator_priorityQueue(NodePQ<Type>* ptr) { m_ptr = ptr; }

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Faz o iterador apontar para o proximo elemento da fila.
     *
     * @return iterator_priorityQueue& retorna uma referencia para o iterador
     */
    iterator_priorityQueue& operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de pós-incremento.
     * Faz o iterador apontar para o proximo elemento da fila.
     *
     * @return iterator_priorityQueue retorna o iterador antes de ser
     * incrementado
     */
    iterator_priorityQueue operator++(int) {
        iterator_priorityQueue temp = *this;
        m_ptr = m_ptr->next;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de indireção.
     * Retorna o valor armazenado no NodePQ apontado pelo iterador.
     *
     * @return Type& retorna uma referencia para o dado armazenado no NodePQ
     */
    Type& operator*() { return m_ptr->data; }

    /**
     * @brief Sobrecarga do operador de igualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para o mesmo nó
     * @return false caso contrário
     */
    bool operator==(const iterator_priorityQueue& other) {
        return m_ptr == other.m_ptr;
    }

    /**
     * @brief Sobrecarga do operador de desigualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para nós diferentes
     * @return false caso contrário
     */
    bool operator!=(const iterator_priorityQueue& other) {
        return m_ptr != other.m_ptr;
    }
};

template <typename Type>
class PriorityQueue {
   private:
    NodePQ<Type>* m_head{};  // ponteiro para o primeiro nó da fila
    NodePQ<Type>* m_tail{};  // ponteiro para o último nó da fila
    int m_size{};            // tamanho da fila

   public:
    /**
     * @brief Construtor default da classe PriorityQueue.
     *
     */
    PriorityQueue() = default;

    /**
     * @brief Função que verifica se a fila está vazia.
     *
     * @return true se a fila está vazia,
     * @return false caso contrário.
     */
    bool empty() { return m_size == 0; }

    /**
     * @brief Função que retorna a quantidade de elementos na fila.
     *
     * @return unsigned
     */
    unsigned size() { return m_size; }

    /**
     * @brief Retorna uma referência const do elemento de maior prioridade na
     * fila.
     *
     */
    const Type& top() { return m_head->data; }

    /**
     * @brief Função que insere um elemento na fila.
     * O elemento é inserido de forma ordenada, de acordo com a
     * prioridade/valor.
     *
     * @param data
     */
    void push(const Type& data) {
        if (m_size == 0) {
            // Se não possuir elementos, insere no início
            m_head = new NodePQ<Type>(data, nullptr);
            m_tail = m_head;
        } else {
            // Se possuir elementos, insere ordenado
            NodePQ<Type>* aux = m_head;
            NodePQ<Type>* prev = nullptr;
            // percorre a fila até encontrar um elemento de menor prioridade
            while (aux != nullptr && aux->data < data) {
                prev = aux;
                aux = aux->next;
            }
            if (prev == nullptr) {
                // insere no início
                m_head = new NodePQ<Type>(data, m_head);
            } else {
                // o anterior aponta para o novo nó, que aponta para o próximo
                prev->next = new NodePQ<Type>(data, aux);
            }
        }
        m_size++;
    }

    /**
     * @brief Função que remove o elemento de maior prioridade da fila.
     *
     */
    void pop() {
        if (m_size == 0) {
            // Se não possuir elementos, não faz nada
            return;
        } else if (m_size == 1) {
            // Se possuir apenas um elemento, remove o primeiro
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        } else {
            // Se possuir mais de um elemento, remove o primeiro
            NodePQ<Type>* aux = m_head;
            m_head = m_head->next;
            aux->next = nullptr;
            delete aux;
        }
        m_size--;
    }

    /**
     * @brief Função que retorna um iterador para o primeiro elemento da fila, o
     * elemento de maior prioridade.
     *
     * @return iterator_priorityQueue<Type>
     */
    iterator_priorityQueue<Type> begin() {
        return iterator_priorityQueue<Type>(m_head);
    }

    /**
     * @brief Função que retorna um iterador para o primeiro bit após o último
     * elemento da fila.
     *
     * @return iterator_priorityQueue<Type>
     */
    iterator_priorityQueue<Type> end() {
        return iterator_priorityQueue<Type>(m_tail->next);
    }
};

#endif  // PRIORITYQUEUE_H
