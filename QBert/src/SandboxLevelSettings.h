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
						 const int scorePerOccupiedTile,
						 const int scorePerDiskLeft,
						 const int scorePerCoilyDeath,
						 const float initialZoomLevel,
						 const std::string& qBertTexture,
						 const std::string& tileTexture,
						 const std::string& alternateTileTexture,
						 const std::string& diskTexture,
						 const glm::vec2& testTileSpriteSize,
						 const glm::vec2& qBertSpritePositionOffset,
						 const glm::vec3& initialQBertPosition,
						 const glm::vec3& startingHexPosition,
						 const glm::vec4& clearColor)
		: PyramidWidth(pyramidWidth),
		  AspectRatioWidth(aspectRatioWidth),
		  AspectRatioHeight(aspectRatioHeight),
		  MaximumHealth(maximumHealth),
		  StartHealth(startHealth),
		  TicksBetweenMoves(ticksBetweenMoves),
		  TicksPerMove(ticksPerMove),
		  ScorePerOccupiedTile(scorePerOccupiedTile),
		  ScorePerDiskLeft(scorePerDiskLeft),
		  ScorePerCoilyDeath(scorePerCoilyDeath),
		  InitialZoomLevel(initialZoomLevel),
		  QBertTexture(qBertTexture),
		  TileTexture(tileTexture),
		  AlternateTileTexture(alternateTileTexture),
		  DiskTexture(diskTexture),
		  TestTileSpriteSize(testTileSpriteSize),
		  QBertSpritePositionOffset(qBertSpritePositionOffset),
		  InitialQBertPosition(initialQBertPosition),
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
	int ScorePerOccupiedTile;
	int ScorePerDiskLeft;
	int ScorePerCoilyDeath;

	float InitialZoomLevel;

	std::string QBertTexture;
	std::string TileTexture;
	std::string AlternateTileTexture;
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
								   ScorePerOccupiedTile,
								   ScorePerDiskLeft,
								   ScorePerCoilyDeath,
								   InitialZoomLevel,
								   QBertTexture,
								   TileTexture,
								   AlternateTileTexture,
								   DiskTexture,
								   TestTileSpriteSize,
								   QBertSpritePositionOffset,
								   InitialQBertPosition,
								   CameraHexPosition,
								   ClearColor);
};
