/**
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 6. 1
  *
  */

#include "LinkedBinaryTree.h"
#include "SearchTree.h"
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <iostream>

using namespace std;

int main()
{
    typedef Entry<int, float> EntryType;

    LinkedBinaryTree<EntryType> t;

    std::cout << "Size : " << t.size() << std::endl;

    t.addRoot();

    std::cout << "Size : " << t.size() << std::endl;


    //
    //
    //
    SearchTree<EntryType> st;

    std::cout << "Size : " << st.size() << std::endl;
    st.insert(1, 2.5);
    st.insert(3, 4.5);
    st.insert(7, 5.5);
    st.insert(2, 1.5);
    st.insert(3, 8.5);
    std::cout << "Size : " << st.size() << std::endl;

    for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
    {
        std::cout << (*it).key() << " , " << (*it).value() << std::endl;
    }

    st.erase(3);
    std::cout << "Size : " << st.size() << std::endl;
    for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
    {
        std::cout << (*it).key() << " , " << (*it).value() << std::endl;
    }

    std::cout << "------------" << std::endl;

    //
    //
    //
    AVLTree<EntryType> avl;

    // random test
//    int nElem = 100;
    int nElem = 1000;
//    int nElem = 10000;
//    int nElem = 100000;
//    int nElem = 1000000;
//    int nElem = 10000000;

    int *key = new int[nElem*2];
    float *val = new float[nElem*2];

    std::srand(std::time(0)); // use current time as seed for random generator


    // initialize
    for(int i=0; i<nElem*2; i++)
    {
        key[i] = std::rand();
        val[i] = (float) std::rand()/RAND_MAX * 20000;
    }


    //
    // Insert test
    //
    clock_t tm;
    tm = clock();
    for(int i=0; i<nElem*2; i++)
    {
        avl.insert(key[i], val[i]);
    }
    tm = clock() - tm;
    printf ("AVL Tree: It took me %f seconds for Insertion only.\n",((float)tm)/(float)CLOCKS_PER_SEC);


    tm = clock();
    for(int i=0; i<nElem*2; i++)
    {
        st.insert(key[i], val[i]);
    }
    tm = clock() - tm;
    printf ("Search Tree: It took me %f seconds for Insertion only.\n",((float)tm)/(float)CLOCKS_PER_SEC);


    //
    // Find test
    //
    tm = clock();
    for(int i=nElem; i<nElem*2; i++)
    {
        avl.find(key[i]);
    }
    tm = clock() - tm;
    printf ("AVL Tree: It took me %f seconds for Find only.\n",((float)tm)/(float)CLOCKS_PER_SEC);

    tm = clock();
    for(int i=nElem; i<nElem*2; i++)
    {
        st.find(key[i]);
    }
    tm = clock() - tm;
    printf ("Search Tree: It took me %f seconds for Find only.\n",((float)tm)/(float)CLOCKS_PER_SEC);


    //
    // AVL tree Erase and Find test
    //

    tm = clock();
    for(int i=nElem; i<nElem*2; i++)
    {
        int r = std::rand() % 10;
        if (r > 0)
        {
            avl.erase(key[i]);
        } else
        {
            avl.find(key[i]);
        }
    }
    tm = clock() - tm;
    printf ("AVL Tree: It took me %f seconds for Erase and Find.\n",((float)tm)/(float)CLOCKS_PER_SEC);


    tm = clock();
    for(int i=nElem; i<nElem*2; i++)
    {
        int r = std::rand() % 10;
        if (r > 0)
        {
            st.erase(key[i]);
        } else
        {
            st.find(key[i]);
        }
    }
    tm = clock() - tm;
    printf ("Search Tree: It took me %f seconds for Erase and Find.\n",((float)tm)/(float)CLOCKS_PER_SEC);


    return 0;
}
