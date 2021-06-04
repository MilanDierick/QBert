// Author: Milan Dierick
// Created: 03/06/2021 2:48 AM
// Solution: QBert

#pragma once
#include "Heirloom.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "ExternalJsonTypeParserDefinitions.h"

struct SandboxLevelSettings
{
	SandboxLevelSettings() = default;

	[[nodiscard]]
	SandboxLevelSettings(const int pyramidWidth,
						 const int aspectRatioWidth,
						 const int aspectRatioHeight,
						 const int maximumHealth,
						 const int startHealth,
						 const int ticksBetweenMoves,
						 const int ticksPerMove,
						 const float initialZoomLevel,
						 const std::string& qBertTexture,
						 const std::string& testTileTexture,
						 const std::string& diskTexture,
						 const glm::vec2& testTileSpriteSize,
						 const glm::vec2& qBertSpritePositionOffset,
						 const glm::vec3& startingHexPosition,
						 const glm::vec4& clearColor)
		: PyramidWidth(pyramidWidth),
		  AspectRatioWidth(aspectRatioWidth),
		  AspectRatioHeight(aspectRatioHeight),
		  MaximumHealth(maximumHealth),
		  StartHealth(startHealth),
		  TicksBetweenMoves(ticksBetweenMoves),
		  TicksPerMove(ticksPerMove),
		  InitialZoomLevel(initialZoomLevel),
		  QBertTexture(qBertTexture),
		  TestTileTexture(testTileTexture),
		  DiskTexture(diskTexture),
		  TestTileSpriteSize(testTileSpriteSize),
		  QBertSpritePositionOffset(qBertSpritePositionOffset),
		  CameraHexPosition(startingHexPosition),
		  ClearColor(clearColor)
	{
	}

	int PyramidWidth;
	int AspectRatioWidth;
	int AspectRatioHeight;
	int MaximumHealth;
	int StartHealth;
	int TicksBetweenMoves;
	int TicksPerMove;

	float InitialZoomLevel;

	std::string QBertTexture;
	std::string TestTileTexture;
	std::string DiskTexture;

	glm::vec2 TestTileSpriteSize;
	glm::vec2 QBertSpritePositionOffset;
	glm::vec3 InitialQBertPosition;
	glm::vec3 CameraHexPosition;
	glm::vec4 ClearColor;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SandboxLevelSettings,
								   PyramidWidth,
								   AspectRatioWidth,
								   AspectRatioHeight,
								   MaximumHealth,
								   StartHealth,
								   TicksBetweenMoves,
								   TicksPerMove,
								   InitialZoomLevel,
								   QBertTexture,
								   TestTileTexture,
								   DiskTexture,
								   TestTileSpriteSize,
								   QBertSpritePositionOffset,
								   InitialQBertPosition,
								   CameraHexPosition,
								   ClearColor);
};
