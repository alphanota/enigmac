//
// Created by angel on 7/1/19.
//

#ifndef ENIGMAC_MULTI_H
#define ENIGMAC_MULTI_H

# include <boost/thread.hpp>
# include <limits>
# include <cmath>
# include <cassert>
#include "../enigma.h"
#include "../Sinkov.h"
#include "../ResultContainer.h"
#include "../SettingsIterator.h"
#include "worker.h"
#include "../utils.h"

# define NUMBER_THREADS 8

namespace multi { // Begin empty namespace
    class worker_t
    {
    private:
        std::vector<Result> mContainer;
        std::vector<std::string> mSettings;
        std::string text;
    public:
        void setup(std::vector<std::string> s, std::string t) {
            mSettings = s;
            text = t;
        }

        // Beginning of Example A.1.1.1c of OpenMP 2.5 standard document
        void decode(std::vector<std::string> settings,std::vector<Result>& results, std::string text) {
            Enigma machine;
            Sinkov sinkov;


            for(std::string setting : settings) {
                machine.setSettings(setting);
                std::string message = machine.encode(text);
                double score = sinkov.score(message);
                results.push_back((Result(setting,score,0)));

            }

            cout << "settingsThread: " << settings.size() << endl;
            cout << "fin: " << mContainer.size() << endl;

        }


        std::vector<Result> getContainer(){
            return mContainer;
        }

        void operator()()
        {     decode(mSettings, mContainer, text); }
    };
}

std::vector<Result> a11c(std::string text)
{

    // number of threads
    int number_threads = NUMBER_THREADS;

    // set of workers
    multi::worker_t worker[NUMBER_THREADS];
    // threads for each worker
    boost::thread* bthread[NUMBER_THREADS];

    int n_total = 336;

    // Break the work up into sub work for each thread
    size_t  n     = n_total / number_threads;

    ResultContainer container(100000);
    SettingsIterator settingsIterator;


    worker[0].setup(settingsIterator.next(0,n), text);
    for(int j = 1; j < number_threads; j++)
    {
        worker[j].setup(settingsIterator.next(j*n, (j+1)*n), text);
        // create this thread
        bthread[j] = new boost::thread(boost::ref(worker[j]));
        cout << "launched worker # " << j << endl;
    }

    worker[0]();

    // wait for other threads to finish
    for(int j = 1; j < number_threads; j++) {
        bthread[j]->join();
        delete bthread[j];
    }

    cout << "DONE: " << endl;

    for(int j = 0; j < number_threads; j++)
    {
        std::vector<Result> rc = worker[j].getContainer();
        container.insertAll(rc);
    }

    return to_vector(container);
}

std::vector<Result> checkFromPreviousResult(string text, std::vector<Result> results, std::vector<worker> (*gen_workers)(int)) {

    Sinkov sinkov;
    // number of threads
    int number_threads = NUMBER_THREADS;

    // set of workers
    std::vector<worker> workers = gen_workers(NUMBER_THREADS);
    // threads for each worker
    boost::thread* bthread[NUMBER_THREADS];

    int n_total = results.size();

    // Break the work up into sub work for each thread
    size_t  n     = n_total / number_threads;


    std::vector<Result>::iterator cur = results.begin();
    std::vector<Result>::iterator end = results.end();




    workers[0].setup( cur, cur+n,text, sinkov);
    cur = cur+n;
    for(int j = 1; j < number_threads; j++)

    {

        workers[j].setup(cur, cur+n, text, sinkov);


        // create this thread
        bthread[j] = new boost::thread(boost::ref(workers[j]));

        cout << "launched worker # " << j << endl;

        cur += n;
    }

    workers[0]();

    // wait for other threads to finish
    for(int j = 1; j < number_threads; j++) {
        bthread[j]->join();
        delete bthread[j];
    }

    cout << "DONE: " << endl;

    ResultContainer container(1000);
    for(int j = 0; j < number_threads; j++)
    {
        std::vector<Result> rc = workers[j].getContainer();
        container.insertAll(rc);
    }

    return to_vector(container);

}

#endif //ENIGMAC_MULTI_H
