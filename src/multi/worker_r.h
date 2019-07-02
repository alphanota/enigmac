//
// Created by angel on 7/1/19.
//

#ifndef ENIGMAC_WORKER_R_H
#define ENIGMAC_WORKER_R_H


#include "worker.h"
#include <iterator>

namespace worker_r_ns {
    std::vector<worker> gen_worker(int num_threads);
}
#endif //ENIGMAC_WORKER_R_H
