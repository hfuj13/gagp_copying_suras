//---------------------------------------------------------------------------
#ifndef FrSubjectH
#define FrSubjectH

//---------------------------------------------------------------------------
class FrSubject final
{
private:
    int argN = 0;
    char **argV = nullptr;
    bool goodFlag = false;

public:
    FrSubject();
    ~FrSubject() = default;
    FrSubject(const FrSubject&) = default;
    FrSubject(FrSubject&&) = default;
    FrSubject& operator=(const FrSubject&) = default;
    FrSubject& operator=(FrSubject&&) = default;

    int getArgN(void) { return argN; }
    char **getArgV(void) { return argV; }
    void setTrueGoodFlag(void)  { goodFlag = true; }
    void setFalseGoodFlag(void) { goodFlag = false; }

    void ExecuteGa(int argc, char** argv);
    void DispState(void);
};

//---------------------------------------------------------------------------
extern FrSubject *pFrSubject;
//---------------------------------------------------------------------------
#endif
