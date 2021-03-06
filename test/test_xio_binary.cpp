/***************************************************************************
* Copyright (c) Johan Mabille, Sylvain Corlay and Wolf Vollprecht          *
* Copyright (c) QuantStack                                                 *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"

#include "xtensor-io/xio_binary.hpp"
#include "xtensor-io/xio_stream_wrapper.hpp"
#include "xtensor-io/xio_file_wrapper.hpp"

namespace xt
{
    TEST(xio_binary, dump_load_stream)
    {
        xtensor<double, 2> data
            {{ 1.0,  2.0,  3.0,  4.0},
             {10.0, 12.0, 15.0, 18.0}};

        const char* fname = "data_stream.bin";
        std::ofstream out_file(fname, std::ofstream::binary);
        auto o = xt::xostream_wrapper(out_file);
        dump_file(o, data, xio_binary_config());

        xarray<double> a;
        std::ifstream in_file(fname, std::ifstream::binary);
        auto i = xt::xistream_wrapper(in_file);
        load_file(i, a, xio_binary_config());
        a.reshape({2, 4});

        ASSERT_TRUE(all(equal(a, data)));
    }

    TEST(xio_binary, dump_load_file)
    {
        xtensor<double, 2> data
            {{ 1.0,  2.0,  3.0,  4.0},
             {10.0, 12.0, 15.0, 18.0}};

        const char* fname = "data_file.bin";
        FILE* out_file = fopen(fname, "wb");
        auto o = xt::xfile_wrapper(out_file);
        dump_file(o, data, xio_binary_config());

        xarray<double> a;
        FILE* in_file = fopen(fname, "rb");
        auto i = xt::xfile_wrapper(in_file);
        load_file(i, a, xio_binary_config());
        a.reshape({2, 4});

        ASSERT_TRUE(all(equal(a, data)));
    }
}
