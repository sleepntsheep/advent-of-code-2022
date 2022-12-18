#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <utility>
#include <cassert>

const std::vector<uint8_t> Rocks[] = {
    {0b11110},
    {0b01000, 0b11100, 0b01000},
    {0b11100, 0b00100, 0b00100},
    {0b10000, 0b10000, 0b10000, 0b10000},
    {0b11000, 0b11000},
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;  
    }
};

class NotTetris {
    public:
        NotTetris(std::string j): jet(j) { }
        ~NotTetris() { }

        void round() {
            std::vector<uint8_t> rock = Rocks[rock_i++ % 5];
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
            return v.size() + height_offset;
        }

        void print() {
            for (int i = v.size() - 1; i >= 0; i--) {
                for (int j = 6; j >= 0; j--) {
                    std::cout << (v[i] & (1 << j) ? '#' : '.');
                }
                std::cout << std::endl;
            }
        }

        bool collide(const std::vector<uint8_t> &rock, int height) {
            if (height >= v.size())
                return false;
            for (int i = 0; i < rock.size(); i++) {
                while (height + i >= v.size())
                    return false;
                if (rock[i] & v[height + i])
                    return true;
            }
            return false;
        }

        bool fall(const std::vector<uint8_t> &rock, int height) {
            if (height == 0 || collide(rock, height - 1))
                return false;
            return true;
        }

        void rest(const std::vector<uint8_t> &rock, int height) {
            for (int i = 0; i < rock.size(); i++) {
                if (height + i >= v.size()) {
                    v.push_back(rock[i]);
                } else {
                    v[height + i] |= rock[i];
                }
            }
        }

        std::vector<uint8_t> push(const std::vector<uint8_t> &rock, int height) {
            std::vector<uint8_t> moved;
            char direction = jet[jet_pos++];
            jet_pos %= jet.size();
            for (int i = 0; i < rock.size(); i++) {
                if (direction == '<') {
                    if (!(rock[i] & 0b1000000))
                        moved.push_back(rock[i] << 1);
                } else {
                    if (!(rock[i] & 0b0000001))
                        moved.push_back(rock[i] >> 1);
                }
            }
            if (moved.size() != rock.size() || collide(moved, height)) {
                return rock;
            }
            return moved;
        }

        uint64_t fast_simulate(uint64_t nrnd) {
            uint64_t crnd = 0;

            using pu64 = std::pair<uint64_t, uint64_t>;
            std::map<pu64, pu64> mp;

            for (;crnd < nrnd;) {
                round();
                crnd++;

                if (mp.count({crnd % 5, jet_pos})) {
                    bool true_cycle = true;
                    auto [height, start] = mp[{crnd % 5, jet_pos}];

                    constexpr int N_CHECK_ROW = 16;
                    for (size_t i = 1; i <= N_CHECK_ROW; i++) {
                        if (v[height - i] != v[v.size() - i]) {
                            true_cycle = false;
                            break;
                        }
                    }

                    auto cycle_rnd = crnd - start;
                    if (true_cycle && cycle_rnd) {
                        auto cycle_height = get_height() - height;
                        auto iters = (nrnd - crnd) / cycle_rnd;
                        height_offset += iters * cycle_height;
                        crnd += iters * cycle_rnd;
                    }
                } else {
                    mp[{crnd % 5, jet_pos}] = {get_height(), crnd};
                }
            }

            return get_height();
        }

        std::vector<uint8_t> v;
        size_t jet_pos = 0;
        uint64_t height_offset = 0;
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
        NotTetris nt(jet);
        nt.fast_simulate(1000000000000LL);
        std::cout << nt.get_height() << std::endl;
    }

    return EXIT_SUCCESS;
}

