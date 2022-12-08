//
// Created by pavel on 12/5/22.
//

#ifndef UPDATER_CHANGES_HPP
#define UPDATER_CHANGES_HPP

#include <vector>
#include "ProtocolUtil.hpp"
#include <ostream>
#include <istream>

struct Change {
    std::string filename;
    ProtocolUtil::fileUpdateAction action;
};

class Changes : public std::vector<Change>{
    friend std::ostream &operator<<(std::ostream &os, const Changes &changes);
    friend std::istream &operator>>(std::istream &is, Changes &changes);
};


#endif //UPDATER_CHANGES_HPP
