
#include "grafik.h"

#include "test.h"

class MyApp : public grafik::Application
{
public:
    MyApp()
    {

        myObj = std::unique_ptr<Test>(new Test);
        
        m_window->addListener(myObj.get());

    }

    ~MyApp()
    {

    }

private:
    std::unique_ptr<Test> myObj;
    
};

int main()
{

    MyApp myapp;


    myapp.Run();



    return 0;
}
