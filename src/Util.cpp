#include "Util.hpp"

std::vector<size_t> str::retrieveRangeIndices(const boost::dynamic_bitset<> & lowbits, const boost::dynamic_bitset<> & topbits)
{

    /*
        we have the bitsets for the lower and the upper bound
        obviously the lower bound is a subset of the upper bound
        namely if we have 1 for some index in the lower bound, the we have it in the upper bound
        we have to set those bits to 0
        we just have to do an XOR
    */
    const boost::dynamic_bitset<> XOR = lowbits ^ topbits;

    /*
        we have the bits now 1 where the suffix is in the given bound
        we have to search for them.
        XOR.count() gives the count of the bits where we have 1
    */
    std::vector<size_t> positions(XOR.count());
    size_t i = XOR.find_first();
    size_t idx = 0;

    /*
        find the next bit's position and store the index
        note that if one decides to stop using the bitset and use multiple memory blocks to work with
        the best way to find the next bit set is to use the expression
        (val & -val) which is equivalen to (val & (~val + 1)) due to 2-complement of how integers are stored in memory
    */
    while (i != XOR.npos)
    {
        positions[idx++] = i;
        i = XOR.find_next(i);
    }

    /*
        explicitly move data
    */
    return std::move(positions);

}
