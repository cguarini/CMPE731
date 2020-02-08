// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector> 
using std::dec;
#define MASK_64 (0xFFFFFFFF)
#define MASK_65 (0x1FFFFFFFF)
#define MASK_66 (0x3FFFFFFFF)
#define MASK_33 (0x1FFFFFFFF)
#define MASK_34 (0x3FFFFFFFF)
#define MASK_32 (0xFFFFFFFF)
#define MASK_4 (0xF)

long counter = 0;
long mask1 = 0b101;
long mask2 = 0b010;
long isolationMask = 0b111;


void findValidBits(long min, long max, long busSize, int k)
{
    long input = min;
    while(input < max){
        if( (!((input % 0xFFFFFF))) && !k){
            std::cout << "Completed a sixteenth of work!" << input << "\n\r";
            std::cout << "Max: " << dec << max <<"\r\n";
        }
        for(int i = 0; i < busSize - 2; i++){
            if(((input & (isolationMask << i)) == (mask1 << i)) || ((input & (isolationMask << i)) == (mask2 << i))){
                //printf("%x\n\r", (int) input);
                counter++;
                break;
            }
        }
        input++;
    }
    std::cout << "Thread should be complete \r\n";
}

int main() 
{

    using namespace std;

    //Will hold all threads generated
    vector<thread> threads;
    //generate a thread for each core on this processor (FX-8350)
    for(int i = 0; i < 8; i++){
        threads.push_back(thread(findValidBits, i * MASK_33/8, (i+1) * MASK_33/8, 33, i));
        cout << "Creating thread: " << i << "\n";
    }

    cout << "All threads created!\n";

    //synchronize threads
    for(int i = 0; i < 8; i++){
        threads.at(i).join();
        cout << "Thread " << i << " joined!";
    }


    cout << "Threads Complete!\n";
    cout << "Count " << dec <<  counter << "\n";

    if(MASK_32 - counter > MASK_32){
        cout << "Found enough address space!\n\r";
        cout << "Counter: " << dec <<  counter << "\n\r";
        cout << "Mask: " << dec << MASK_32 << "\n\r";
    }
    else{
        cout << "Did not find enough address space!\n\r";
    }
    return 0;
}