#ifndef LIBASTEROID_HPP
#define LIBASTEROID_HPP

#include <cstdint>

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace galaxy{
    struct asteroid {
        /**
         * this is a map indexed by strings, each representing a label.
         *
         * The labels are mapped to their *declaration points* in the
         * outputted DASM-16 code.
         */
        std::unordered_map<std::string, std::uint16_t> exported_labels;

        /**
         * this is a set of locations in DASM-16 assembly code.
         *
         * In the actual DASM-16 code, any positions where non-imported labels
         * are used will be set to the right value for that asm file
         * and will be added to this set, so they can be moved later
         */
        std::unordered_set<std::uint16_t> used_labels;

        /**
         * this is a map indexed by integers, each representing a location
         * in DASM-16 code.
         *
         * The are positions mapped to the labels *used in those positions*.
         * In the actual DASM-16 code, any positions where imported labels
         * are used will be set to their offeset and will be added to this map.
         * 
         * For example, SET PC, [foo_bar+1], where foo_bar is some imported label
         * will be changed to SET PC, [1] (with no short literal optimisation), and 
         * the linker will be responsible for adding foo_bar to that 1.
         */
        std::unordered_map<std::uint16_t, std::string> imported_labels;

        /// the machine code.
        std::vector<std::uint16_t> object_code;
    };
}

#endif /* LIBASTEROID_HPP */
