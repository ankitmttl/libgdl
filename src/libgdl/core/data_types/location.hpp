/**
 * @file location.hpp
 * @author Sumedh Ghaisas
 *
 * Data structure to store location of any identifier.
 */
#ifndef _LIBGDL_CORE_DATATYPES_HPP_INCLUDED
#define _LIBGDL_CORE_DATATYPES_HPP_INCLUDED

#include <string>

#include <libgdl/gdlparser/parser/location.hh>

namespace libgdl
{

/**
 * This structure represents location of the identifier. It stores the filename
 * and lineNo for tracking. Location is used in debugging KnowledgeBase. Location
 * is used in place of location_type (implicitly defined by gdlparser) so
 * that filename (the string variable) will be destroyed properly. location_type
 * class holds pointer to filename (string) which sometimes create problems.
 */
struct Location
{
  //! some useful typedefs
  typedef gdlparser::parser::yy::location location_type;

  //! empty constructor
  Location() {}
  //! constructs location object from location_type of parser
  Location(const location_type& loc)
  {
    filename = *loc.begin.filename;
    lineNo = loc.begin.line;
  }
  //! constructs location from line number and filename
  Location(size_t lineNo, const std::string& filename)
    : filename(filename), lineNo(lineNo) {}

  //! Comparison operators
  bool operator==(const Location& loc) const
  {
    if(lineNo != loc.lineNo) return false;
    if(filename != loc.filename) return false;
    return true;
  }
  bool operator!=(const Location& loc) const { return !(*this == loc); }


  //! holds filename
  std::string filename;
  //! holds line number
  size_t lineNo;
}; // struct Location

}; // namespace libgdl

inline std::ostream& operator<<(std::ostream& o,
                                const libgdl::Location& loc)
{
  o << loc.lineNo << " \"" << loc.filename << "\"";
  return o;
}

#endif // _LIBGDL_CORE_HPP_INCLUDED