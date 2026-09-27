#include "sepch.h"
#include "event.h"

// STL
#include <algorithm>

namespace sinter::engine
{

	void EventSystem::Init()
	{
		SE_FUNCTION_TRACE_ENTER();

		m_type.className = "EventSystem";
		m_type.classID = typeid(EventSystem).hash_code();

		SE_ENGINE_DEBUG("\tEventSystem initialized successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	void EventSystem::Shutdown()
	{
		SE_FUNCTION_TRACE_ENTER();

		for (auto& subs : m_subscribers)
		{
			subs.clear();
		}
		m_pendingAdds.clear();
		m_hasDeadSubscribers = false;

		{
			std::lock_guard<std::mutex>lock(m_queueMutex);
			m_queue.clear();
		}
		m_processing.clear();

		SE_ENGINE_DEBUG("\tEventSystem shut down successfully!");

		SE_FUNCTION_TRACE_EXIT();
	}

	SubscriptionID EventSystem::Subscribe(EventType p_type, EventCallbackFn p_callback)
	{
		if (STATIC_CAST(u32, p_type) >= k_eventTypeCount)
		{
			SE_ENGINE_ERROR("Attempted to subscribe to an invalid event type {0}.", STATIC_CAST(u32, p_type));
			return InvalidSubscriptionID;
		}

		if (p_callback == nullptr)
		{
			SE_ENGINE_ERROR("There is no callback function provided for subscription to event type {0}.", EventTypeToString(p_type));
			return InvalidSubscriptionID;
		}

		const SubscriptionID id = core::UUID(SHIFT_LEFT(m_nextID++, 8) | STATIC_CAST(u64, p_type));
		Subscriber sub{ id, std::move(p_callback) };

		if (m_publishDepth > 0)
		{
			m_pendingAdds.push_back(std::move(sub));
		}
		else
		{
			m_subscribers[STATIC_CAST(u32, p_type)].push_back(std::move(sub));
		}

		return id;
	}

	void EventSystem::Unsubscribe(SubscriptionID p_id)
	{
		if (p_id == InvalidSubscriptionID)
		{
			SE_ENGINE_ERROR("Attempted to unsubscribe with an invalid subscription ID.");
			return;
		}

		auto pendingIt = std::find_if(m_pendingAdds.begin(), m_pendingAdds.end(), [p_id](const Subscriber& s) { return s.id == p_id; });
		if (pendingIt != m_pendingAdds.end())
		{
			m_pendingAdds.erase(pendingIt);
			return;
		}

		const u32 l_typeIndex = TypeIndexFromID(p_id);
		if (l_typeIndex >= k_eventTypeCount)
		{
			SE_ENGINE_ERROR("Attempted to unsubscribe with a malformed subscription ID: {0}.", p_id);
			return;
		}

		auto& subs = m_subscribers[l_typeIndex];
		auto it = std::find_if(subs.begin(), subs.end(), [p_id](const Subscriber& s) { return s.id == p_id; });
		if (it == subs.end())
		{
			SE_ENGINE_ERROR("Attempted to unsubscribe with an unknown subscription ID: {0}.", p_id);
			return;
		}

		if (m_publishDepth > 0)
		{
			it->callback = nullptr;
			m_hasDeadSubscribers = true;
		}
		else
		{
			subs.erase(it);
		}
	}

	void EventSystem::Publish(EventContext& p_refEvent)
	{
		const u32 typeIndex = STATIC_CAST(u32, p_refEvent.type);
		if (typeIndex >= k_eventTypeCount)
		{
			SE_ENGINE_ERROR("Attempted to publish an event with an invalid type {0}.", typeIndex);
			return;
		}

		auto& subs = m_subscribers[typeIndex];

		m_publishDepth++;
		for (auto& sub : subs)
		{
			if (!sub.callback)
			{
				continue;
			}

			if (sub.callback(p_refEvent))
			{
				p_refEvent.handled = true;
				break;
			}
		}
		m_publishDepth--;

		if (m_publishDepth == 0)
		{
			FlushPendingChanges();
		}
	}

	void EventSystem::QueueEvent(const EventContext& p_refEvent)
	{
		if (p_refEvent.type == EventType::None || STATIC_CAST(u32, p_refEvent.type) >= k_eventTypeCount)
		{
			SE_ENGINE_ERROR("Attempted to queue an event with an invalid type {0}.", STATIC_CAST(u32, p_refEvent.type));
			return;
		}

		std::lock_guard<std::mutex> l_lock(m_queueMutex);
		m_queue.push_back(p_refEvent);
	}

	void EventSystem::DispatchEvents()
	{
		{
			std::lock_guard<std::mutex> l_lock(m_queueMutex);
			std::swap(m_queue, m_processing);
		}

		for (auto& p_refEvent : m_processing)
		{
			Publish(p_refEvent);
		}

		m_processing.clear();
	}

	void EventSystem::FlushPendingChanges()
	{
		if (m_hasDeadSubscribers)
		{
			for (auto& subs : m_subscribers)
			{
				subs.erase(std::remove_if(subs.begin(), subs.end(), [](const Subscriber& s) { return !s.callback; }), subs.end());
			}
			m_hasDeadSubscribers = false;
		}

		for (auto& sub : m_pendingAdds)
		{
			m_subscribers[TypeIndexFromID(sub.id)].push_back(std::move(sub));
		}
		m_pendingAdds.clear();
	}

} // namespace sinter::engine