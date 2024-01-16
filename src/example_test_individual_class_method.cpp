#include <iostream>
#include <string>

/// @brief Shared non-template base class with protected members
class SharedBase
{
  protected:
    /// @brief Explicit constructor of the shared base class
    explicit SharedBase(const std::string &data) : common_data_{data}
    {
    }

    /// @brief Virtual destructor of the shared base class
    virtual ~SharedBase() = default;

    /// @brief Method accessible to all derived classes operating on the members of SharedBase
    std::string commonData() const noexcept
    {
        return common_data_;
    }

  private:
    std::string common_data_;
};

/// @brief CRTP Base class with default implementation
/// @tparam Derived class inheriting from the templated base class
template <typename Derived> class Base : public SharedBase
{
  public:
    /// @brief Default constructor
    Base() : SharedBase{"Default data"}
    {
    }

    /// @brief Non-default constructor
    explicit Base(const std::string &data) : SharedBase{data}
    {
    }

    /// @brief Destructor of the base class
    virtual ~Base() = default;

    /// @brief Delegates the operation to the derived class or
    // uses default implementation provided in the base class
    std::string process()
    {
        return static_cast<Derived *>(this)->operation();
    }

    /// @brief Default implementation is stored in the base class
    std::string operation()
    {
        return "Default operation with " + commonData();
    }
};

/// @brief Derived class, providing non-default implementation to the Base class
class RealClass : public Base<RealClass>
{
  public:
    /// @brief Default constructor
    RealClass() : Base<RealClass>{"Real data"}
    {
    }

    /// @brief Destructor of the derived class
    ~RealClass() = default;

    /// @brief Implementation overriding base class's implementation
    std::string operation()
    {
        return "Real operation with " + commonData();
    }
};

/// @brief Mock class, uses default operation
class MockClass : public Base<MockClass>
{
    // No override provided, uses default operation from Base
};

int main()
{
    RealClass real_class{};
    std::cout << real_class.operation() << std::endl; // Should print "Real operation with Real Data"

    MockClass mock_class{};
    std::cout << mock_class.operation() << std::endl; // Should print "Default operation with Default data"

    return 0;
}