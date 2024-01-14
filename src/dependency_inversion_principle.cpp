#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

/*
Principle overview:
    1. High level modules should not depend on low-level modules. Both should depend on abstractions.
    2. Abstractions should not depend on details. Details should depend on abstractions (interfaces or base classes).
*/

enum class Relationship
{
    PARENT,
    CHILD,
    SIBLING
};

class Person
{
  public:
    Person(const std::string &name) : name_{name}
    {
    }

    Person(std::string &&name) : name_{std::move(name)}
    {
    }

    const auto &name() const noexcept
    {
        return name_;
    }

  private:
    std::string name_;
};

class RelationshipBrowser
{
  public:
    virtual std::vector<Person> findAllChildrenOf(const std::string &name) = 0;
    virtual ~RelationshipBrowser() = default;

  private:
};

class Relationships : public RelationshipBrowser // Low level
{
  public:
    void addParentAndChild(const Person &parent, const Person &child)
    {
        relations_.push_back({parent, Relationship::PARENT, child});
        relations_.push_back({child, Relationship::CHILD, parent});
    }

    const auto &relations() const noexcept
    {
        return relations_;
    }

    std::vector<Person> findAllChildrenOf(const std::string &name) override
    {
        std::vector<Person> result;
        for (const auto &[first, rel, second] : relations_)
        {
            if ((first.name() == name) && (rel == Relationship::PARENT))
            {
                result.push_back(second);
            }
        }
        return result;
    }

  private:
    std::vector<std::tuple<Person, Relationship, Person>> relations_;
};

class Research // High level
{
  public:
    Research(RelationshipBrowser &browser)
    {
        for (const auto &child : browser.findAllChildrenOf("John"))
        {
            std::cout << "John has a child called " << child.name() << std::endl;
        }
    }

  private:
};

int main()
{
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Relationships relationships;
    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    Research research(relationships);

    return 0;
}