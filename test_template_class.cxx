#include <iostream>

template<typename T = int>
class Image {
    public:
        Image()=default;
        Image(T);
        ~Image()=default;
        T getImage();
        void print();
    private:
        T value;
};

template<typename T>
Image<T>::Image(T input) : value(input) {
}

template<typename T>
T Image<T>::getImage() {
    return this->value;
}

template<typename T>
void Image<T>::print() {
    std::cout << "Image value = " << this->value << std::endl;
}

void func(Image<> &image) {
    image.print();
}

int main(int argc, char** argv) {
    Image i(argv[0]);
    i.print();
    auto v = i.getImage();
    std::cout << "Image value = " << v << std::endl;
    func(i);
    return 0;
}
