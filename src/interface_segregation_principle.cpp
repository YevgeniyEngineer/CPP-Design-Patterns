
class Document;

class IPrinter
{
  public:
    virtual void print(Document &doc) = 0;
    virtual ~IPrinter() = default;
};

class IScanner
{
  public:
    virtual void scan(Document &scan) = 0;
    virtual ~IScanner() = default;
};

class IFax
{
  public:
    virtual void fax(Document &scan) = 0;
    virtual ~IFax() = default;
};

class IMachine : public IPrinter, public IScanner
{
  public:
    virtual ~IMachine() = default;
};

class Printer : public IPrinter
{
  public:
    void print(Document &doc) override
    {
        // Some logic here...
    }
};

class Scanner : public IScanner
{
  public:
    void scan(Document &doc) override
    {
        // Some logic here...
    }
};

class Fax : public IFax
{
  public:
    void fax(Document &doc) override
    {
        // Some logic here...
    }
};

class Machine : public IMachine
{
  public:
    Machine(IPrinter &printer, IScanner &scanner) : printer_{printer}, scanner_{scanner}
    {
    }

    ~Machine() = default;

    void print(Document &doc) override
    {
        printer_.print(doc);
    }

    void scan(Document &doc) override
    {
        scanner_.scan(doc);
    }

  private:
    IPrinter &printer_;
    IScanner &scanner_;
};

int main()
{
    return 0;
}