template <typename T, typename K>
class basic_hit
{
   public:
    basic_hit() = default;
    ~basic_hit() = default;
    basic_hit(int d, float v)
    {
        det = d;
        val = v;
    };
    T getDet() const { return det; }
    K getVal() const { return val; }

    bool operator<(const basic_hit<T, K>& rhs) const
    {
        return det < rhs.getDet();
    }

   private:
    T det;
    K val;
};

template <typename T, typename K>
struct MMAPICompare {
    bool operator()(basic_hit<T, K>& lhs,
                    basic_hit<T, K>& rhs) const
    {
        return lhs.getDet() < rhs.getDet();
    }
};