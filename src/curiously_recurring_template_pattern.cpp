#include <iostream>

template <typename Derived, typename T> class Numeric
{
  public:
    Derived &operator+=(const Derived &other)
    {
        Derived &self = static_cast<Derived &>(*this);
        self.value_ += other.value_;
        return self;
    }

    Derived &operator-=(const Derived &other)
    {
        Derived &self = static_cast<Derived &>(*this);
        self.value_ -= other.value_;
        return self;
    }

    void print() const
    {
        std::cout << static_cast<const Derived &>(*this).value_ << std::endl;
    }

  protected:
    Numeric() : value_{0}
    {
    }

    Numeric(T value) : value_{value}
    {
    }

    virtual ~Numeric() = default;

  private:
    T value_;
};

class Integer final : public Numeric<Integer, int>
{
  public:
    Integer() : Numeric()
    {
    }

    Integer(int value) : Numeric(value)
    {
    }
};

class Float final : public Numeric<Float, float>
{
  public:
    Float() : Numeric()
    {
    }

    Float(float value) : Numeric(value)
    {
    }
};

int main()
{
    Integer number1(3.14);
    Integer number2(1.5);

    number1 += number2;
    number1.print();

    Float number3(3.14);
    Float number4(1.5);

    number3 -= number4;
    number3.print();

    return 0;
}