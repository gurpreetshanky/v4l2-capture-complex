#pragma once

#include <string>
#include <string_view>
#include <fstream>

class udmabuf
{
public:
    udmabuf();
    explicit udmabuf(std::string_view name);

    ~udmabuf();

    udmabuf(udmabuf&&) = default;
    udmabuf(const udmabuf&) = delete;
    udmabuf& operator=(udmabuf&&) = default;
    void operator=(const udmabuf&) = delete;

    std::ifstream get_prop(std::string_view name) const
    {
        std::string path = (m_class_path + "/").append(name);
        return std::ifstream(path);
    }

    std::ofstream set_prop(std::string_view name) const
    {
        std::string path = (m_class_path + "/").append(name);
        return std::ofstream(path);
    }

    enum dma_direction_t {
        dma_bidirectinal = 0,
        dma_to_device    = 1,
        dma_from_device  = 2
    };

    void sync_for_cpu(unsigned long offset, unsigned long length, dma_direction_t direction) const;
    void sync_for_dev(unsigned long offset, unsigned long length, dma_direction_t direction) const;

    const void *get() const;
    void* get();
    size_t size() const;

private:
    void map();

private:
    int m_fd = -1;
    std::string m_name;
    std::string m_dev_name;
    std::string m_class_path;
    size_t      m_phys_addr = 0;
    size_t      m_size = 0;
    void*       m_ptr = nullptr;
};

