#include "Heirloom.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Heirloom/Core/EntryPoint.h"
#include "SandboxScene.h"

class QBertApplication final : public Heirloom::Application
{
public:
	QBertApplication()
	{
		HL_PROFILE_FUNCTION()

		Heirloom::SceneManager::LoadScene(new SandboxScene("SandboxScene"), false);

		HL_INFO("Initialized QBertApplication!");
	}

	~QBertApplication() override
	{
	}
};

Heirloom::Application* Heirloom::CreateApplication()
{
	HL_PROFILE_FUNCTION();

	return new QBertApplication();
}

