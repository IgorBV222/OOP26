#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <optional>

class Logger {
public:
    //race condition
    void log(const std::string& message) {
        std::lock_guard< std::mutex> lock(_mutex); // можно передать только один
        std::scoped_lock s_lock{ _mutex, _mutex2 }; // оба заблокируются в указанном порядке
        std::cout << '[' << _counter << ']' << message << '\n';
        _counter++;
       //std::lock_guard< std::mutex> lock2(_secondMutex);
    }
    /*void successMessage() {
        std::lock_guard< std::mutex> lock(_mutex);
        std::cout << "Success Message" << '\n';
    }*/
    void someFunc() {
        //std::lock_guard< std::mutex> lock(_secondMutex); //lock(_mutex)
        std::cout << "Some text" << '\n';
        std::lock_guard< std::mutex> lock2(_mutex); //lock2(_secondMutex)
        //deadlock
    }

private:
    int _counter = 0;
    std::mutex _mutex;
    std::mutex _mutex2;
   // std::mutex _secondMutex;
};

int main()
{

   /* Logger logger;
    logger.log("Hellow");
    logger.log("Info message");


    std::thread t1 = std::thread([&logger]() {
        std::string threadName = "t1";
        for (size_t i = 0; i < 100; i++) {
            logger.log(threadName + " doing " + std::to_string(i) + " iteration of work\n");
        }
    });

    std::thread t2 = std::thread([&logger]() {
        std::string threadName = "t2";
        for (size_t i = 0; i < 100; i++) {
            logger.log(threadName + " doing " + std::to_string(i) + " iteration of work\n");
        }
    });
    t1.join();
    t2.join();*/


    std::optional <int> val = std::nullopt;
    //std::cout << val.value() << std::endl;
    val = 5;
    if (val.has_value()) {
        std::cout <<"val has value = "<< val.value()<< std::endl;
    }
    else {
        std::cout << "no" << std::endl;
    }


}
