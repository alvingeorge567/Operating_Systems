#include <iostream>
#include <process.h>
#include <windows.h>

using namespace std;

// Thread function
unsigned int __stdcall ThreadFunc(void* arg) {
    int threadId = *(int*)arg;
    DWORD processId = GetCurrentProcessId();
    cout << "Thread " << threadId << " started in process with PID: " << processId << endl;
    Sleep(5000);
    cout << "Thread " << threadId << " finished." << endl;
    return 0;
}

int main() {
    // Create an array to store thread handles
    HANDLE threads[4];

    // Create multiple threads
    for (int i = 0; i < 4; ++i) {
        int* threadId = new int(i); // Allocate memory for thread ID
        threads[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, threadId, 0, NULL);
        if (threads[i] == NULL) {
            cerr << "Failed to create thread " << i << endl;
            delete threadId;
            return 1;
        }
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(4, threads, TRUE, INFINITE);

    // Close thread handles and free memory
    for (int i = 0; i < 4; ++i) {
        CloseHandle(threads[i]);
    }

    return 0;
}