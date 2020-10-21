#ifndef XTENSOR_IO_DISK_HANDLER_HPP
#define XTENSOR_IO_DISK_HANDLER_HPP

#include <xtensor/xarray.hpp>
#include <xtensor/xexpression.hpp>

namespace xt
{
    template <class C>
    class xio_disk_handler
    {
    public:

        template <class E>
        void write(const xexpression<E>& expression, const std::string& path) const;

        template <class ET>
        void read(ET& array, const std::string& path) const;

        void configure_format(const C& format_config);

    private:

        C m_format_config;
    };

    template <class C>
    template <class E>
    inline void xio_disk_handler<C>::write(const xexpression<E>& expression, const std::string& path) const
    {
        std::ofstream out_file(path, std::ofstream::binary);
        if (out_file.is_open())
        {
            dump_file(out_file, expression, m_format_config);
        }
        else
        {
            XTENSOR_THROW(std::runtime_error, "write: failed to open file " + path);
        }
    }

    template <class C>
    template <class ET>
    inline void xio_disk_handler<C>::read(ET& array, const std::string& path) const
    {
        std::ifstream in_file(path, std::ifstream::binary);
        if (in_file.is_open())
        {
            load_file<ET>(in_file, array, m_format_config);
        }
        else
        {
            XTENSOR_THROW(std::runtime_error, "read: failed to open file " + path);
        }
    }

    template <class C>
    inline void xio_disk_handler<C>::configure_format(const C& format_config)
    {
        m_format_config = format_config;
    }


}

#endif
