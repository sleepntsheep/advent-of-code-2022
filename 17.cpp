#include <cstdint>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <cassert>

const std::vector<uint8_t> rocks[] = {
    {0b11110},
    {0b01000, 0b11100, 0b01000},
    {0b11100, 0b00100, 0b00100},
    {0b10000, 0b10000, 0b10000, 0b10000},
    {0b11000, 0b11000},
};

class NotTetris {
    public:
        NotTetris(std::string j): jet(j) { }
        ~NotTetris() { }

        void round() {
            std::vector<uint8_t> rock = rocks[rock_i++ % 5];
            int ry = v.size() + 3;
            while (1) {
                rock = push(rock, ry);
                if (fall(rock, ry)) {
                    ry--;
                } else {
                    rest(rock, ry);
                    break;
                }
            }
        }

        uint64_t get_height() {
            return v.size();
        }

        void print() {
            for (int i = v.size() - 1; i >= 0; i--) {
                for (int j = 6; j >= 0; j--) {
                    std::cout << (v[i] & (1 << j) ? '#' : '.');
                }
                std::cout << std::endl;
            }
        }

        bool collide(const std::vector<uint8_t> &rocks, int height) {
            if (height >= v.size())
                return false;
            for (int i = 0; i < rocks.size(); i++) {
                while (height + i >= v.size())
                    return false;
                if (rocks[i] & v[height + i])
                    return true;
            }
            return false;
        }

        bool fall(const std::vector<uint8_t> &rocks, int height) {
            if (height == 0 || collide(rocks, height - 1))
                return false;
            return true;
        }

        void rest(const std::vector<uint8_t> &rocks, int height) {
            for (int i = 0; i < rocks.size(); i++) {
                if (height + i >= v.size()) {
                    v.push_back(rocks[i]);
                } else {
                    v[height + i] |= rocks[i];
                }
            }
        }

        std::vector<uint8_t> push(const std::vector<uint8_t> &rocks, int height) {
            std::vector<uint8_t> moved;
            char direction = jet[jet_pos++];
            jet_pos %= jet.size();
            for (int i = 0; i < rocks.size(); i++) {
                if (direction == '<') {
                    if (!(rocks[i] & 0b1000000))
                        moved.push_back(rocks[i] << 1);
                } else {
                    if (!(rocks[i] & 0b0000001))
                        moved.push_back(rocks[i] >> 1);
                }
            }
            if (moved.size() != rocks.size() || collide(moved, height)) {
                return rocks;
            }
            return moved;
        }

        std::vector<uint8_t> v;
        size_t jet_pos = 0;
        int rock_i = 0;
        std::string jet;
    private:
};

int main()
{
    std::string jet;
    std::cin >> jet;

    { // PART 1
        NotTetris nt(jet);
        for (int rnd = 0; rnd < 2022; rnd++) nt.round();
        //nt.print();
        std::cout << nt.get_height() << ' ';
    }

    { // PART 2 NOT DONE
        uint64_t nrnd = 1e12;
        uint64_t crnd = 0;
        uint64_t height_offset = 0;

        using pu64 = std::pair<uint64_t, uint64_t>;
        std::map<pu64, pu64> mp;
        NotTetris nt(jet);

        std::cout << height_offset + nt.get_height() << std::endl;
    }

    return EXIT_SUCCESS;
}

