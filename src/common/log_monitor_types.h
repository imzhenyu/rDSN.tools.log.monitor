/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef log_monitor_TYPES_H
#define log_monitor_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace dsn { namespace tools {

class log_monitor_entry;

typedef struct _log_monitor_entry__isset {
  _log_monitor_entry__isset() : file(false), line(false), log(false), level(false), func(false) {}
  bool file :1;
  bool line :1;
  bool log :1;
  bool level :1;
  bool func :1;
} _log_monitor_entry__isset;

class log_monitor_entry {
 public:

  log_monitor_entry(const log_monitor_entry&);
  log_monitor_entry(log_monitor_entry&&);
  log_monitor_entry& operator=(const log_monitor_entry&);
  log_monitor_entry& operator=(log_monitor_entry&&);
  log_monitor_entry() : file(), line(0), log(), level(0), func() {
  }

  virtual ~log_monitor_entry() throw();
  std::string file;
  int32_t line;
  std::string log;
  int32_t level;
  std::string func;

  _log_monitor_entry__isset __isset;

  void __set_file(const std::string& val);

  void __set_line(const int32_t val);

  void __set_log(const std::string& val);

  void __set_level(const int32_t val);

  void __set_func(const std::string& val);

  bool operator == (const log_monitor_entry & rhs) const
  {
    if (!(file == rhs.file))
      return false;
    if (!(line == rhs.line))
      return false;
    if (!(log == rhs.log))
      return false;
    if (!(level == rhs.level))
      return false;
    if (!(func == rhs.func))
      return false;
    return true;
  }
  bool operator != (const log_monitor_entry &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const log_monitor_entry & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(log_monitor_entry &a, log_monitor_entry &b);

inline std::ostream& operator<<(std::ostream& out, const log_monitor_entry& obj)
{
  obj.printTo(out);
  return out;
}

}} // namespace

#endif
