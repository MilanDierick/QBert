#include "ScoreComponent.h"

#include "EventArgs.h"
#include "IScoreSource.h"
#include "SandboxScene.h"

ScoreComponent::ScoreComponent(const Heirloom::WeakRef<Heirloom::GameObject> parent, const unsigned int initialScore)
	: m_Score(initialScore), m_Parent(parent)
{
	RegisterToAllScoreSourceEvents();
}

Heirloom::WeakRef<Heirloom::GameObject> ScoreComponent::GetParent() const { return m_Parent; }

void ScoreComponent::SetParent(const Heirloom::Ref<Heirloom::GameObject> gameObject) { m_Parent = gameObject; }

void ScoreComponent::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);
}

void ScoreComponent::Render()
{
	ImGui::SetNextWindowPos(ImVec2(10, 100));
	ImGui::Begin("Score",
				 nullptr,
				 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowFontScale(2.0);
	ImGui::Text("Score: %d", m_Score);
	ImGui::End();
}

void ScoreComponent::RegisterToAllScoreSourceEvents()
{
	std::vector<Heirloom::Ref<Heirloom::GameObject>> gameObjects = m_Parent.lock()->GetCurrentScene()->GetGameObjects();

	for (Heirloom::Ref<Heirloom::GameObject> gameObject : gameObjects)
	{
		Heirloom::Ref<IScoreSource> scoreSource = gameObject->GetComponent<IScoreSource>();

		if (scoreSource) { scoreSource->ScoreSourceEvent += HL_BIND_EVENT_FN(ScoreComponent::OnScoreSourceEvent); }
	}
}

void ScoreComponent::OnScoreSourceEvent(const ScoreSourceEventArgs args)
{
	switch (args.ScoreSource)
	{
		case ScoreSource::Tile: m_Score += SandboxScene::Configuration.ScorePerOccupiedTile;
			break;
		default: ;
	}
}
