/**
 * @file log.hpp
 * @author Sumedh Ghaisas
 *
 * Declaration of Log.
 */
#ifndef __LIBGDL_CORE_UTIL_LOG_HPP
#define __LIBGDL_CORE_UTIL_LOG_HPP

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

#include "prefixedoutstream.hpp"
#include "nulloutstream.hpp"

//! Color code escape sequences
#define BASH_RED "\033[0;31m"
#define BASH_GREEN "\033[0;32m"
#define BASH_YELLOW "\033[0;33m"
#define BASH_CYAN "\033[0;36m"
#define BASH_CLEAR "\033[0m"

namespace libgdl
{

/**
 * Provides a convenient way to give formatted output.
 *
 * The Log class has four members which can be used in the same way ostreams can
 * be used:
 *
 *  - Log::Debug
 *  - Log::Info
 *  - Log::Warn
 *  - Log::Fatal
 *
 * Each of these will prefix a tag to the output (for easy filtering). Log also
 * supports time-stamp. If enabled the time-stamp will be added before each line
 * and prefix. If the output is to the terminal some color schema relating to
 * the severity level can be added.
 *
 * An example is given below.
 *
 * @code
 * Log test;
 * test.Info << "Checking a condition." << std::endl;
 * if (!someCondition())
 *   Log::Warn << "someCondition() is not satisfied!" << std::endl;
 * test.Info << "Checking an important condition." << std::endl;
 * if (!someImportantCondition())
 * {
 *   Log.Fatal << "someImportantCondition() is not satisfied! Terminating.";
 *   Log.Fatal << std::endl;
 *   exit(0);
 * }
 * @endcode
 * The coloring is enabled by default.
 *
 * To enable time-stamp addition-
 * @code
 * Log test(std::cout, true);
 * @endcode
 *
 * To disable the coloring -
 * @code
 * Log log(std::cout, true, false);
 * @endcode
 *
 * @see PrefixedOutStream
 */
class Log
{
 public:
  //! Constructs Logging stream from output stream
  //!
  //! \param stream Stream to output
  //! \param timestamp To enable the time-stamp addition
  //! \param addColor To enable color coding
  //!
  //!
  Log(std::ostream& stream = std::cout,
      bool timestamp = false,
      bool addColor = true)

  {
    if(addColor)
    {
      Debug = util::PrefixedOutStream(stream,
                                      BASH_CYAN "[DEBUG] " BASH_CLEAR,
                                      false,
                                      timestamp);
      Info = util::PrefixedOutStream(stream,
                                     BASH_GREEN "[INFO ] " BASH_CLEAR,
                                     false /* unless --verbose */,
                                     timestamp);
      Warn = util::PrefixedOutStream(stream,
                                     BASH_YELLOW "[WARN ] " BASH_CLEAR,
                                     false,
                                     timestamp);
      Fatal = util::PrefixedOutStream(stream,
                                      BASH_RED "[FATAL] " BASH_CLEAR,
                                      false,
                                      timestamp);
    }
    else
    {
      Debug = util::PrefixedOutStream(stream,
                                      "[DEBUG] ",
                                      false,
                                      timestamp);
      Info = util::PrefixedOutStream(stream,
                                     "[INFO ] ",
                                     false /* unless --verbose */,
                                     timestamp);
      Warn = util::PrefixedOutStream(stream,
                                     "[WARN ] ",
                                     false,
                                     timestamp);
      Fatal = util::PrefixedOutStream(stream,
                                      "[FATAL] ",
                                      false,
                                      timestamp);
    }
  }

  //! Checks if the specified condition is true.
  //! If not, halts program execution and prints a custom error message.
  //! Does nothing in non-debug mode.
  //!
  //!
  //! \param condition Condition to check
  //! \param message Message to be shown if the condition fails
  //! \return
  //!
  //!
  static void Assert(bool condition,
                     const std::string& message = "Assert Failed.");

  //! Set output stream
  //!
  //! \param stream Output stream to be used by the logging stream
  //! \return void
  //!
  //!
  void SetStream(std::ostream& stream)
  {
    Debug.SetStream(stream);
    Info.SetStream(stream);
    Warn.SetStream(stream);
    Fatal.SetStream(stream);
  }

  //! Prints debug output with the appropriate tag: [DEBUG].
  util::PrefixedOutStream Debug;

  //! Prints informational messages if --verbose is specified, prefixed with
  //! [INFO ].
  util::PrefixedOutStream Info;

  //! Prints warning messages prefixed with [WARN ].
  util::PrefixedOutStream Warn;

  //! Prints fatal messages prefixed with [FATAL], then terminates the program.
  util::PrefixedOutStream Fatal;
}; // class Log

}; //namespace libgdl

#endif // __LIBGDL_CORE_UTIL_LOG_HPP
