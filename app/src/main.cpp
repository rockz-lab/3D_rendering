
#include "grafik.h"

#include "test.h"

class MyApp : public grafik::Application
{
public:
    MyApp()
    {
        // create a test object
        myObj = std::unique_ptr<testPoint>(new testPoint);

        myObj->addVisual(std::string(PROJECT_SOURCE) + "/resources/meshes/Statue.obj");

        m_window->addListener(myObj.get());

        // create a collsion tester
        Bounds bounds = { -300, 300, -200, 200 };
        tester = std::unique_ptr<testBounds>(new testBounds(bounds));
        tester->addCollider(myObj.get());
        tester->addListener(myObj.get());
    }

    void Run()
    {
        while (m_runApp)
        {
            tester->checkColls();
            Update();
        }
    }

    ~MyApp()
    {

    }

private:
    std::unique_ptr<testPoint> myObj;
    
    std::unique_ptr<testBounds> tester;
};

int main()
{

    MyApp myapp;


    myapp.Run();



    return 0;
}
