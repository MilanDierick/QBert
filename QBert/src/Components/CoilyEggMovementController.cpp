#include "CoilyEggMovementController.h"

#include "CoilyMovementController.h"
#include "TileComponent.h"

CoilyEggMovementController::CoilyEggMovementController(const MovementControllerData data,
													   const TileState preferredTileState,
													   const Heirloom::WeakRef<Heirloom::GameObject> parent)
	: MovementController(data, preferredTileState, parent.lock()->GetTransform()), m_Parent(parent)
{
	SetTicksSinceLastMove(0);
}

Heirloom::WeakRef<Heirloom::GameObject> CoilyEggMovementController::GetParent() const { return m_Parent; }

void CoilyEggMovementController::SetParent(Heirloom::Ref<Heirloom::GameObject> gameObject) { m_Parent = gameObject; }

void CoilyEggMovementController::Update(Heirloom::Timestep ts)
{
	UNREFERENCED_PARAMETER(ts);

	MovementController::Update(false);

	if (GetCurrentHex().R == 0)
	{
		if (GetTicksSinceLastMove() >= GetTicksBetweenMoves() * 2) { SpawnCoily(); }

		return;
	}

	if (GetCurrentHex().Q == GetTargetHex().Q && GetCurrentHex().R == GetTargetHex().R) { DesignateNextHexTarget(); }
}

void CoilyEggMovementController::Render()
{
}

void CoilyEggMovementController::SpawnCoily()
{
	m_Parent.lock()->SetActive(false);

	#pragma region CoilyGameObject
	MovementControllerData coilyData = SandboxScene::ReadFileToJson<MovementControllerData>(
		"assets/levels/sandbox/CoilyMovementControllerData.json");

	coilyData.CurrentHex = GetCurrentHex();
	coilyData.TargetHex = GetCurrentHex();

	const auto coilyTexture = Heirloom::Texture2D::Create("assets/textures/CoilyTexture.png");
	const auto coilySprite  = Heirloom::CreateRef<Heirloom::Sprite>(coilyTexture);

	auto coilyGameObject = CreateRef<Heirloom::GameObject>(m_Parent.lock()->GetCurrentScene());

	coilyGameObject->AddComponent(CreateRef<CoilyMovementController>(coilyData, TileState::Clear, coilyGameObject));

	auto coilySpriteRenderer = coilyGameObject->AddComponent(Heirloom::CreateRef<Heirloom::SpriteRenderer>());
	coilySpriteRenderer->SetSprite(coilySprite);
	coilySpriteRenderer->SetSpriteOffset(glm::vec3{0.0f, GetHexagonalGridLayout().Size.y * 1.10f, -1.0f});

	m_Parent.lock()->GetCurrentScene()->GetGameObjects().push_back(coilyGameObject);
	#pragma endregion

	const CoilyEggDestroyedEventArgs args = CoilyEggDestroyedEventArgs(GetCurrentHex());
	CoilyEggDestroyedEvent.Invoke(args);
}

void CoilyEggMovementController::DesignateNextHexTarget()
{
	if (std::rand() % 2 == 1) { SetTargetHexInDirection(MovementDirection::SouthEast); }
	else { SetTargetHexInDirection(MovementDirection::SouthWest); }
}
