//
// Created by pavel on 11/29/22.
//

#ifndef UPDATER_VERSION_HPP
#define UPDATER_VERSION_HPP


#include <ostream>
#include <istream>
#include "networking/Connection.hpp"

class Version {
    int v1{};
    int v2{};
    int v3{};
public:
    Version();
    Version(int v1, int v2, int v3);
    bool operator<(const Version &rhs) const;
    bool operator>(const Version &rhs) const;
    bool operator<=(const Version &rhs) const;
    bool operator>=(const Version &rhs) const;
    bool operator==(const Version &rhs) const;
    [[nodiscard]] int getV1() const;
    [[nodiscard]] int getV2() const;
    [[nodiscard]] int getV3() const;
    friend Connection &operator<<(Connection &conn, const Version &version);
    friend Connection &operator>>(Connection &conn, Version &version);
    friend std::ostream &operator<<(std::ostream &os, const Version &version);
    friend std::istream &operator>>(std::istream &is, Version &version);
};


namespace std {

    template <>
    struct hash<Version>
    {
        std::size_t operator()(const Version& v) const
        {
          return 10000 * v.getV1() + 100 * v.getV2() + v.getV3();
        }
    };
}

#endif //UPDATER_VERSION_HPP
