
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include <iostream>
#include <memory>

#define PRINT_USE_COUNT(p) std::cout << "Use count: " << p.use_count() << std::endl;

struct Base {
    Base() {
        std::cout << "Base constructor" << std::endl;
    }
    ~Base() {
        std::cout << "Base destructor" << std::endl;
    }
    virtual int size(void) = 0;
};

struct Wi : public Base {
    int a{4};
    char b[1024];
    Wi() {
        std::cout << "Wi constructor" << std::endl;
    }
    ~Wi() {
        std::cout << "Wi destructor" << std::endl;
    }
    int size(void) {
        return sizeof(*this);
    }
    int geta(void) {
        return a;
    }
};

extern "C" void app_main(void)
{
    std::unique_ptr<Wi> w(new Wi);
    std::cout << "Size: " << w->size() << " : " << sizeof(Base) << std::endl;

    std::cout << "create a queue.." << std::endl;
    auto q = xQueueCreate(1, sizeof(Base));

    std::cout << "add object in queue.." << std::endl;
    xQueueSendToBack(q, &w, 0);

    std::cout << "get object from queue..." << std::endl;
    Base *pc;
    xQueueReceive(q, &pc, 0);

    auto *v = dynamic_cast<Wi *>(pc);

    std::cout << v->geta() << std::endl; 
}

#if 0
class testClass {
public:
    testClass() {
        std::cout << "testClass constructed" << std::endl;
    }
    ~testClass() {
        std::cout << "testClass destructed" << std::endl;
    }
};

class myContainer {
public:
    myContainer(std::shared_ptr<testClass> p) {
        _p = p;
        std::cout << "myContainer constructed" << std::endl;
    }

    ~myContainer() {
        std::cout << "myContainer destructed" << std::endl;
    }

    std::shared_ptr<testClass>& p() {
        return _p;
    }

private:
    std::shared_ptr<testClass> _p;
};

extern "C" void app_main(void) {
    std::cout << "Start of test, creating the shared_ptr..." << std::endl;
    auto p = std::make_shared<testClass>();
    PRINT_USE_COUNT(p);

    std::cout << "Creating one container..." << std::endl;
    myContainer c(p);
    PRINT_USE_COUNT(p);

    std::cout << "Creating the queue..." << std::endl;
    auto q = xQueueCreate(1, sizeof(myContainer*));

    std::cout << "Sending a dynamically created item to the queue..."
            << std::endl;
    myContainer *cp = new myContainer(p);
    xQueueSendToBack(q, &cp, 0);
    PRINT_USE_COUNT(p);

    {
        myContainer *pc;

        xQueueReceive(q, &pc, 0);
        PRINT_USE_COUNT(p);
        std::cout << "Use count of pc->p() " << pc->p().use_count()
                << std::endl;

        std::cout << "Freeing the dynamically created item..." << std::endl;
        delete pc;
        PRINT_USE_COUNT(p);
    }

    std::cout << "end of test" << std::endl;
}
#endif