#ifndef NODEPAIR_H
#define NODEPAIR_H
template <typename T, typename U>
struct NodePair{
    T primary;
    U secondary;

    NodePair(){}
    NodePair(const T& primary, const U& secondary){
        this->primary = primary;
        this->secondary = secondary;
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
        out << right.primary << "(" << right.secondary << ")";
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
