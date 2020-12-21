
#include <string>
#include <exception>

class URLException : public std::exception
{
    public:
        URLException(const std::string &exception_string)
        {
            _exception_string = exception_string;
        }

        const char* what() const throw()
        {
            return _exception_string.c_str();
        }

        ~URLException() throw()
        {

        }
    private:
        std::string _exception_string;
};