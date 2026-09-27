#pragma once

// Sinter Engine
#include <sinter/sinter.h>

using namespace sinter;
using namespace core;
using namespace engine;

class PlaygroundApplication : public Application
{
public:
	PlaygroundApplication(const ApplicationConfiguration& p_refConfiguration);
	virtual ~PlaygroundApplication() = default;

	void Init() override;
	void Shutdown() override;

	void OnProcessUpdate() override;

	b8 OnWindowMove(EventContext& p_refEvent);
	b8 OnWindowResize(EventContext& p_refEvent);
	b8 OnWindowClose(EventContext& p_refEvent);
	b8 OnWindowFocus(EventContext& p_refEvent);
	b8 OnWindowIconify(EventContext& p_refEvent);
	b8 OnWindowMaximize(EventContext& p_refEvent);
	b8 OnWindowContentScale(EventContext& p_refEvent);

	b8 OnKeyPressed(EventContext& p_refEvent);
	b8 OnKeyReleased(EventContext& p_refEvent);
	b8 OnKeyTyped(EventContext& p_refEvent);

	b8 OnMouseMoved(EventContext& p_refEvent);
	b8 OnMouseButtonPressed(EventContext& p_refEvent);
	b8 OnMouseButtonReleased(EventContext& p_refEvent);
	b8 OnMouseScrolled(EventContext& p_refEvent);

private:
};