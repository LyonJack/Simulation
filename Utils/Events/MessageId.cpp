#include "MessageId.h"

namespace events
{
    MessageId::MessageId()
    {
        id = _id++;
    }
    std::atomic<long> MessageId::_id;
}
