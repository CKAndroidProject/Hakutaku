#ifndef PROCESS_H
#define PROCESS_H

#include <sys/uio.h>
#include <memory>

#include "proc_maps.h"
#include "proc_pagemap.h"
#include "types.h"

namespace hak {
    enum work_mode {
        ROOT,
        NON_ROOT
    };

    enum memory_mode {
        DIRECT, MEM_FILE, SYSCALL,
        PTRACE // not supported
    };

    class process: public std::enable_shared_from_this<process> {
        pid_t pid;
        memory_mode mem_mode;

        handle mem_fd;
        handle pagemap_fd;
    public:
        explicit process(pid_t pid);
        ~process();

        auto is_running() const -> bool;

        [[nodiscard]] auto get_maps(i32 range = ALL) const -> std::shared_ptr<proc_maps>;

        void read(pointer addr, void *data, size_t len);

        void write(pointer addr, void *data, size_t len);

        void set_memory_mode(memory_mode mode);

        auto get_page_entry(pointer address) -> hak::pagemap_entry;
    private:
        void init_mem_fd();
        void init_pagemaps_fd();
    };
}

#endif // PROCESS_H