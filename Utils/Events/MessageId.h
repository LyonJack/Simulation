#pragma once
#include <atomic>
namespace events
{
	struct MessageId
	{
	public:
		MessageId();

	private:
		long id;
		static std::atomic<long> _id;
	};
}