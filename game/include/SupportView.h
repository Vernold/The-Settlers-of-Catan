#ifndef SupportView_h
#define SupportView_h

#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>

#include "Regexp.h"
#include "IGameEngine.h"

enum {
    SUCCESS = 0,
    FAILURE = -1
};

/*
 true
*/

class SupportView
{
protected:
    IGameEngine &engine;
    
public:
    SupportView(IGameEngine &);
    
protected:
    void clear() const noexcept;
    std::string get_line(const std::string &) const noexcept;
    void out_line(size_t, char) const noexcept;
    void out_string(size_t, const std::string &) const noexcept;
    void window(const std::vector<const std::string> &) const noexcept;
    
    std::string to_upper(const std::string &) const noexcept;
    Resource to_resource(const std::string &) const;
    CrossCorner to_corner(const std::string &) const;
    RoadSide to_side(const std::string &) const;
    Coord to_coord(const std::string &) const;
    
    std::vector<std::string> get_build_args(const std::string &) const;
    
    const std::string to_string(Resource) const;
    
    void info() const;
};

#endif /* SupportView_h */
