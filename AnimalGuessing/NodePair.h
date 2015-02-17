#ifndef NODEPAIR_H
#define NODEPAIR_H

template <class T>
struct Node{
    Node<T>* next;
    T item;
    Node(){next = NULL;}
    Node(const T& item){this->item = item; next = NULL;}
    Node(const T& item, Node<T>* next){this->item = item; this->next = next;}
    friend std::ostream& operator <<(std::ostream& out, const Node& N){
        out << N.item;
        return out;
    }
};

template <typename T, typename U>
struct NodePair{
    T primary;
    U secondary;

    NodePair(){}
    NodePair(const T& primary, const U& secondary){
        this->primary = primary;
        this->secondary = secondary;
    }

    friend bool equalS(const NodePair<T,U>& left, const NodePair<T,U> right){
        return left.secondary == right.secondary;
    }

    friend bool lessS(const NodePair<T,U>& left, const NodePair<T,U> right){
        return left.secondary < right.secondary;
    }

    friend bool greatS(const NodePair<T,U>& left, const NodePair<T,U> right){
        return left.secondary > right.secondary;
    }

    friend bool operator ==(const NodePair<T,U>& left, const NodePair<T,U> right){
        return left.primary == right.primary;
    }

    friend bool operator <(const NodePair<T,U>& left, const NodePair<T,U> right){
        return left.primary < right.primary;
    }

    friend bool operator >(const NodePair<T,U>& left, const NodePair<T,U> right){
        return left.primary > right.primary;
    }

    friend std::ostream& operator <<(std::ostream& out, const NodePair<T,U>& right){
        out << right.primary << " (" << right.secondary << ")";
        return out;
    }

    NodePair<T,U>& operator ++(void){
        secondary++;
        return *this;
    }
    NodePair<T,U> operator ++(int){
        NodePair<T,U> temp(this->primary,this->secondary);
        secondary++;
        return temp;
    }

};

#endif // NODEPAIR_H
