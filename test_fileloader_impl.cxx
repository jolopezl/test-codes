

enum FileLoaderType {
    FILELOADER_UNKNOWN,
    FILELOADER_FLOAT,
    FILELOADER_INTEGER,
    FILELOADER_BOOLEAN,
    FILELOADER_COMPLEX,
}

struct Loader()
{
    virtual Loader();
    virtual ~Loader();
    virtual std::vector<void> GetData();
}

template <T>
struct SpecLoader : Loader {
    SpecLoader() : Loader(){};
    ~SpecLoader(){};
    std::vector<T> GetData()
    {
       return {static_cast<T>(1)};
    }
}

struct Frame {
    Frame();
    ~Frame();
    Loader _loader;
}

int
  main()
{
    Frame f(FILELOADER_FLOAT);

    return 0;
}