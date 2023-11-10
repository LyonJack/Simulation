#include "MessageCenter.h"
namespace events
{
    EventAggregator* MessageCenter::eventAggregator = new EventAggregator();
}