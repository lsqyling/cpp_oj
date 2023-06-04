
template <typename T, int N = 10>
class vector
{
public:
    vector() : len_(0), elements_(new T[N]) {}
    void push_back(T const&val);
    void clear();
    ~vector() { delete[] elements_; }
private:
    T* elements_;
    int len_;

};

template<typename T, int N>
void vector<T, N>::push_back(const T &val)
{
    elements_[len_++] = val;

}

template<typename T, int N>
void vector<T, N>::clear()
{
    len_ = 0;
}


using str = vector<char>;


int main()
{
    vector<int> vi;

    vi.push_back(3);

    return 0;
}
