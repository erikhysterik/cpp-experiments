#include <iostream>
#include <deque>
#include <functional>
using namespace std;

//// inspired by js frameworks //////

// an attempt to get around the issues with std::async/future as noted here:
// http://w...content-available-to-author-only...s.com/parallel/improving-futures-and-callbacks-in-c-to/240004255
// http://stackoverflow.com/questions/26372904/what-limitation-of-stdasync-is-stroustrup-referring-to
// http://b...content-available-to-author-only...i.com/2011/10/10/async-tasks-in-c11-not-quite-there-yet/

class A{
	public:
	A() : c(0)
	{}
	
	void doThings(){
    	// chaining!!! 
    	makeAsyncCall().then(
    		[this](bool result)
    		{std::cout << "result: " << result << " lambda1" << std::endl; 
    		 if (result){
    			makeAsyncCall()/*.then([this](bool result){std::cout << "result: " << result << " lambda2" << std::endl; finish();})*/;
    		 }
    		 else
    		 {
    		 	finish();
    		 }
    		}
    		).then([this](bool result){std::cout << "result: " << result << " lambda2" << std::endl; finish();});
    	// using either syntax form of the second .then ends up having the same execution order......
    	// try uncommenting each one individually and see
    }
	
	bool asyncResult(bool b){
    	if (fstore.size()){
    		fstore[0](b);
    		fstore.pop_front();
    		return true;
    	}
    	return false;
    }
	
	private:
	
	A& then(std::function<void(bool)> f)
    {
    	std::cout << "storing function callback" << std::endl;
    	fstore.push_back(f);
    	return *this;
    }
    
    A& makeAsyncCall(){
    	std::cout << "async call: " << c++ << std::endl;
    	return *this;
    }
    
    void finish(){
    	std::cout << "i'm done" << std::endl;
    }
    
    int c;
    // if you needed some sort of actual correlation for the callback to execute instead
	// of just fifo, you could either not make .then return A& meaning you'd only have a makeAsyncCall().then(...)
	// type syntax available, or devise some map scheme where the function callback is created and pushed onto the map 
	// and the makeAsyncCall that uses that id somehow knows what its callback is supposed to be and gets the id from the
	// callback map. a little weird but possible i suppose.
    std::deque<std::function<void(bool)>> fstore;
};



int main() {
	A a;
	
	a.doThings();
	
	// pretend this is where the async result thread comes in
	// with the response....
	while(a.asyncResult(true));
	//a.asyncResult(true);
	//a.asyncResult(false);
	
	return 0;
}
