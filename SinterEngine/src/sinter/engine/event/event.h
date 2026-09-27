#pragma once

// Internal
#include "event_types.h"

#include <sinter/core/assert.h>
#include <sinter/core/patterns/singleton.h>
#include <sinter/core/types/array.h>
#include <sinter/core/types/object.h>
#include <sinter/core/types/vector.h>

// STL
#include <mutex>

namespace sinter::engine
{

	class EventSystem final : public core::Singleton<EventSystem>, public core::SEObject
	{
		friend class core::Singleton<EventSystem>;

		static constexpr u32 k_eventTypeCount = STATIC_CAST(u32, EventType::Count);

	public:
		void Init();
		void Shutdown();

		SubscriptionID Subscribe(EventType p_type, EventCallbackFn p_callback);
		void Unsubscribe(SubscriptionID p_id);

		void Publish(EventContext& p_refEvent);

		void QueueEvent(const EventContext& p_refEvent);
		void DispatchEvents();

	private:
		EventSystem() = default;
		~EventSystem() = default;

		static u32 TypeIndexFromID(SubscriptionID p_id) { return STATIC_CAST(u32, p_id & 0xFF); }

		void FlushPendingChanges();

	private:
		struct Subscriber
		{
			SubscriptionID id{ InvalidSubscriptionID };
			EventCallbackFn callback{ nullptr };
		};

		SEArray<SEVector<Subscriber>, k_eventTypeCount> m_subscribers;

		SEVector<Subscriber> m_pendingAdds;
		b8 m_hasDeadSubscribers{ false };
		u32 m_publishDepth{ 0 };
		u64 m_nextID{ 1 };

		SEVector<EventContext> m_queue;
		SEVector<EventContext> m_processing;
		std::mutex m_queueMutex;
	};

} // namespace sinter::engine