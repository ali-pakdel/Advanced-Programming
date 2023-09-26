#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <string>
#include <vector>

class Comment
{
public:
    Comment(std::string username_, std::string comment_)
    {
        username = username_;
        comment = comment_;
    }
    std::string get_username() { return username; }
    std::string get_comment() { return comment; }
private:
    std::string username;
    std::string comment;
};
typedef std::vector<Comment> CommentsVec;

#endif