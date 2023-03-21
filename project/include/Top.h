#ifndef PROJECT_INCLUDE_TOP_H_
#define PROJECT_INCLUDE_TOP_H_

#include <vector>
#include "Film.h"

class Top {
 public:
    Top() = delete;
    ~Top() = default;
    Top(const Top& other) = delete;
    Top(Top&& other) = delete;

    Top(const std::vector<film_t>& _films, int _top_size);
    Top(std::vector<film_t>&& _film, int _top_size);

    std::vector<film_t> getTop();
 private:
    std::vector<film_t> films;
    int top_size;
    void generateTop();
};

#endif  // PROJECT_INCLUDE_TOP_H_
