#include "HealthComponent.h"

HealthComponent::HealthComponent(const int maximumLives, const int currentLives)
	: m_MaximumLives(maximumLives), m_CurrentLives(currentLives)
{
}

void HealthComponent::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);
}

void HealthComponent::Render()
{
	ImGui::SetNextWindowPos(ImVec2(10, 50));
	ImGui::Begin("Health",
				 nullptr,
				 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2.0);
	ImGui::Text("Health: %d", m_CurrentLives);
	ImGui::End();
}

void HealthComponent::RegisterOutOfBoundsEventHandler(Heirloom::Ref<QBertMovementController> controller)
{
	controller->OutOfBoundsEvent += HL_BIND_EVENT_FN(HealthComponent::OnOutOfBoundsEvent);
}

void HealthComponent::OnOutOfBoundsEvent(OutOfBoundsEventArgs args)
{
	UNREFERENCED_PARAMETER(args);

	if (--m_CurrentLives <= 0)
	{
		const HealthDepletedEventArgs healthDepletedEventArgs = HealthDepletedEventArgs(m_MaximumLives, m_CurrentLives);
		HealthDepletedEvent.Invoke(healthDepletedEventArgs);
	}
}
