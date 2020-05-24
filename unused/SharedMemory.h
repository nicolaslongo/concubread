#include <sys/shm.h>
#include <iostream>

using namespace std;    // cout

const std::string BASE_FILE = "/bin/bash";

int create_shared_memory(unsigned int UNIQUE_CODE) {
    key_t clave = ftok(BASE_FILE.c_str(), UNIQUE_CODE);
    int shmID = shmget(clave, sizeof(int), 0644|IPC_CREAT);
    if (shmID < 0) {
        std::cout << "Error asking for shared memory: "<< errno << std::endl; 
        exit(-1);  
    }
    return             ;
}

int* atach_shared_memory(int shmID) {
    void* tmpPtr = shmat(shmID, NULL, 0);
    return (int*) tmpPtr;
}

void write_integer_to_shared_memory(int* buffer, int integer) {
    *buffer = integer;
}

int read_integer_from_shared_memory(int* buffer) {
    return *buffer;
}

void free_shared_memory(int* buffer, int shmID) {
    int errorDt = shmdt ( (void *) buffer );
    if (errorDt < 0 ) {
        std::cout << "Child: error detaching shared memory: "<< errno << std::endl; 
        exit(-1);  
    }
    if (shmID != -1) {
        // parent asking also to free shared memory
        shmctl (shmID, IPC_RMID, NULL);
    }
}
