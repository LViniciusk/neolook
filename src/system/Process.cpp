#include "../includes/Process.h"

Process::Process(const unsigned& id,
                 const unsigned& instant,
                 const unsigned short& d_cpu,
                 const unsigned short& d_disk,
                 const unsigned short& d_network)
    : id(id), instant(instant), d_cpu(d_cpu), d_disk(d_disk), d_network(d_network) {}

Process::Process() = default;

Process::~Process() = default;