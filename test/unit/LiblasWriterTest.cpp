#ifdef _MSC_VER
#define BOOST_TEST_DYN_LINK
#endif

#include <boost/test/unit_test.hpp>
#include <boost/cstdint.hpp>

#include "libpc/FauxReader.hpp"
#include "libpc/src/drivers/liblas/writer.hpp"

#include "support.hpp"

using namespace libpc;

BOOST_AUTO_TEST_SUITE(LiblasWriterTest)

BOOST_AUTO_TEST_CASE(test_1)
{
    // remove file from earlier run, if needed
    Utils::deleteFile("temp.las");

    Bounds<double> bounds(1.0, 2.0, 3.0, 101.0, 102.0, 103.0);
    FauxReader reader(bounds, 1000, FauxReader::Constant);

    std::ostream* ofs = Utils::createFile("temp.las");

    {
        // need to scope the writer, so that's it dtor can use the stream
        LiblasWriter writer(reader, *ofs);
        writer.write(10);
    }

    Utils::closeFile(ofs);

    BOOST_CHECK(compare_files("temp.las", "../../test/data/simple.las"));

    Utils::deleteFile("temp.las");

    return;
}

BOOST_AUTO_TEST_SUITE_END()
