#ifndef OPENVPN_BUFFER_MEMQ_H
#define OPENVPN_BUFFER_MEMQ_H

#include <deque>

#include <openvpn/common/types.hpp>
#include <openvpn/buffer/buffer.hpp>

namespace openvpn {

  class MemQBase
  {
  public:
    MemQBase() : length(0) {}

    bool empty() const
    {
      return q.empty();
    }

    size_t total_length() const { return length; }

    void clear()
    {
      while (!q.empty())
	q.pop_back();
      length = 0;
    }

    void write(BufferPtr& bp)
    {
      q.push_back(bp);
      length += bp->size();
    }

    BufferPtr read()
    {
      BufferPtr ret = q.front();
      q.pop_front();
      length -= ret->size();
      return ret;
    }

  protected:
    typedef std::deque<BufferPtr> q_type;
    size_t length;
    q_type q;
  };

} // namespace openvpn

#endif // OPENVPN_BUFFER_MEMQ_H
